#include "working_with_files.h"
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

bool compareTasksByTime(const Working_With_Files::TaskData &a, const Working_With_Files::TaskData &b) {
    return QTime::fromString(a.time, "HH:mm") < QTime::fromString(b.time, "HH:mm");
}

Working_With_Files::Working_With_Files(QObject *parent) : QObject(parent) {}

bool Working_With_Files::write_all_tasks(const QString &filePath, const std::vector<TaskData> &tasks) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "workingwithfiles.cpp: couldn't open the file for writing:" << filePath;
        return false;
    }
    QJsonArray tasksArray;
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
        tasksArray.append(taskObj);
    }
    QJsonObject root;
    root["tasks"] = tasksArray;
    int nextId = 1;
    for (const auto &task : tasks) {
        if (task.task_id >= nextId) {
            nextId = task.task_id + 1;
        }
    }
    root["next_task_id"] = nextId;
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();
    return true;
}

bool Working_With_Files::load_tasks_from_file(const QString &filePath, std::vector<TaskData> &tasks) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "workingwithfiles.cpp: couldn't open the file for reading:" << filePath;
        return false;
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()) {
        qDebug() << "workingwithfiles.cpp: invalid JSON file";
        return false;
    }
    QJsonObject root = doc.object();
    if (!root.contains("tasks") || !root["tasks"].isArray()) {
        qDebug() << "workingwithfiles.cpp: no tasks array in JSON";
        return false;
    }
    tasks.clear();
    QJsonArray tasksArray = root["tasks"].toArray();
    for (const QJsonValue &value : tasksArray) {
        if (value.isObject()) {
            QJsonObject taskObj = value.toObject();
            TaskData task;
            task.year = taskObj["year"].toInt();
            task.month = taskObj["month"].toInt();
            task.day = taskObj["day"].toInt();
            task.time = taskObj["time"].toString();
            task.title = taskObj["title"].toString();
            task.checked = taskObj["checked"].toBool();
            task.user_id = taskObj["user_id"].toInt();
            task.task_id = taskObj["task_id"].toInt();
            tasks.push_back(task);
        }
    }
    std::sort(tasks.begin(), tasks.end(), compareTasksByTime);
    return true;
}

bool Working_With_Files::update_task_in_file(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!load_tasks_from_file(filePath, tasks)) {
        return false;
    }
    auto it = std::find_if(tasks.begin(), tasks.end(), [&task](const TaskData &t) {
        return t.task_id == task.task_id && t.user_id == task.user_id;
    });

    if (it != tasks.end()) {
        *it = task;
        return write_all_tasks(filePath, tasks);
    }
    qDebug() << "workingwithfiles.cpp: the task was not found for updating:" << task.task_id;
    return false;
}

bool Working_With_Files::delete_task_from_file(const QString &filePath, const TaskData &task) {
    std::vector<TaskData> tasks;
    if (!load_tasks_from_file(filePath, tasks)) {
        return false;
    }
    auto new_end = std::remove_if(tasks.begin(), tasks.end(), [&task](const TaskData &t) {
        return t.task_id == task.task_id && t.user_id == task.user_id;
    });
    if (new_end != tasks.end()) {
        tasks.erase(new_end, tasks.end());
        return write_all_tasks(filePath, tasks);
    }
    qDebug() << "workingwithfiles.cpp: the task was not found to be deleted:" << task.task_id;
    return false;
}

bool Working_With_Files::read_all_tasks(const QString &filePath, std::vector<QString> &lines) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "workingwithfiles.cpp: couldn't open the file for reading:" << filePath;
        return false;
    }
    QTextStream in(&file);
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
    tasks.push_back(task);
    return write_all_tasks(filePath, tasks);
}
