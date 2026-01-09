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

# Проверка существования пользователя (новый endpoint)
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
        # Проверяем существование пользователя
        cursor.execute("SELECT id FROM users WHERE id = %s", (user_id,))
        if not cursor.fetchone():
            return {
                "status": "error",
                "message": "Пользователь не найден"
            }
        
        # Создание задачи
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
        # Проверяем существование пользователя
        cursor.execute("SELECT id FROM users WHERE id = %s", (user_id,))
        if not cursor.fetchone():
            return {
                "status": "error",
                "message": "Пользователь не найден"
            }
        
        sql = '''
            SELECT id, title, year, month, day, 
                   hours, minutes, is_completed
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
        # Проверяем, что задача существует и принадлежит пользователю
        cursor.execute(
            "SELECT id FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        if not cursor.fetchone():
            return {
                "status": "error",
                "message": "Задача не найдена"
            }
        
        # Формируем запрос на обновление
        update_fields = []
        values = []
        
        if task_data.title is not None:
            update_fields.append("title = %s")
            values.append(task_data.title)
        if task_data.year is not None:
            update_fields.append("year = %s")
            values.append(task_data.year)
        if task_data.month is not None:
            update_fields.append("month = %s")
            values.append(task_data.month)
        if task_data.day is not None:
            update_fields.append("day = %s")
            values.append(task_data.day)
        if task_data.hours is not None:
            update_fields.append("hours = %s")
            values.append(task_data.hours)
        if task_data.minutes is not None:
            update_fields.append("minutes = %s")
            values.append(task_data.minutes)
        if task_data.is_completed is not None:
            update_fields.append("is_completed = %s")
            values.append(task_data.is_completed)
        
        if not update_fields:
            return {
                "status": "error",
                "message": "Нет полей для обновления"
            }
        
        values.extend([task_id, user_id])
        sql = f"UPDATE tasks SET {', '.join(update_fields)} WHERE id = %s AND user_id = %s"
        cursor.execute(sql, values)
        conn.commit()
        
        return {
            "status": "success", 
            "message": f"Задача {task_id} обновлена успешно"
        }
    except Exception as e:
        conn.rollback()
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
        # Проверяем существование задачи
        cursor.execute(
            "SELECT id FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        if not cursor.fetchone():
            return {
                "status": "error",
                "message": "Задача не найдена"
            }
        
        # Удаляем задачу
        cursor.execute(
            "DELETE FROM tasks WHERE id = %s AND user_id = %s", 
            (task_id, user_id)
        )
        conn.commit()
        
        return {
            "status": "success", 
            "message": f"Задача {task_id} удалена успешно"
        }
    except Exception as e:
        conn.rollback()
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