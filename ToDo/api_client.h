#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <vector>
#include <QString>

struct Task {
    QString title;
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    bool is_completed;
    int task_id;
    int local_id;

    Task() : year(0), month(0), day(0), hours(0), minutes(0), is_completed(false), task_id(0), local_id(0) {}

    QJsonObject to_json() const {
        QJsonObject obj;
        obj["title"] = title;
        obj["year"] = year;
        obj["month"] = month;
        obj["day"] = day;
        obj["hours"] = hours;
        obj["minutes"] = minutes;
        obj["is_completed"] = is_completed;
        obj["task_id"] = task_id;
        obj["local_id"] = local_id;
        return obj;
    }

    static Task from_json(const QJsonObject& json) {
        Task task;
        task.title = json["title"].toString();
        task.year = json["year"].toInt();
        task.month = json["month"].toInt();
        task.day = json["day"].toInt();
        task.hours = json["hours"].toInt();
        task.minutes = json["minutes"].toInt();
        task.is_completed = json["is_completed"].toBool();
        task.task_id = json.contains("task_id") ? json["task_id"].toInt() : 0;
        task.local_id = json.contains("local_id") ? json["local_id"].toInt() : 0;
        return task;
    }
};

class Api_Client : public QObject
{
    Q_OBJECT

public:
    explicit Api_Client(QObject *parent = nullptr);
    ~Api_Client();
    void set_base_url(const QString& url);
    void register_user(const QString& username, const QString& password);
    void login_user(const QString& username, const QString& password);
    void check_user_exists(const QString& username);
    void create_task(int user_id, const Task& task);
    void get_tasks(int user_id, int year = 0, int month = 0, int day = 0);
    void update_task(int user_id, int task_id, const Task& task);
    void delete_task(int user_id, int task_id);

signals:
    void login_success(int user_id);
    void login_error(const QString& error_message);
    void registration_success(int user_id);
    void registration_error(const QString& error_message);
    void user_checked(bool exists, const QString& message);
    void task_created(int task_id);
    void tasks_loaded(const std::vector<Task>& tasks);
    void task_updated(int task_id);
    void task_deleted(int task_id);
    void api_error(const QString& error_message);

private slots:
    void on_network_reply(QNetworkReply* reply);

private:
    QNetworkAccessManager* network_manager;
    QString base_url;
    void send_request(const QString& endpoint, const QJsonObject& data = QJsonObject(), const QString& method = "GET");
};

#endif // API_CLIENT_H
