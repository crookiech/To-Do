import time
import statistics
import json
import psycopg2
import sqlite3
from pathlib import Path

class Benchmark:
    def __init__(self):
        self.results = {}
        self.test_data = self.generate_test_data()
        
    def generate_test_data(self):
        import random
        test_data = {}
        user_count = 1000
        task_count = 100
        for user_id in range(1, user_count):
            tasks = []
            for i in range(task_count):
                task = {
                    'title': f'Тестовая задача {i}',
                    'year': 2024,
                    'month': random.randint(1, 12),
                    'day': random.randint(1, 28),
                    'hours': random.randint(0, 23),
                    'minutes': random.randint(0, 59),
                    'is_completed': random.choice([True, False])
                }
                tasks.append(task)
            test_data[user_id] = tasks
        print(f"Сгенерировано: {user_count} пользователей × {task_count} задач = {user_count * task_count} записей")
        return test_data

class PostgresTest:
    def __init__(self):
        try:
            self.conn = psycopg2.connect(
                host="localhost",
                database="todo_benchmark",
                user="postgres",
                password="123456789",
                port="5432"
            )
            self.setup_database()
        except Exception as e:
            print(f"Ошибка подключения к PostgreSQL: {e}")
            self.conn = None
    
    def setup_database(self):
        cursor = self.conn.cursor()
        cursor.execute("DROP TABLE IF EXISTS benchmark_tasks")
        cursor.execute("DROP TABLE IF EXISTS benchmark_users")
        cursor.execute('''
            CREATE TABLE benchmark_users (
                id SERIAL PRIMARY KEY,
                username VARCHAR(50) UNIQUE
            )
        ''')
        cursor.execute('''
            CREATE TABLE benchmark_tasks (
                id SERIAL PRIMARY KEY,
                user_id INTEGER,
                title TEXT,
                year INTEGER,
                month INTEGER,
                day INTEGER,
                hours INTEGER,
                minutes INTEGER,
                is_completed BOOLEAN DEFAULT FALSE
            )
        ''')
        self.conn.commit()
        cursor.close()
    
    def test_insert(self, test_data):
        if not self.conn:
            return None
        cursor = self.conn.cursor()
        times = []
        print("Тест INSERT:")
        for user_id, tasks in test_data.items():
            start = time.perf_counter()
            cursor.execute(
                "INSERT INTO benchmark_users (username) VALUES (%s) RETURNING id",
                (f"user_{user_id}",)
            )
            user_db_id = cursor.fetchone()[0]
            for task in tasks:
                cursor.execute('''
                    INSERT INTO benchmark_tasks 
                    (user_id, title, year, month, day, hours, minutes, is_completed)
                    VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
                ''', (
                    user_db_id, task['title'], 
                    task['year'], task['month'], task['day'],
                    task['hours'], task['minutes'], task['is_completed']
                ))
            end = time.perf_counter()
            times.append((end - start) * 1000)
        self.conn.commit()
        cursor.close()
        avg_time = statistics.mean(times)
        total_time = sum(times)
        print(f"\tСреднее время: {avg_time:.2f} мс на пользователя")
        print(f"\tОбщее время: {total_time:.2f} мс")
        print(f"\tСкорость: {(len(times)*1000)/total_time:.1f} пользователей/сек" if total_time > 0 else "Скорость: 0 пользователей/сек")
        return {
            'avg_time_ms': avg_time,
            'total_time_ms': total_time,
            'throughput': (len(times)*1000)/total_time if total_time > 0 else 0
        }
    
    def test_select(self):
        if not self.conn:
            return None
        cursor = self.conn.cursor()
        times = []
        print("Тест SELECT:")
        queries = [
            ("\tПростой SELECT по user_id", "SELECT * FROM benchmark_tasks WHERE user_id = %s LIMIT 10", 1),
            ("\tSELECT с фильтром по дате", "SELECT * FROM benchmark_tasks WHERE year = 2024 AND month = 5 LIMIT 10", None),
            ("\tSELECT с сортировкой", "SELECT * FROM benchmark_tasks ORDER BY year, month, day LIMIT 10", None),
            ("\tSELECT COUNT", "SELECT COUNT(*) FROM benchmark_tasks WHERE is_completed = true", None),
        ]
        for desc, sql, param in queries:
            start = time.perf_counter()
            if param:
                cursor.execute(sql, (param,))
            else:
                cursor.execute(sql)
            end = time.perf_counter()
            query_time = (end - start) * 1000
            times.append(query_time)
            print(f"{desc}: {query_time:.2f} мс")
        cursor.close()
        avg_time = statistics.mean(times)
        print(f"\tСреднее время запроса: {avg_time:.2f} мс")
        return {
            'avg_time_ms': avg_time,
            'min_time_ms': min(times),
            'max_time_ms': max(times),
            'queries_tested': len(queries)
        }
    
    def test_concurrent(self):
        if not self.conn:
            return None
        print("Тест конкурентных запросов:")
        import threading
        import queue
        results_queue = queue.Queue()
        def worker(worker_id):
            try:
                conn = psycopg2.connect(
                    host="localhost",
                    database="todo_benchmark",
                    user="postgres",
                    password="123456789"
                )
                cursor = conn.cursor()
                start = time.perf_counter()
                for i in range(100):
                    cursor.execute(
                        "SELECT COUNT(*) FROM benchmark_tasks WHERE user_id = %s",
                        (worker_id % 100 + 1,)
                    )
                    cursor.fetchone()
                end = time.perf_counter()
                cursor.close()
                conn.close()
                avg_time = ((end - start) / 100) * 1000
                results_queue.put(avg_time)
            except Exception as e:
                print(f"Worker {worker_id} ошибка: {e}")
                results_queue.put(100)
        threads = []
        for i in range(100):
            t = threading.Thread(target=worker, args=(i,))
            threads.append(t)
            t.start()
        for t in threads:
            t.join()
        times = []
        while not results_queue.empty():
            times.append(results_queue.get())
        if times:
            avg_time = statistics.mean(times)
            print(f"\tСреднее время при 100 параллельных соединениях: {avg_time:.2f} мс")
            print(f"\tВсего выполнено: {100*100} запросов")
            return {'avg_concurrent_time_ms': avg_time}
        return None

