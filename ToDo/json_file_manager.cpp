#include "json_file_manager.h"

JsonFileManager::JsonFileManager(QObject *parent) : QObject(parent) {}

bool JsonFileManager::loadTasks(const QString &filePath, std::vector<TaskData> &tasks) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file for reading:" << filePath;
        return false;
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isObject()) {
        qDebug() << "Invalid JSON document";
        return false;
    }
    QJsonObject root = doc.object();
    if (!root.contains("tasks") || !root["tasks"].isArray()) {
        qDebug() << "No tasks array in JSON";
        return false;
    }
    QJsonArray tasksArray = root["tasks"].toArray();
    tasks.clear();
    for (const QJsonValue &value : tasksArray) {
        if (value.isObject()) {
            tasks.push_back(TaskData::fromJson(value.toObject()));
        }
    }
    return true;
}

bool JsonFileManager::saveTasks(const QString &filePath, const std::vector<TaskData> &tasks) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open JSON file for writing:" << filePath;
        return false;
    }
    QJsonArray tasksArray;
    for (const TaskData &task : tasks) {
        tasksArray.append(task.toJson());
    }
    QJsonObject root;
    root["tasks"] = tasksArray;
    root["next_task_id"] = getNextTaskId(filePath);
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    return true;
}

bool JsonFileManager::addTask(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!loadTasks(filePath, tasks)) {
        tasks.clear();
    }
    tasks.push_back(task);
    return saveTasks(filePath, tasks);
}

bool JsonFileManager::updateTask(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!loadTasks(filePath, tasks)) {
        return false;
    }
    for (auto &t : tasks) {
        if (t.task_id == task.task_id && t.user_id == task.user_id) {
            t = task;
            return saveTasks(filePath, tasks);
        }
    }
    qDebug() << "Task not found for update, ID:" << task.task_id;
    return false;
}

bool JsonFileManager::deleteTask(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!loadTasks(filePath, tasks)) {
        return false;
    }
    auto it = std::remove_if(tasks.begin(), tasks.end(),
        [&task](const TaskData &t) {
            return t.task_id == task.task_id && t.user_id == task.user_id;
        });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return saveTasks(filePath, tasks);
    }
    qDebug() << "Task not found for deletion, ID:" << task.task_id;
    return false;
}

int JsonFileManager::getNextTaskId(const QString &filePath) {
    std::vector<TaskData> tasks;
    if (!loadTasks(filePath, tasks)) {
        return 1;
    }
    int maxId = 0;
    for (const TaskData &task : tasks) {
        if (task.task_id > maxId) {
            maxId = task.task_id;
        }
    }
    return maxId + 1;
}
