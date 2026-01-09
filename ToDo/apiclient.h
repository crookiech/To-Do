#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <vector>

class ApiClient : public QObject
{
    Q_OBJECT

public:
    struct Task {
        int id;
        QString title;
        int year;
        int month;
        int day;
        int hours;
        int minutes;
        bool is_completed;

        QJsonObject toJson() const {
            QJsonObject obj;
            obj["id"] = id;
            obj["title"] = title;
            obj["year"] = year;
            obj["month"] = month;
            obj["day"] = day;
            obj["hours"] = hours;
            obj["minutes"] = minutes;
            obj["is_completed"] = is_completed;
            return obj;
        }

        static Task fromJson(const QJsonObject& json) {
            Task task;
            task.id = json["id"].toInt();
            task.title = json["title"].toString();
            task.year = json["year"].toInt();
            task.month = json["month"].toInt();
            task.day = json["day"].toInt();
            task.hours = json["hours"].toInt();
            task.minutes = json["minutes"].toInt();
            task.is_completed = json["is_completed"].toBool();
            return task;
        }
    };

    explicit ApiClient(QObject *parent = nullptr);
    ~ApiClient();

    void setBaseUrl(const QString& url);
    void registerUser(const QString& username, const QString& password);
    void loginUser(const QString& username, const QString& password);
    void checkUserExists(const QString& username);
    void createTask(int user_id, const Task& task);
    void getTasks(int user_id, int year = 0, int month = 0, int day = 0);
    void updateTask(int user_id, int task_id, const Task& task);
    void deleteTask(int user_id, int task_id);

signals:
    void registrationSuccess(int user_id);
    void registrationError(const QString& error);
    void loginSuccess(int user_id);
    void loginError(const QString& error);
    void userChecked(bool exists, const QString& message);
    void tasksLoaded(const std::vector<Task>& tasks);
    void taskCreated(int task_id);
    void taskUpdated(int task_id);
    void taskDeleted(int task_id);
    void apiError(const QString& error);

private slots:
    void onNetworkReply(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;
    QString baseUrl;
    void sendRequest(const QString& endpoint, const QJsonObject& data, const QString& method = "POST");
};

#endif // APICLIENT_H
