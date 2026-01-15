#include "api_client.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>

Api_Client::Api_Client(QObject *parent) :
    QObject(parent),
    network_manager(new QNetworkAccessManager(this))
{
    connect(network_manager, &QNetworkAccessManager::finished, this, &Api_Client::on_network_reply);
    base_url = "http://localhost:8000";
}

Api_Client::~Api_Client()
{
    delete network_manager;
}

void Api_Client::set_base_url(const QString& url)
{
    base_url = url;
}

void Api_Client::send_request(const QString& endpoint, const QJsonObject& data, const QString& method)
{
    QUrl url(base_url + endpoint);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (method == "POST" || method == "PUT") {
        QByteArray json_data = QJsonDocument(data).toJson();
        if (method == "POST") {
            network_manager->post(request, json_data);
        } else {
            network_manager->put(request, json_data);
        }
    }
    else if (method == "GET") {
        QUrlQuery query;
        for (auto it = data.begin(); it != data.end(); ++it) {
            query.addQueryItem(it.key(), it.value().toString());
        }
        if (!query.isEmpty()) {
            url.setQuery(query);
            request.setUrl(url);
        }
        network_manager->get(request);
    }
    else if (method == "DELETE") {
        network_manager->deleteResource(request);
    }
}

void Api_Client::register_user(const QString& username, const QString& password)
{
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    send_request("/api/register", data, "POST");
}

void Api_Client::login_user(const QString& username, const QString& password)
{
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    send_request("/api/login", data, "POST");
}

void Api_Client::create_task(int user_id, const Task& task)
{
    QJsonObject data = task.to_json();
    send_request(QString("/api/tasks/%1").arg(user_id), data, "POST");
}

void Api_Client::get_tasks(int user_id, int year, int month, int day)
{
    QJsonObject data;
    if (year > 0) data["year"] = year;
    if (month > 0) data["month"] = month;
    if (day > 0) data["day"] = day;
    send_request(QString("/api/tasks/%1").arg(user_id), data, "GET");
}

void Api_Client::update_task(int user_id, int task_id, const Task& task)
{
    QJsonObject data;
    data["title"] = task.title;
    data["year"] = task.year;
    data["month"] = task.month;
    data["day"] = task.day;
    data["hours"] = task.hours;
    data["minutes"] = task.minutes;
    data["is_completed"] = task.is_completed;
    send_request(QString("/api/tasks/%1/%2").arg(user_id).arg(task_id), data, "PUT");
}

void Api_Client::delete_task(int user_id, int task_id)
{
    send_request(QString("/api/tasks/%1/%2").arg(user_id).arg(task_id), QJsonObject(), "DELETE");
}

void Api_Client::check_user_exists(const QString& username)
{
    send_request(QString("/api/check-user/%1").arg(username), QJsonObject(), "GET");
}

void Api_Client::on_network_reply(QNetworkReply* reply)
{
    if (!reply) return;
    QByteArray response_data = reply->readAll();
    QString endpoint = reply->url().path();
    QString method = reply->operation() == QNetworkAccessManager::GetOperation ? "GET" :
                     reply->operation() == QNetworkAccessManager::PostOperation ? "POST" :
                     reply->operation() == QNetworkAccessManager::PutOperation ? "PUT" :
                     reply->operation() == QNetworkAccessManager::DeleteOperation ? "DELETE" : "Unknown";
    if (reply->error() != QNetworkReply::NoError) {
        QString error_Msg = reply->errorString();
        if (reply->error() == QNetworkReply::ConnectionRefusedError ||
            reply->error() == QNetworkReply::TimeoutError ||
            reply->error() == QNetworkReply::HostNotFoundError) {
            error_Msg = "Сервер недоступен. Работаем в оффлайн-режиме.";
        }
        emit api_error(error_Msg);
        reply->deleteLater();
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(response_data);
    if (method == "DELETE" && response_data.isEmpty()) {
        QStringList parts = endpoint.split("/");
        if (parts.size() >= 5) {
            bool ok;
            int task_id = parts[4].toInt(&ok);
            if (ok) {
                emit task_deleted(task_id);
            }
        }
        reply->deleteLater();
        return;
    }
    if (doc.isNull() || !doc.isObject()) {
        emit api_error("Invalid JSON response from server");
        reply->deleteLater();
        return;
    }
    QJsonObject json = doc.object();
    QString status = json["status"].toString();
    QString message = json["message"].toString();
    if (method == "DELETE" && endpoint.startsWith("/api/tasks/")) {
        QStringList parts = endpoint.split("/");
        if (parts.size() >= 5) {
            bool ok;
            int task_id = parts[4].toInt(&ok);
            if (ok) {
                if (status == "success") {
                    emit task_deleted(task_id);
                } else {
                    emit api_error(message);
                }
            }
        }
        reply->deleteLater();
        return;
    }
    if (endpoint.startsWith("/api/tasks/") && method == "PUT") {
        QStringList parts = endpoint.split("/");
        if (parts.size() >= 5) {
            bool ok;
            int task_id = parts[4].toInt(&ok);

            if (ok) {
                if (status == "success") {
                    emit task_updated(task_id);
                } else {
                    emit api_error(message);
                }
            }
        }
    }
    if (endpoint.startsWith("/api/check-user/")) {
        if (status == "success") {
            bool exists = json["exists"].toBool();
            emit user_checked(exists, message);
        } else {
            emit api_error(message);
        }
        reply->deleteLater();
        return;
    }
    if (endpoint == "/api/register") {
        if (status == "success") {
            int user_id = json["user_id"].toInt();
            emit registration_success(user_id);
        } else {
            emit registration_error(message);
        }
        reply->deleteLater();
        return;
    }
    if (endpoint == "/api/login") {
        if (status == "success") {
            int user_id = json["user_id"].toInt();
            emit login_success(user_id);
        } else {
            emit login_error(message);
        }
        reply->deleteLater();
        return;
    }
    if (endpoint.startsWith("/api/tasks/")) {
        QStringList parts = endpoint.split("/");
        if (parts.size() >= 4) {
            if (status == "success") {
                if (method == "GET") {
                    std::vector<Task> tasks;
                    if (json.contains("tasks") && json["tasks"].isArray()) {
                        QJsonArray tasks_array = json["tasks"].toArray();
                        for (const QJsonValue& value : tasks_array) {
                            tasks.push_back(Task::from_json(value.toObject()));
                        }
                    }
                    emit tasks_loaded(tasks);
                }
                else if (method == "POST") {
                    int task_id = json["task_id"].toInt();
                    emit task_created(task_id);
                }
                else if (method == "PUT") {
                    int task_id = parts.size() >= 5 ? parts[4].toInt() : 0;
                    emit task_updated(task_id);
                }
            } else {
                emit api_error(message);
            }
        }
    }
    reply->deleteLater();
}
