#ifndef JSON_FILE_MANAGER_H
#define JSON_FILE_MANAGER_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <vector>

struct TaskData {
    int year;
    int month;
    int day;
    QString time;
    QString title;
    bool checked;
    int user_id;
    int task_id;

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["year"] = year;
        obj["month"] = month;
        obj["day"] = day;
        obj["time"] = time;
        obj["title"] = title;
        obj["checked"] = checked;
        obj["user_id"] = user_id;
        obj["task_id"] = task_id;
        return obj;
    }

    static TaskData fromJson(const QJsonObject& obj) {
        TaskData task;
        task.year = obj["year"].toInt();
        task.month = obj["month"].toInt();
        task.day = obj["day"].toInt();
        task.time = obj["time"].toString();
        task.title = obj["title"].toString();
        task.checked = obj["checked"].toBool();
        task.user_id = obj["user_id"].toInt();
        task.task_id = obj["task_id"].toInt();
        return task;
    }
};

class JsonFileManager : public QObject {
    Q_OBJECT

public:
    explicit JsonFileManager(QObject *parent = nullptr);
    bool loadTasks(const QString &filePath, std::vector<TaskData> &tasks);
    bool saveTasks(const QString &filePath, const std::vector<TaskData> &tasks);
    bool addTask(const QString &filePath, const TaskData &task);
    bool updateTask(const QString &filePath, const TaskData &task);
    bool deleteTask(const QString &filePath, const TaskData &task);
    int getNextTaskId(const QString &filePath);

private:
    QString m_filePath;
};

#endif // JSON_FILE_MANAGER_H
