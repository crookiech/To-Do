#ifndef WORKINGWITHFILES_H
#define WORKINGWITHFILES_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <vector>

class WorkingWithFiles : public QObject
{
    Q_OBJECT
public:
    explicit WorkingWithFiles(QObject *parent = nullptr);

    struct TaskData {
        QString date;
        QString title;
        QString time;
        int checked;
        QString toString() const {return QString("%1|%2|%3|%4").arg(date).arg(title).arg(time).arg(checked);}
    };
    bool loadTasksFromFile(const QString &filePath, std::vector<TaskData> &tasks);
    bool updateTaskInFile(const QString &filePath, const TaskData &task);
    bool deleteTaskFromFile(const QString &filePath, const TaskData &task);
    bool writeAllTasks(const QString &filePath, const std::vector<TaskData> &tasks);

private:
    bool readAllTasks(const QString &filePath, std::vector<QString> &lines);
};

#endif // WORKINGWITHFILES_H
