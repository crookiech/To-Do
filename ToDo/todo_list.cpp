#include "todo_list.h"
#include "ui_todo_list.h"
#include "calendar.h"
#include "add.h"
#include "edit.h"
#include "globals.h"
#include "working_with_files.h"
#include "api_client.h"
#include <QDate>
#include <QString>
#include <QListWidgetItem>
#include <QMessageBox>

ToDo_List::ToDo_List(int day, int month, int year, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToDo_List),
    day(day),
    month(month),
    year(year),
    file_manager(this),
    apiClient(new Api_Client(this))
{
    ui->setupUi(this);
    QSize iconSize(75, 75);
    ui->add_task->setIcon(QIcon(":/resources/resources/plusik.png"));
    ui->add_task->setIconSize(iconSize);
    ui->edit_task->setIcon(QIcon(":/resources/resources/pen.png"));
    ui->edit_task->setIconSize(iconSize);
    ui->delete_task->setIcon(QIcon(":/resources/resources/cal.png"));
    ui->delete_task->setIconSize(iconSize);
    ui->label_date->setText(QString(QDate(year, month, day).toString("dd.MM.yyyy")));
    connect(apiClient, &Api_Client::task_deleted, this, &ToDo_List::on_task_deleted);
    connect(apiClient, &Api_Client::api_error, this, &ToDo_List::onApiError);
    load_tasks_from_file(path_to_tasks);
    connect(ui->list_tasks, &QListWidget::itemChanged, this, &ToDo_List::on_list_tasks_changed);
}

ToDo_List::~ToDo_List()
{
    delete ui;
}

void ToDo_List::on_calendar_button_clicked()
{
    hide();
    Calendar window;
    window.setModal(true);
    window.exec();
}

QMessageBox* ToDo_List::create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox* msgBox = new QMessageBox(parent);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet("background-color: white; color: black;");
    msgBox->setIcon(icon);
    return msgBox;
}

void ToDo_List::on_add_task_clicked()
{
    Add window(day, month, year, this);
    window.setModal(true);
    window.exec();
    load_tasks_from_file(path_to_tasks);
    emit taskAdded();
}

void ToDo_List::on_edit_task_clicked()
{
    QListWidgetItem *selectedItem = ui->list_tasks->currentItem();
    if (selectedItem) {
        QString title = selectedItem->data(Qt::UserRole + 4).toString();
        QString time = selectedItem->data(Qt::UserRole + 5).toString();
        int task_id = selectedItem->data(Qt::UserRole + 8).toInt();
        Edit window(day, month, year, title, time, task_id, this);
        window.setModal(true);
        if (window.exec() == QDialog::Accepted) {
            load_tasks_from_file(path_to_tasks);
        }
    } else {
        QMessageBox* msgBox = create_message_box(this, "Редактирование задачи", "Выберите задачу для редактирования", QMessageBox::Information);
        msgBox->show();
    }
}

void ToDo_List::on_delete_task_clicked()
{
    QListWidgetItem *selectedItem = ui->list_tasks->currentItem();
    if (!selectedItem) {
        QMessageBox* msgBox = create_message_box(this, "Удаление задачи", "Выберите задачу для удаления", QMessageBox::Information);
        msgBox->show();
        return;
    }
    if (current_user_id <= 0) {
        QMessageBox* msgBox = create_message_box(this, "Ошибка", "Вы не авторизованы. Удаление только локально.", QMessageBox::Warning);
        msgBox->show();
    }
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle("Подтверждение удаления");
    confirmBox.setText("Вы действительно хотите удалить эту задачу?");
    confirmBox.setStyleSheet("background-color: white; color: black;");
    confirmBox.setIcon(QMessageBox::Question);
    confirmBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *noButton = confirmBox.addButton("Нет", QMessageBox::NoRole);
    confirmBox.setDefaultButton(noButton);
    confirmBox.exec();
    if (confirmBox.clickedButton() == noButton) {
        return;
    }
    Working_With_Files::TaskData task;
    task.year = year;
    task.month = month;
    task.day = day;
    task.title = selectedItem->data(Qt::UserRole + 4).toString();
    task.time = selectedItem->data(Qt::UserRole + 5).toString();
    task.checked = selectedItem->data(Qt::UserRole + 6).toBool();
    task.user_id = selectedItem->data(Qt::UserRole + 7).toInt();
    task.task_id = selectedItem->data(Qt::UserRole + 8).toInt();
    task.local_id = selectedItem->data(Qt::UserRole + 9).toInt();
    if (file_manager.delete_task_from_file(path_to_tasks, task)) {
        delete selectedItem;
        if (task.task_id > 0 && task.user_id == current_user_id) {
            deleteTaskFromServer(task.task_id);
        } else {
            QString message;
            if (current_user_id <= 0) {
                message = "Задача удалена локально. Для синхронизации с сервером войдите в систему.";
            } else if (task.user_id != current_user_id) {
                message = "Задача удалена локально (не ваш пользователь).";
            } else {
                message = "Задача успешно удалена локально.";
            }
            QMessageBox* msgBox = create_message_box(this, "Успех", message, QMessageBox::Information);
            msgBox->show();
        }
    } else {
        QMessageBox* msgBox = create_message_box(this, "Ошибка", "Не удалось удалить задачу", QMessageBox::Critical);
        msgBox->show();
    }
}

