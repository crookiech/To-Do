#include "edit.h"
#include "ui_edit.h"
#include "todo_list.h"
#include "globals.h"
#include "working_with_files.h"
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QDebug>

Edit::Edit(int day, int month, int year, QString title, QString time, int task_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit),
    day(day),
    month(month),
    year(year),
    old_title(title),
    old_time(time),
    task_id(task_id)
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
            qDebug() << "edit.cpp: time parsing error: " << time;
            hours_spinbox->setValue(0);
            minutes_spinbox->setValue(0);
        }
    } else {
        qDebug() << "edit.cpp: incorrect time format: " << time;
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
}

Edit::~Edit()
{
    delete ui;
    delete hours_spinbox;
    delete minutes_spinbox;
}

void Edit::on_ok_button_clicked()
{
    QString new_title = ui->task_title->text();
    QString new_time;
    int hours = hours_spinbox->value();
    int minutes = minutes_spinbox->value();
    new_time = QString::number(hours).rightJustified(2, '0') + ":" + QString::number(minutes).rightJustified(2, '0');
    if (new_title.isEmpty() || new_time.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }
    hide();
    Working_With_Files file_manager;
    std::vector<Working_With_Files::TaskData> tasks;
    if (!file_manager.load_tasks_from_file(path_to_tasks, tasks)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить задачи.");
        return;
    }
    bool found = false;
    for (auto &task : tasks) {
        if (task.task_id == task_id && task.user_id == current_user_id) {
            task.title = new_title;
            task.time = new_time;
            found = true;
            break;
        }
    }
    if (found) {
        if (file_manager.write_all_tasks(path_to_tasks, tasks)) {
            qDebug() << "edit.cpp: task updated in JSON file, ID:" << task_id;
            accept();
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить задачу.");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Задача не найдена.");
    }
    ToDo_List* window = qobject_cast<ToDo_List*>(parent());
    if (window) {
        window->load_tasks_from_file(path_to_tasks);
    } else {
        qDebug() << "edit.cpp: couldn't get a pointer to TodoList";
    }
}
