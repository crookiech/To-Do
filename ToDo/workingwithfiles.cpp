#include "workingwithfiles.h"
#include <algorithm>

WorkingWithFiles::WorkingWithFiles(QObject *parent) : QObject(parent) {}

bool WorkingWithFiles::writeAllTasks(const QString &filePath, const std::vector<TaskData> &tasks) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "workingwithfiles.cpp: couldn't open the file for writing:" << filePath;
        return false;
    }
    QTextStream out(&file);
    for (const auto &task : tasks) {
        out << task.toString() << "\n";
    }
    file.close();
    return true;
}

bool WorkingWithFiles::loadTasksFromFile(const QString &filePath, std::vector<TaskData> &tasks)
{
    std::vector<QString> lines;
    if (!readAllTasks(filePath, lines)) {
        return false;
    }
    tasks.clear();
    for (const auto &line : lines) {
        QStringList parts = line.split("|");
        if (parts.size() == 4) {
            TaskData task;
            task.date = parts[0];
            task.title = parts[1];
            task.time = parts[2];
            task.checked = parts[3].toInt();
            tasks.push_back(task);
        }
    }
    return true;
}

bool WorkingWithFiles::updateTaskInFile(const QString &filePath, const TaskData &task)
{
    std::vector<TaskData> tasks;
    if (!loadTasksFromFile(filePath, tasks)) {
        return false;
    }
    auto it = std::find_if(tasks.begin(), tasks.end(), [&task](const TaskData &t) {
        return t.date == task.date && t.title == task.title && t.time == task.time;
    });
    if (it != tasks.end()) {
        *it = task;
        return writeAllTasks(filePath, tasks);
    }
    qDebug() << "workingwithfiles.cpp: the issue was not found for updating:" << task.date << task.title << task.time;
    return false;
}

bool WorkingWithFiles::deleteTaskFromFile(const QString &filePath, const TaskData &task)
{
    std::vector<TaskData> tasks;
    if (!loadTasksFromFile(filePath, tasks)) {
        return false;
    }
    auto new_end = std::remove_if(tasks.begin(), tasks.end(), [&task](const TaskData &t) {
        return t.date == task.date && t.title == task.title && t.time == task.time && t.checked == task.checked;
    });
    if (new_end != tasks.end()) {
        tasks.erase(new_end, tasks.end());
        return writeAllTasks(filePath, tasks);
    }
    qDebug() << "workingwithfiles.cpp: the issue was not found to be deleted:" << task.date << task.title << task.time;
    return false;
}

bool WorkingWithFiles::readAllTasks(const QString &filePath, std::vector<QString> &lines)
{
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
