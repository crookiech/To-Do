#include "globals.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QApplication>

QString path_to_tasks;
int current_user_id = -1;
QString current_username = "";
bool is_online_mode = true;

void initialize_paths()
{
    QString app_dir = QCoreApplication::applicationDirPath();
    path_to_tasks = app_dir + "/tasks.json";
    qDebug() << "Tasks file path:" << path_to_tasks;
    QFile file(path_to_tasks);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QJsonObject root;
            QJsonArray tasks_array;
            root["tasks"] = tasks_array;
            root["next_local_id"] = 1;
            root["next_task_id"] = 1;
            QJsonDocument doc(root);
            file.write(doc.toJson());
            file.close();
        }
    }
}