class SQLiteTest:
    def __init__(self, db_file='benchmark_sqlite.db'):
        try:
            if Path(db_file).exists():
                Path(db_file).unlink()
            self.conn = sqlite3.connect(db_file)
            self.db_file = db_file
            self.setup_database()
        except Exception as e:
            print(f"Ошибка SQLite: {e}")
            self.conn = None
    
    def setup_database(self):
        cursor = self.conn.cursor()
        cursor.execute('''
            CREATE TABLE benchmark_users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE
            )
        ''')
        cursor.execute('''
            CREATE TABLE benchmark_tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER,
                title TEXT,
                year INTEGER,
                month INTEGER,
                day INTEGER,
                hours INTEGER,
                minutes INTEGER,
                is_completed BOOLEAN DEFAULT FALSE
            )
        ''')
        self.conn.commit()
        cursor.close()
    
    def test_insert(self, test_data):
        if not self.conn:
            return None
        cursor = self.conn.cursor()
        times = []
        print("Тест INSERT:")
        for user_id, tasks in test_data.items():
            start = time.perf_counter()
            cursor.execute(
                "INSERT INTO benchmark_users (username) VALUES (?)",
                (f"user_{user_id}",)
            )
            user_db_id = cursor.lastrowid
            for task in tasks:
                cursor.execute('''
                    INSERT INTO benchmark_tasks 
                    (user_id, title, year, month, day, hours, minutes, is_completed)
                    VALUES (?, ?, ?, ?, ?, ?, ?, ?)
                ''', (
                    user_db_id, task['title'], 
                    task['year'], task['month'], task['day'],
                    task['hours'], task['minutes'], task['is_completed']
                ))
            end = time.perf_counter()
            times.append((end - start) * 1000)
        self.conn.commit()
        cursor.close()
        avg_time = statistics.mean(times)
        total_time = sum(times)
        print(f"\tСреднее время: {avg_time:.2f} мс на пользователя")
        print(f"\tОбщее время: {total_time:.2f} мс")
        print(f"\tСкорость: {(len(times)*1000)/total_time:.1f} пользователей/сек" if total_time > 0 else "Скорость: 0 пользователей/сек")
        return {
            'avg_time_ms': avg_time,
            'total_time_ms': total_time,
            'throughput': (len(times)*1000)/total_time if total_time > 0 else 0
        }
    
    def test_select(self):
        if not self.conn:
            return None
        cursor = self.conn.cursor()
        times = []
        print("Тест SELECT:")
        queries = [
            ("\tПростой SELECT по user_id", "SELECT * FROM benchmark_tasks WHERE user_id = ? LIMIT 10", 1),
            ("\tSELECT с фильтром по дате", "SELECT * FROM benchmark_tasks WHERE year = 2024 AND month = 5 LIMIT 10", None),
            ("\tSELECT с сортировкой", "SELECT * FROM benchmark_tasks ORDER BY year, month, day LIMIT 10", None),
            ("\tSELECT COUNT", "SELECT COUNT(*) FROM benchmark_tasks WHERE is_completed = 1", None),
        ]
        for desc, sql, param in queries:
            start = time.perf_counter()
            if param:
                cursor.execute(sql, (param,))
            else:
                cursor.execute(sql)
            end = time.perf_counter()
            query_time = (end - start) * 1000
            times.append(query_time)
            print(f"  {desc}: {query_time:.2f} мс")
        cursor.close()
        avg_time = statistics.mean(times)
        print(f"\tСреднее время запроса: {avg_time:.2f} мс")
        return {
            'avg_time_ms': avg_time,
            'min_time_ms': min(times),
            'max_time_ms': max(times),
            'queries_tested': len(queries)
        }
    
    def test_concurrent(self):
        if not self.conn:
            return None
        print("Тест конкурентных запросов:")
        import threading
        import queue
        results_queue = queue.Queue()
        def worker(worker_id):
            try:
                conn = sqlite3.connect(self.db_file)
                cursor = conn.cursor()
                start = time.perf_counter()
                for i in range(100):
                    cursor.execute(
                        "SELECT COUNT(*) FROM benchmark_tasks WHERE user_id = ?",
                        (worker_id % 100 + 1,)
                    )
                    cursor.fetchone()
                end = time.perf_counter()
                cursor.close()
                conn.close()
                avg_time = ((end - start) / 100) * 1000
                results_queue.put(avg_time)
            except Exception as e:
                print(f"  Worker {worker_id} ошибка: {e}")
                results_queue.put(100)
        threads = []
        for i in range(100):
            t = threading.Thread(target=worker, args=(i,))
            threads.append(t)
            t.start()
        for t in threads:
            t.join()
        times = []
        while not results_queue.empty():
            times.append(results_queue.get())
        if times:
            avg_time = statistics.mean(times)
            print(f"\tСреднее время при 100 параллельных соединениях: {avg_time:.2f} мс")
            print(f"\tВсего выполнено: {100*100} запросов")
            return {'avg_concurrent_time_ms': avg_time}
        return None

