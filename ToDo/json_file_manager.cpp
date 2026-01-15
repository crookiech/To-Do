#include "json_file_manager.h"

Json_File_Manager::Json_File_Manager(QObject *parent) : QObject(parent) {}

bool Json_File_Manager::load_tasks(const QString &file_path, std::vector<Task_Data> &tasks) {
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QByteArray json_data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(json_data);
    if (doc.isNull() || !doc.isObject()) {
        return false;
    }
    QJsonObject root = doc.object();
    if (!root.contains("tasks") || !root["tasks"].isArray()) {
        return false;
    }
    QJsonArray tasks_array = root["tasks"].toArray();
    tasks.clear();
    for (const QJsonValue &value : tasks_array) {
        if (value.isObject()) {
            tasks.push_back(Task_Data::from_json(value.toObject()));
        }
    }
    return true;
}

bool Json_File_Manager::save_tasks(const QString &file_path, const std::vector<Task_Data> &tasks) {
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }
    QJsonArray tasks_array;
    for (const Task_Data &task : tasks) {
        tasks_array.append(task.to_json());
    }
    QJsonObject root;
    root["tasks"] = tasks_array;
    root["next_task_id"] = get_next_task_id(file_path);
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    return true;
}

bool Json_File_Manager::add_task(const QString &file_path, const Task_Data &task) {
    std::vector<Task_Data> tasks;
    if (!load_tasks(file_path, tasks)) {
        tasks.clear();
    }
    tasks.push_back(task);
    return save_tasks(file_path, tasks);
}

bool Json_File_Manager::update_task(const QString &file_path, const Task_Data &task) {
    std::vector<Task_Data> tasks;
    if (!load_tasks(file_path, tasks)) {
        return false;
    }
    for (auto &t : tasks) {
        if (t.task_id == task.task_id && t.user_id == task.user_id) {
            t = task;
            return save_tasks(file_path, tasks);
        }
    }
    return false;
}

bool Json_File_Manager::delete_task(const QString &file_path, const Task_Data &task) {
    std::vector<Task_Data> tasks;
    if (!load_tasks(file_path, tasks)) {
        return false;
    }
    auto it = std::remove_if(tasks.begin(), tasks.end(),
        [&task](const Task_Data &t) {
            return t.task_id == task.task_id && t.user_id == task.user_id;
        });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return save_tasks(file_path, tasks);
    }
    return false;
}

int Json_File_Manager::get_next_task_id(const QString &file_path) {
    std::vector<Task_Data> tasks;
    if (!load_tasks(file_path, tasks)) {
        return 1;
    }
    int maxId = 0;
    for (const Task_Data &task : tasks) {
        if (task.task_id > maxId) {
            maxId = task.task_id;
        }
    }
    return maxId + 1;
}
