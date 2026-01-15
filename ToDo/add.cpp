#include "add.h"
#include "ui_add.h"
#include "globals.h"
#include "working_with_files.h"
#include "api_client.h"
#include "todo_list.h"
#include <QDate>
#include <QString>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>

Add::Add(int day, int month, int year, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add),
    day(day),
    month(month),
    year(year),
    apiClient(new Api_Client(this)),
    localTaskIdToUpdate(0)
{
    ui->setupUi(this);
    QDate date(year, month, day);
    QString formatted_date = date.toString("dd.MM.yyyy");
    ui->task_date->setText(formatted_date);
    hours_spinbox = new QSpinBox(this);
    hours_spinbox->setRange(0, 23);
    hours_spinbox->setValue(12);
    minutes_spinbox = new QSpinBox(this);
    minutes_spinbox->setRange(0, 59);
    minutes_spinbox->setValue(0);
    QLabel* colon_label = new QLabel(":", this);
    colon_label->setAlignment(Qt::AlignCenter);
    ui->task_time->addWidget(hours_spinbox);
    ui->task_time->addWidget(colon_label);
    ui->task_time->addWidget(minutes_spinbox);
    connect(apiClient, &Api_Client::task_created, this, &Add::on_task_created_on_server);
    connect(apiClient, &Api_Client::api_error, this, &Add::on_api_error);
}

Add::~Add()
{
    delete ui;
    delete hours_spinbox;
    delete minutes_spinbox;
}

QMessageBox* Add::create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox* msgBox = new QMessageBox(parent);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet("background-color: white; color: black;");
    msgBox->setIcon(icon);
    return msgBox;
}

void Add::on_ok_button_clicked()
{
    QString title = ui->task_title->text().trimmed();
    int hours = hours_spinbox->value();
    int minutes = minutes_spinbox->value();
    QString time = QString("%1:%2").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0'));
    if (title.isEmpty()) {
        QMessageBox* msgBox = create_message_box(this, "Добавление задачи", "Пожалуйста, введите название задачи", QMessageBox::Warning);
        msgBox->show();
        return;
    }
    save_task_locally(title, time, hours, minutes);
}

void Add::save_task_locally(const QString& title, const QString& time, int hours, int minutes)
{
    Working_With_Files file_manager;
    std::vector<Working_With_Files::TaskData> tasks;
    if (!file_manager.load_tasks_from_file(path_to_tasks, tasks)) {
        tasks.clear();
    }
    int nextLocalId = file_manager.get_next_local_id(path_to_tasks);
    Working_With_Files::TaskData task;
    task.year = year;
    task.month = month;
    task.day = day;
    task.time = time;
    task.title = title;
    task.checked = false;
    task.user_id = current_user_id;
    task.task_id = 0;
    task.local_id = nextLocalId;
    localTaskIdToUpdate = nextLocalId;
    if (file_manager.add_task_to_json(path_to_tasks, task)) {
        save_task_to_server(title, hours, minutes, nextLocalId);
    }
}

void Add::save_task_to_server(const QString& title, int hours, int minutes, int local_task_id)
{
    Task serverTask;
    serverTask.title = title;
    serverTask.year = year;
    serverTask.month = month;
    serverTask.day = day;
    serverTask.hours = hours;
    serverTask.minutes = minutes;
    serverTask.is_completed = false;
    serverTask.local_id = local_task_id;
    apiClient->create_task(current_user_id, serverTask);
}

void Add::on_task_created_on_server(int server_task_id)
{
    if (server_task_id > 0) {
        update_local_task_with_server_id(server_task_id);
    }
    close_window();
}

void Add::update_local_task_with_server_id(int server_task_id)
{
    Working_With_Files file_manager;
    std::vector<Working_With_Files::TaskData> tasks;
    if (!file_manager.load_tasks_from_file(path_to_tasks, tasks)) {
        return;
    }
    bool found = false;
    for (auto &task : tasks) {
        if (task.local_id == localTaskIdToUpdate && task.user_id == current_user_id) {
            task.task_id = server_task_id;
            found = true;
            break;
        }
    }
    if (found) {
        if (file_manager.write_all_tasks(path_to_tasks, tasks)) {
        } else {
        }
    } else {
        int maxLocalId = 0;
        int taskIndex = -1;
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].user_id == current_user_id && tasks[i].local_id > maxLocalId) {
                maxLocalId = tasks[i].local_id;
                taskIndex = i;
            }
        }
        if (taskIndex != -1) {
            tasks[taskIndex].task_id = server_task_id;
            if (file_manager.write_all_tasks(path_to_tasks, tasks)) {
            }
        }
    }
}

void Add::on_api_error(const QString& errorMessage)
{
    if (errorMessage.contains("Сервер недоступен") ||
        errorMessage.contains("Connection refused") ||
        errorMessage.contains("HostNotFoundError")) {
        QMessageBox::information(this, "Предупреждение", "Задача сохранена только локально. Сервер недоступен.");
        close_window();
    } else {
        QMessageBox::warning(this, "Ошибка сервера", "Не удалось сохранить задачу на сервер: " + errorMessage + "\nЗадача сохранена только локально.");
        close_window();
    }
}

void Add::close_window()
{
    ToDo_List* parentWindow = qobject_cast<ToDo_List*>(parent());
    if (parentWindow) {
        parentWindow->load_tasks_from_file(path_to_tasks);
        emit parentWindow->taskAdded();
    }
    accept();
}