void ToDo_List::deleteTaskFromServer(int task_id)
{
    if (current_user_id <= 0) {
        return;
    }
    apiClient->delete_task(current_user_id, task_id);
}

void ToDo_List::on_task_deleted()
{
    QMessageBox* msgBox = create_message_box(this, "Удаление задачи", "Задача успешно удалена", QMessageBox::Information);
    msgBox->show();
}

void ToDo_List::onApiError(const QString& errorMessage)
{
    if (errorMessage.contains("Сервер недоступен") ||
        errorMessage.contains("Connection refused")) {
        QMessageBox::information(this, "Предупреждение", "Задача удалена локально, но сервер недоступен.");
    } else {
        QMessageBox::warning(this, "Ошибка сервера", "Не удалось удалить задачу с сервера: " + errorMessage + "\nЗадача удалена только локально.");
    }
}

void ToDo_List::load_tasks_from_file(const QString &filePath)
{
    std::vector<Working_With_Files::TaskData> tasks;
    if (file_manager.load_tasks_from_file(filePath, tasks)) {
        ui->list_tasks->clear();
        int current_user = current_user_id;
        for (const auto &task : tasks) {
            bool userMatches = (task.user_id == current_user);
            bool dateMatches = (task.year == year && task.month == month && task.day == day);
            if (userMatches && dateMatches) {
                QString taskText = QString("%1 %2").arg(task.time).arg(task.title);
                QListWidgetItem *item = new QListWidgetItem(taskText);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(task.checked ? Qt::Checked : Qt::Unchecked);
                QFont font = item->font();
                font.setStrikeOut(task.checked);
                item->setFont(font);
                item->setData(Qt::UserRole + 1, task.year);
                item->setData(Qt::UserRole + 2, task.month);
                item->setData(Qt::UserRole + 3, task.day);
                item->setData(Qt::UserRole + 4, task.title);
                item->setData(Qt::UserRole + 5, task.time);
                item->setData(Qt::UserRole + 6, task.checked);
                item->setData(Qt::UserRole + 7, task.user_id);
                item->setData(Qt::UserRole + 8, task.task_id);
                item->setData(Qt::UserRole + 9, task.local_id);
                ui->list_tasks->addItem(item);
            }
        }
    }
}

void ToDo_List::on_list_tasks_changed(QListWidgetItem *item)
{
    if (!item) return;
    ui->list_tasks->blockSignals(true);
    Working_With_Files::TaskData task;
    task.year = item->data(Qt::UserRole + 1).toInt();
    task.month = item->data(Qt::UserRole + 2).toInt();
    task.day = item->data(Qt::UserRole + 3).toInt();
    task.title = item->data(Qt::UserRole + 4).toString();
    task.time = item->data(Qt::UserRole + 5).toString();
    task.checked = (item->checkState() == Qt::Checked);
    task.user_id = item->data(Qt::UserRole + 7).toInt();
    task.task_id = item->data(Qt::UserRole + 8).toInt();
    task.local_id = item->data(Qt::UserRole + 9).toInt();
    if (!file_manager.update_task_in_file(path_to_tasks, task)) {
    }
    if (task.task_id > 0 && task.user_id == current_user_id) {
        Task serverTask;
        serverTask.title = task.title;
        serverTask.year = task.year;
        serverTask.month = task.month;
        serverTask.day = task.day;
        QStringList timeParts = task.time.split(":");
        if (timeParts.size() == 2) {
            serverTask.hours = timeParts[0].toInt();
            serverTask.minutes = timeParts[1].toInt();
        }
        serverTask.is_completed = task.checked;
        serverTask.task_id = task.task_id;
        serverTask.local_id = task.local_id;
        apiClient->update_task(current_user_id, task.task_id, serverTask);
    }
    QFont font = item->font();
    font.setStrikeOut(task.checked);
    item->setFont(font);
    ui->list_tasks->blockSignals(false);
}
