#include "edit.h"
#include "ui_edit.h"
#include "todo_list.h"
#include "globals.h"
#include "working_with_files.h"
#include "api_client.h"
#include <QDate>
#include <QString>
#include <QMessageBox>
#include <QSpinBox>

Edit::Edit(int day, int month, int year, QString title, QString time, int task_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit),
    day(day),
    month(month),
    year(year),
    old_title(title),
    old_time(time),
    task_id(task_id),
    api_client(new Api_Client(this))
{
    ui->setupUi(this);
    QDate date(year, month, day);
    QString formatted_date = date.toString("dd.MM.yyyy");
    ui->task_date->setText(formatted_date);
    hours_spinbox = new QSpinBox(this);
    hours_spinbox->setRange(0, 23);
    minutes_spinbox = new QSpinBox(this);
    minutes_spinbox->setRange(0, 59);
    QStringList time_parts = time.split(":");
    if (time_parts.size() == 2) {
        bool ok_hours, ok_minutes;
        int hours = time_parts[0].toInt(&ok_hours);
        int minutes = time_parts[1].toInt(&ok_minutes);
        if (ok_hours && ok_minutes) {
            hours_spinbox->setValue(hours);
            minutes_spinbox->setValue(minutes);
        } else {
            hours_spinbox->setValue(0);
            minutes_spinbox->setValue(0);
        }
    } else {
        hours_spinbox->setValue(0);
        minutes_spinbox->setValue(0);
    }
    QLabel* label_hours = new QLabel(":", this);
    QLabel* label_minutes = new QLabel("", this);
    ui->task_time->addWidget(hours_spinbox);
    ui->task_time->addWidget(label_hours);
    ui->task_time->addWidget(minutes_spinbox);
    ui->task_time->addWidget(label_minutes);
    ui->task_title->setText(title);
    connect(api_client, &Api_Client::task_updated, this, &Edit::on_task_updated);
    connect(api_client, &Api_Client::api_error, this, &Edit::on_api_error);
}

Edit::~Edit()
{
    delete ui;
    delete hours_spinbox;
    delete minutes_spinbox;
}

QMessageBox* Edit::create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox* msgBox = new QMessageBox(parent);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet("background-color: white; color: black;");
    msgBox->setIcon(icon);
    return msgBox;
}

void Edit::on_ok_button_clicked()
{
    QString new_title = ui->task_title->text().trimmed();
    int hours = hours_spinbox->value();
    int minutes = minutes_spinbox->value();
    QString new_time = QString("%1:%2").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0'));
    if (new_title.isEmpty()) {
        QMessageBox* msgBox = create_message_box(this, "Редактирование задачи", "Пожалуйста, введите название задачи", QMessageBox::Warning);
        msgBox->show();
        return;
    }
    Working_With_Files file_manager;
    std::vector<Working_With_Files::TaskData> tasks;
    if (!file_manager.load_tasks_from_file(path_to_tasks, tasks)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить задачи.");
        return;
    }
    bool found = false;
    Working_With_Files::TaskData updated_task;
    bool is_completed = false;
    int local_id = 0;
    for (auto &task : tasks) {
        if (task.task_id == task_id && task.user_id == current_user_id) {
            is_completed = task.checked;
            local_id = task.local_id;
            task.title = new_title;
            task.time = new_time;
            found = true;
            break;
        }
    }
    if (!found) {
        QMessageBox::warning(this, "Ошибка", "Задача не найдена.");
        return;
    }
    if (file_manager.write_all_tasks(path_to_tasks, tasks)) {

        QJsonObject data;
        data["title"] = new_title;
        data["year"] = year;
        data["month"] = month;
        data["day"] = day;
        data["hours"] = hours;
        data["minutes"] = minutes;
        data["is_completed"] = is_completed;
        if (current_user_id > 0 && task_id > 0) {
            Task server_task;
            server_task.title = new_title;
            server_task.year = year;
            server_task.month = month;
            server_task.day = day;
            server_task.hours = hours;
            server_task.minutes = minutes;
            server_task.is_completed = is_completed;
            server_task.task_id = task_id;
            server_task.local_id = local_id;
            QJsonObject json = server_task.to_json();
            api_client->update_task(current_user_id, task_id, server_task);
        } else {
            close_window();
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить задачу локально.");
    }
}

void Edit::on_task_updated()
{
    close_window();
}

void Edit::on_api_error(const QString& error_message)
{
    if (error_message.contains("Сервер недоступен") ||
        error_message.contains("Connection refused") ||
        error_message.contains("HostNotFoundError")) {
        QMessageBox::information(this, "Предупреждение", "Задача обновлена локально, но сервер недоступен.");
    } else {
        QMessageBox::warning(this, "Ошибка сервера", "Не удалось обновить задачу на сервере: " + error_message + "\nЗадача обновлена только локально.");
    }
    close_window();
}

void Edit::close_window()
{
    ToDo_List* parent_window = qobject_cast<ToDo_List*>(parent());
    if (parent_window) {
        parent_window->load_tasks_from_file(path_to_tasks);
    }
    accept();
}
