#ifndef JSON_FILE_MANAGER_H
#define JSON_FILE_MANAGER_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <vector>

struct Task_Data {
    int year;
    int month;
    int day;
    QString time;
    QString title;
    bool checked;
    int user_id;
    int task_id;

    QJsonObject to_json() const {
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

    static Task_Data from_json(const QJsonObject& obj) {
        Task_Data task;
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

class Json_File_Manager : public QObject {
    Q_OBJECT

public:
    explicit Json_File_Manager(QObject *parent = nullptr);
    bool load_tasks(const QString &file_path, std::vector<Task_Data> &tasks);
    bool save_tasks(const QString &file_path, const std::vector<Task_Data> &tasks);
    bool add_task(const QString &file_path, const Task_Data &task);
    bool update_task(const QString &file_path, const Task_Data &task);
    bool delete_task(const QString &file_path, const Task_Data &task);
    int get_next_task_id(const QString &file_path);

private:
    QString m_file_path;
};

#endif // JSON_FILE_MANAGER_H
