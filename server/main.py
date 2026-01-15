from fastapi import FastAPI, HTTPException, Path, Query
from pydantic import BaseModel
from typing import List, Optional
import psycopg2
from psycopg2.extras import RealDictCursor

app = FastAPI(
    title="ToDo Server",
    description="Сервер для управления задачами ToDo приложения"
)

# Модели данных
class UserRegister(BaseModel):
    username: str
    password: str

class UserLogin(BaseModel):
    username: str
    password: str

class TaskCreate(BaseModel):
    title: str
    year: int
    month: int
    day: int
    hours: int
    minutes: int
    is_completed: Optional[bool] = False
    local_id: Optional[int] = None

class TaskUpdate(BaseModel):
    title: Optional[str] = None
    year: Optional[int] = None
    month: Optional[int] = None
    day: Optional[int] = None
    hours: Optional[int] = None
    minutes: Optional[int] = None
    is_completed: Optional[bool] = None

# Подключение к базе данных
def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="todo",
        user="postgres",
        password="123456789",
        cursor_factory=RealDictCursor,
        client_encoding='UTF8'
    )
    return conn

# Корневой endpoint
@app.get("/")
async def root():
    return {"message": "ToDo Server is running!", "status": "success"}

# Регистрация пользователя
@app.post("/api/register")
async def register(user_data: UserRegister):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        cursor.execute(
            "SELECT id FROM users WHERE username = %s",
            (user_data.username,)
        )
        if cursor.fetchone():
            return {
                "status": "error",
                "message": "Пользователь с таким именем уже существует"
            }
        cursor.execute(
            "INSERT INTO users (username, password) VALUES (%s, %s) RETURNING id",
            (user_data.username, user_data.password)
        )
        user_id = cursor.fetchone()['id']
        conn.commit()
        return {
            "status": "success", 
            "user_id": user_id, 
            "message": "Регистрация прошла успешно"
        }
    except Exception as e:
        conn.rollback()
        return {
            "status": "error",
            "message": f"Ошибка регистрации: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

@app.post("/api/login")
async def login(login_data: UserLogin):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        cursor.execute(
            "SELECT id, password FROM users WHERE username = %s",
            (login_data.username,)
        )
        user = cursor.fetchone()
        if not user:
            return {
                "status": "error",
                "message": "Пользователь не найден"
            }
        if user['password'] != login_data.password:
            return {
                "status": "error",
                "message": "Неверный пароль"
            }
        
        return {
            "status": "success", 
            "user_id": user['id'],
            "message": "Вход выполнен успешно"
        }
    except Exception as e:
        return {
            "status": "error",
            "message": f"Ошибка входа: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

# Проверка существования пользователя
@app.get("/api/check-user/{username}")
async def check_user(username: str):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        cursor.execute(
            "SELECT id FROM users WHERE username = %s",
            (username,)
        )
        user = cursor.fetchone()
        if user:
            return {
                "status": "success",
                "exists": True,
                "message": "Пользователь существует"
            }
        else:
            return {
                "status": "success",
                "exists": False,
                "message": "Пользователь не найден"
            }
    except Exception as e:
        return {
            "status": "error",
            "message": f"Ошибка проверки: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

# Создание задачи
@app.post("/api/tasks/{user_id}")
async def create_task(user_id: int, task_data: TaskCreate):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT id FROM users WHERE id = %s", (user_id,))
        if not cursor.fetchone():
            return {
                "status": "error",
                "message": "Пользователь не найден"
            }
        cursor.execute('''
                       INSERT INTO tasks (user_id, title, year, month, day, hours, minutes, is_completed)
                       VALUES (%s, %s, %s, %s, %s, %s, %s, %s) RETURNING id 
                       ''', (
            user_id, task_data.title, 
            task_data.year, task_data.month, task_data.day,
            task_data.hours, task_data.minutes,
            task_data.is_completed
        ))
        task_id = cursor.fetchone()['id']
        conn.commit()
        return {
            "status": "success", 
            "task_id": task_id,
            "local_id": task_data.local_id,
            "message": "Задача создана успешно"
        }
    except Exception as e:
        conn.rollback()
        return {
            "status": "error",
            "message": f"Ошибка создания задачи: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

# Получение задач пользователя
@app.get("/api/tasks/{user_id}")
async def get_user_tasks(
    user_id: int,
    year: Optional[int] = Query(None, gt=0),
    month: Optional[int] = Query(None, gt=0, le=12),
    day: Optional[int] = Query(None, gt=0, le=31)
):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT id FROM users WHERE id = %s", (user_id,))
        if not cursor.fetchone():
            return {
                "status": "error",
                "message": "Пользователь не найден"
            }
        sql = '''
        SELECT id, title, year, month, day, hours, minutes, is_completed
        FROM tasks
        WHERE user_id = %s
        '''
        params = [user_id]
        if year and month and day:
            sql += " AND year = %s AND month = %s AND day = %s"
            params.extend([year, month, day])
        elif year and month:
            sql += " AND year = %s AND month = %s"
            params.extend([year, month])
        elif year:
            sql += " AND year = %s"
            params.append(year)
        sql += " ORDER BY year, month, day, hours, minutes"
        cursor.execute(sql, params)
        tasks = cursor.fetchall()
        return {
            "status": "success",
            "user_id": user_id,
            "tasks": tasks,
            "count": len(tasks)
        }
    except Exception as e:
        return {
            "status": "error",
            "message": f"Ошибка получения задач: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

# Обновление задачи
@app.put("/api/tasks/{user_id}/{task_id}")
async def update_task(user_id: int, task_id: int, task_data: TaskUpdate):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        print(f"\n=== PUT REQUEST START ===")
        print(f"Updating task {task_id} for user {user_id}")
        print(f"Update data received: {task_data.dict(exclude_unset=True)}")
        cursor.execute(
            "SELECT id, title, year, month, day, hours, minutes, is_completed FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        existing_task = cursor.fetchone()
        if not existing_task:
            print(f"Task {task_id} not found for user {user_id}")
            return {
                "status": "error",
                "message": "Задача не найдена"
            }
        print(f"Existing task before update: {existing_task}")
        update_fields = []
        values = []
        fields_to_update = task_data.dict(exclude_unset=True)
        print(f"Fields to update: {fields_to_update}")
        if "title" in fields_to_update:
            update_fields.append("title = %s")
            values.append(task_data.title)
            print(f"  - Title: {task_data.title} (was: {existing_task['title']})")
        if "year" in fields_to_update:
            update_fields.append("year = %s")
            values.append(task_data.year)
            print(f"  - Year: {task_data.year} (was: {existing_task['year']})")
        if "month" in fields_to_update:
            update_fields.append("month = %s")
            values.append(task_data.month)
            print(f"  - Month: {task_data.month} (was: {existing_task['month']})")
        if "day" in fields_to_update:
            update_fields.append("day = %s")
            values.append(task_data.day)
            print(f"  - Day: {task_data.day} (was: {existing_task['day']})")
        if "hours" in fields_to_update:
            update_fields.append("hours = %s")
            values.append(task_data.hours)
            print(f"  - Hours: {task_data.hours} (was: {existing_task['hours']})")
        if "minutes" in fields_to_update:
            update_fields.append("minutes = %s")
            values.append(task_data.minutes)
            print(f"  - Minutes: {task_data.minutes} (was: {existing_task['minutes']})")
        if "is_completed" in fields_to_update:
            update_fields.append("is_completed = %s")
            values.append(task_data.is_completed)
            print(f"  - Completed: {task_data.is_completed} (was: {existing_task['is_completed']})")
        if not update_fields:
            print("No fields to update")
            return {
                "status": "error",
                "message": "Нет полей для обновления"
            }
        values.extend([task_id, user_id])
        sql = f"UPDATE tasks SET {', '.join(update_fields)} WHERE id = %s AND user_id = %s"
        print(f"SQL: {sql}")
        print(f"Values: {values}")
        cursor.execute(sql, values)
        conn.commit()
        cursor.execute(
            "SELECT id, title, year, month, day, hours, minutes, is_completed FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        updated_task = cursor.fetchone()
        print(f"Task after update: {updated_task}")
        print(f"=== PUT REQUEST END ===\n")
        return {
            "status": "success", 
            "task_id": task_id,
            "message": f"Задача {task_id} обновлена успешно"
        }
    except Exception as e:
        conn.rollback()
        print(f"Error updating task: {str(e)}")
        import traceback
        traceback.print_exc()
        return {
            "status": "error",
            "message": f"Ошибка обновления задачи: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

# Удаление задачи
@app.delete("/api/tasks/{user_id}/{task_id}")
async def delete_task(user_id: int, task_id: int):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        print(f"DELETE request: user_id={user_id}, task_id={task_id}")
        cursor.execute(
            "SELECT id FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        task = cursor.fetchone()
        if not task:
            print(f"Task {task_id} not found for user {user_id}")
            return {
                "status": "error",
                "message": "Задача не найдена"
            }
        print(f"Deleting task {task_id} for user {user_id}")
        cursor.execute(
            "DELETE FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        conn.commit()
        print(f"Task {task_id} deleted successfully")
        return {
            "status": "success", 
            "message": f"Задача {task_id} удалена успешно"
        }
    except Exception as e:
        conn.rollback()
        print(f"Error deleting task: {str(e)}")
        return {
            "status": "error",
            "message": f"Ошибка удаления задачи: {str(e)}"
        }
    finally:
        cursor.close()
        conn.close()

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000, reload=True)