class JSONFileTest:
    def __init__(self, data_dir='json_data'):
        self.data_dir = Path(data_dir)
        self.data_dir.mkdir(exist_ok=True)
        for file in self.data_dir.glob("*.json"):
            file.unlink()
    
    def test_insert(self, test_data):
        print("Тест записи:")
        write_times = []
        for user_id, tasks in test_data.items():
            start = time.perf_counter()
            file_path = self.data_dir / f"user_{user_id}.json"
            with open(file_path, 'w', encoding='utf-8') as f:
                json.dump(tasks, f, indent=2, ensure_ascii=False)
            end = time.perf_counter()
            write_times.append((end - start) * 1000)
        
        avg_time = statistics.mean(write_times)
        total_time = sum(write_times)
        print(f"\tСреднее время: {avg_time:.2f} мс на пользователя")
        print(f"\tОбщее время: {total_time:.2f} мс")
        print(f"\tСкорость: {(len(write_times)*1000)/total_time:.1f} пользователей/сек" if total_time > 0 else "Скорость: 0 пользователей/сек")
        total_size = sum(f.stat().st_size for f in self.data_dir.glob("*.json"))
        print(f"\tОбщий размер данных: {total_size/1024:.1f} KB")
        return {
            'avg_time_ms': avg_time,
            'total_time_ms': total_time,
            'throughput': (len(write_times)*1000)/total_time if total_time > 0 else 0,
            'size_kb': total_size / 1024
        }
    
    def test_select(self):
        print("Тест чтения:")
        read_times = []
        files = list(self.data_dir.glob("*.json"))
        if not files:
            print("Нет данных для тестирования чтения")
            return None
        start = time.perf_counter()
        with open(files[0], 'r', encoding='utf-8') as f:
            data = json.load(f)
        query1_time = (time.perf_counter() - start) * 1000
        print(f"\tЧтение одного файла: {query1_time:.2f} мс")
        read_times.append(query1_time)
        start = time.perf_counter()
        all_tasks_month5 = []
        for file in files[:5]:
            with open(file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                filtered = [t for t in data if t['month'] == 5]
                all_tasks_month5.extend(filtered)
        query2_time = (time.perf_counter() - start) * 1000
        print(f"\tС фильтрацией по месяцу: {query2_time:.2f} мс")
        read_times.append(query2_time)
        start = time.perf_counter()
        all_tasks = []
        for file in files[:3]:  # Ограничимся 3 файлами
            with open(file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                all_tasks.extend(data)
        all_tasks.sort(key=lambda x: (x['year'], x['month'], x['day']))
        query3_time = (time.perf_counter() - start) * 1000
        print(f"\tС сортировкой по дате: {query3_time:.2f} мс")
        read_times.append(query3_time)
        start = time.perf_counter()
        completed_count = 0
        for file in files[:5]:
            with open(file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                completed_count += sum(1 for t in data if t['is_completed'])
        query4_time = (time.perf_counter() - start) * 1000
        read_times.append(query4_time)
        avg_time = statistics.mean(read_times)
        print(f"\tСреднее время: {avg_time:.2f} мс")
        return {
            'avg_time_ms': avg_time,
            'min_time_ms': min(read_times),
            'max_time_ms': max(read_times),
            'queries_tested': len(read_times)
        }
    def test_concurrent(self):
        print("Тест конкурентных запросов:")
        import threading
        import queue
        results_queue = queue.Queue()
        def worker(worker_id):
            try:
                files = list(self.data_dir.glob("*.json"))
                if not files:
                    results_queue.put(100)
                    return
                start = time.perf_counter()
                for i in range(100):
                    file_idx = worker_id % len(files)
                    with open(files[file_idx], 'r', encoding='utf-8') as f:
                        data = json.load(f)
                        filtered = [t for t in data if t['month'] == (worker_id % 12 + 1)]
                end = time.perf_counter()
                avg_time = ((end - start) / 100) * 1000
                results_queue.put(avg_time)
            except Exception as e:
                print(f"  Worker {worker_id} ошибка: {e}")
                results_queue.put(100)
        threads = []
        for i in range(100):
            t = threading.Thread(target=worker, args=(i,))
            threads.append(t)
            t.start()
        for t in threads:
            t.join()
        times = []
        while not results_queue.empty():
            times.append(results_queue.get())
        if times:
            avg_time = statistics.mean(times)
            print(f"\tСреднее время при 100 параллельных чтениях: {avg_time:.2f} мс")
            print(f"\tВсего выполнено: {100*100} операций чтения")
            return {'avg_concurrent_time_ms': avg_time}
        return None

def run_benchmark():
    benchmark = Benchmark()
    all_results = {}
    print("\n1. Тестирование POSTGRESQL")
    pg_test = PostgresTest()
    if pg_test.conn:
        pg_results = {}
        insert_result = pg_test.test_insert(benchmark.test_data)
        if insert_result:
            pg_results['insert'] = insert_result
        select_result = pg_test.test_select()
        if select_result:
            pg_results['select'] = select_result
        concurrent_result = pg_test.test_concurrent()
        if concurrent_result:
            pg_results['concurrent'] = concurrent_result
        all_results['PostgreSQL'] = pg_results
        pg_test.conn.close()
    print("\n2. Тестирование SQLite")
    sqlite_test = SQLiteTest()
    if sqlite_test.conn:
        sqlite_results = {}
        insert_result = sqlite_test.test_insert(benchmark.test_data)
        if insert_result:
            sqlite_results['insert'] = insert_result
        select_result = sqlite_test.test_select()
        if select_result:
            sqlite_results['select'] = select_result
        concurrent_result = sqlite_test.test_concurrent()
        if concurrent_result:
            sqlite_results['concurrent'] = concurrent_result
        all_results['SQLite'] = sqlite_results
        sqlite_test.conn.close()
    print("\n3. Тестирование JSON файлов")
    json_test = JSONFileTest()
    json_results = {}
    insert_result = json_test.test_insert(benchmark.test_data)
    if insert_result:
        json_results['insert'] = insert_result
    select_result = json_test.test_select()
    if select_result:
        json_results['select'] = select_result
    concurrent_result = json_test.test_concurrent()
    if concurrent_result:
        json_results['concurrent'] = concurrent_result
    all_results['JSON_Files'] = json_results
    print("\nСводные результаты:")
    if not all_results:
        print("Нет результатов для отображения")
        return
    print(f"{'Хранилище':<15} {'Вставка (мс)':<15} {'Чтение (мс)':<15} {'Параллельно (мс)':<15}")
    for storage_name, results in all_results.items():
        insert_time = results.get('insert', {}).get('avg_time_ms', 'N/A')
        if insert_time != 'N/A':
            insert_str = f"{insert_time:.1f}"
        else:
            insert_str = "N/A"
        select_time = results.get('select', {}).get('avg_time_ms', 'N/A')
        if select_time != 'N/A':
            select_str = f"{select_time:.1f}"
        else:
            select_str = "N/A"
        concurrent_time = results.get('concurrent', {}).get('avg_concurrent_time_ms', 'N/A')
        if concurrent_time != 'N/A':
            concurrent_str = f"{concurrent_time:.1f}"
        else:
            concurrent_str = "N/A"
        print(f"{storage_name:<15} {insert_str:<15} {select_str:<15} {concurrent_str:<15}")

if __name__ == "__main__":
    try:
        run_benchmark()
    except Exception as e:
        print(f"Критическая ошибка: {e}")
        import traceback
        traceback.print_exc()