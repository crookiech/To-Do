#ifndef WORKING_WITH_FILES_H
#define WORKING_WITH_FILES_H

#include <QObject>
#include <QString>
#include <vector>

class Working_With_Files : public QObject
{
    Q_OBJECT

public:
    struct TaskData {
        int year;
        int month;
        int day;
        QString time;
        QString title;
        bool checked;
        int user_id;
        int task_id;
        int local_id;

        TaskData();
    };

    explicit Working_With_Files(QObject *parent = nullptr);
    bool write_all_tasks(const QString &filePath, const std::vector<TaskData> &tasks);
    bool load_tasks_from_file(const QString &filePath, std::vector<TaskData> &tasks);
    bool update_task_in_file(const QString &filePath, const TaskData &task);
    bool delete_task_from_file(const QString &filePath, const TaskData &task);
    bool read_all_tasks(const QString &filePath, std::vector<QString> &lines);
    bool add_task_to_json(const QString &filePath, const TaskData &task);
    int get_next_local_id(const QString &filePath);

signals:
    void tasks_updated();
};

#endif // WORKING_WITH_FILES_H
