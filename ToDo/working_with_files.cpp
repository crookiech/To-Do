#include "working_with_files.h"
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTime>
#include <QDir>

Working_With_Files::TaskData::TaskData() :
    year(0), month(0), day(0),
    checked(false), user_id(0),
    task_id(0), local_id(0) {}

Working_With_Files::Working_With_Files(QObject *parent) : QObject(parent) {}

bool Working_With_Files::write_all_tasks(const QString &filePath, const std::vector<TaskData> &tasks) {
    QFile file(filePath);
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }
    QJsonArray tasksArray;
    int maxLocalId = 0;
    int maxServerId = 0;
    for (const auto &task : tasks) {
        QJsonObject taskObj;
        taskObj["year"] = task.year;
        taskObj["month"] = task.month;
        taskObj["day"] = task.day;
        taskObj["time"] = task.time;
        taskObj["title"] = task.title;
        taskObj["checked"] = task.checked;
        taskObj["user_id"] = task.user_id;
        taskObj["task_id"] = task.task_id;
        taskObj["local_id"] = task.local_id;
        if (task.local_id > maxLocalId) {
            maxLocalId = task.local_id;
        }
        if (task.task_id > maxServerId) {
            maxServerId = task.task_id;
        }
        tasksArray.append(taskObj);
    }
    QJsonObject root;
    root["tasks"] = tasksArray;
    root["next_local_id"] = maxLocalId + 1;
    root["next_task_id"] = maxServerId + 1;
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();
    emit tasks_updated();
    return true;
}

bool Working_With_Files::load_tasks_from_file(const QString &filePath, std::vector<TaskData> &tasks) {
    QFile file(filePath);
    if (!file.exists()) {
        if (!write_all_tasks(filePath, std::vector<TaskData>())) {
            return false;
        }
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QByteArray jsonData = file.readAll();
    file.close();
    if (jsonData.isEmpty()) {
        tasks.clear();
        return true;
    }
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()) {
        return false;
    }
    QJsonObject root = doc.object();
    if (!root.contains("tasks") || !root["tasks"].isArray()) {
        tasks.clear();
        return true;
    }
    tasks.clear();
    QJsonArray tasksArray = root["tasks"].toArray();
    for (const QJsonValue &value : tasksArray) {
        if (value.isObject()) {
            QJsonObject taskObj = value.toObject();
            TaskData task;
            if (taskObj.contains("year")) task.year = taskObj["year"].toInt();
            if (taskObj.contains("month")) task.month = taskObj["month"].toInt();
            if (taskObj.contains("day")) task.day = taskObj["day"].toInt();
            if (taskObj.contains("time")) task.time = taskObj["time"].toString();
            if (taskObj.contains("title")) task.title = taskObj["title"].toString();
            if (taskObj.contains("checked")) task.checked = taskObj["checked"].toBool();
            if (taskObj.contains("user_id")) task.user_id = taskObj["user_id"].toInt();
            if (taskObj.contains("task_id")) task.task_id = taskObj["task_id"].toInt();
            if (taskObj.contains("local_id")) task.local_id = taskObj["local_id"].toInt();
            if (task.local_id == 0 && task.task_id > 0) {
                task.local_id = task.task_id;
            }
            tasks.push_back(task);
        }
    }
    std::sort(tasks.begin(), tasks.end(),
        [](const TaskData &a, const TaskData &b) {
            return QTime::fromString(a.time, "HH:mm") < QTime::fromString(b.time, "HH:mm");
        }
    );
    return true;
}

bool Working_With_Files::update_task_in_file(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!load_tasks_from_file(filePath, tasks)) {
        return false;
    }
    bool found = false;
    for (auto &t : tasks) {
        if (task.task_id > 0) {
            if (t.task_id == task.task_id && t.user_id == task.user_id) {
                t = task;
                found = true;
                break;
            }
        } else if (task.local_id > 0) {
            if (t.local_id == task.local_id && t.user_id == task.user_id) {
                t = task;
                found = true;
                break;
            }
        }
    }
    if (!found) {
        return false;
    }
    return write_all_tasks(filePath, tasks);
}

bool Working_With_Files::delete_task_from_file(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!load_tasks_from_file(filePath, tasks)) {
        return false;
    }
    auto new_end = std::remove_if(tasks.begin(), tasks.end(),
        [&task](const TaskData &t) {
            if (task.task_id > 0) {
                return t.task_id == task.task_id && t.user_id == task.user_id;
            } else if (task.local_id > 0) {
                return t.local_id == task.local_id && t.user_id == task.user_id;
            }
            return false;
        }
    );
    if (new_end != tasks.end()) {
        tasks.erase(new_end, tasks.end());
        bool result = write_all_tasks(filePath, tasks);
        if (result) {
            emit tasks_updated();
        }
        return result;
    }
    return false;
}

bool Working_With_Files::read_all_tasks(const QString &filePath, std::vector<QString> &lines) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    lines.clear();
    while (!in.atEnd()) {
        lines.push_back(in.readLine());
    }
    file.close();
    return true;
}

bool Working_With_Files::add_task_to_json(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!load_tasks_from_file(filePath, tasks)) {
        tasks.clear();
    }
    TaskData newTask = task;
    if (newTask.local_id == 0) {
        newTask.local_id = get_next_local_id(filePath);
    }
    tasks.push_back(newTask);
    bool result = write_all_tasks(filePath, tasks);
    if (result) {
        emit tasks_updated();
    }
    return result;
}

int Working_With_Files::get_next_local_id(const QString &filePath) {
    std::vector<TaskData> tasks;
    if (!load_tasks_from_file(filePath, tasks)) {
        return 1;
    }
    int maxLocalId = 0;
    for (const auto &task : tasks) {
        if (task.local_id > maxLocalId) {
            maxLocalId = task.local_id;
        }
    }
    return maxLocalId + 1;
}
