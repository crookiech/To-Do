#include "apiclient.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

ApiClient::ApiClient(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &ApiClient::onNetworkReply);
    baseUrl = "http://localhost:8000";
}

ApiClient::~ApiClient()
{
    delete networkManager;
}

void ApiClient::setBaseUrl(const QString& url)
{
    baseUrl = url;
}

void ApiClient::sendRequest(const QString& endpoint, const QJsonObject& data, const QString& method)
{
    QUrl url(baseUrl + endpoint);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (method == "POST" || method == "PUT") {
        QByteArray jsonData = QJsonDocument(data).toJson();
        if (method == "POST") {
            networkManager->post(request, jsonData);
        } else {
            networkManager->put(request, jsonData);
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
        networkManager->get(request);
    }
    else if (method == "DELETE") {
        networkManager->deleteResource(request);
    }
}

void ApiClient::registerUser(const QString& username, const QString& password)
{
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    sendRequest("/api/register", data, "POST");
}

void ApiClient::loginUser(const QString& username, const QString& password)
{
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    sendRequest("/api/login", data, "POST");
}

void ApiClient::createTask(int user_id, const Task& task)
{
    QJsonObject data;
    data["title"] = task.title;
    data["year"] = task.year;
    data["month"] = task.month;
    data["day"] = task.day;
    data["hours"] = task.hours;
    data["minutes"] = task.minutes;
    data["is_completed"] = task.is_completed;
    sendRequest(QString("/api/tasks/%1").arg(user_id), data, "POST");
}

void ApiClient::getTasks(int user_id, int year, int month, int day)
{
    QJsonObject data;
    if (year > 0) data["year"] = year;
    if (month > 0) data["month"] = month;
    if (day > 0) data["day"] = day;
    sendRequest(QString("/api/tasks/%1").arg(user_id), data, "GET");
}

void ApiClient::updateTask(int user_id, int task_id, const Task& task)
{
    QJsonObject data = task.toJson();
    sendRequest(QString("/api/tasks/%1/%2").arg(user_id).arg(task_id), data, "PUT");
}

void ApiClient::deleteTask(int user_id, int task_id)
{
    sendRequest(QString("/api/tasks/%1/%2").arg(user_id).arg(task_id), QJsonObject(), "DELETE");
}

void ApiClient::checkUserExists(const QString& username)
{
    sendRequest(QString("/api/check-user/%1").arg(username), QJsonObject(), "GET");
}

void ApiClient::onNetworkReply(QNetworkReply* reply)
{
    if (!reply) return;
    QByteArray responseData = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() != QNetworkReply::NoError) {
        emit apiError(reply->errorString());
        reply->deleteLater();
        return;
    }
    reply->deleteLater();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    if (doc.isNull() || !doc.isObject()) {
        emit apiError("Invalid JSON response");
        return;
    }
    QJsonObject json = doc.object();
    QString status = json["status"].toString();
    QString message = json["message"].toString();
    QString endpoint = reply->url().path();
    if (endpoint.startsWith("/api/check-user/")) {
        if (status == "success") {
            bool exists = json["exists"].toBool();
            emit userChecked(exists, message);
        } else {
            emit apiError(message);
        }
        return;
    }
    if (endpoint == "/api/register") {
        if (status == "success") {
            int user_id = json["user_id"].toInt();
            emit registrationSuccess(user_id);
        } else {
            emit registrationError(message);
        }
        return;
    }
    if (endpoint == "/api/login") {
        if (status == "success") {
            int user_id = json["user_id"].toInt();
            emit loginSuccess(user_id);
        } else {
            emit loginError(message);
        }
        return;
    }
    if (endpoint.startsWith("/api/tasks/")) {
        QStringList parts = endpoint.split("/");
        if (parts.size() >= 4) {
            int user_id = parts[3].toInt();
            if (parts.size() == 4) {
                if (status == "success") {
                    if (reply->operation() == QNetworkAccessManager::GetOperation) {
                        std::vector<Task> tasks;
                        QJsonArray tasksArray = json["tasks"].toArray();
                        for (const QJsonValue& value : tasksArray) {
                            tasks.push_back(Task::fromJson(value.toObject()));
                        }
                        emit tasksLoaded(tasks);
                    }
                    else if (reply->operation() == QNetworkAccessManager::PostOperation) {
                        int task_id = json["task_id"].toInt();
                        emit taskCreated(task_id);
                    }
                } else {
                    emit apiError(message);
                }
            }
            else if (parts.size() == 5) {
                if (status == "success") {
                    int task_id = parts[4].toInt();
                    if (reply->operation() == QNetworkAccessManager::PutOperation) {
                        emit taskUpdated(task_id);
                    }
                    else if (reply->operation() == QNetworkAccessManager::DeleteOperation) {
                        emit taskDeleted(task_id);
                    }
                } else {
                    emit apiError(message);
                }
            }
        }
    }
}
