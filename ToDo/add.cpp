#include "add.h"
#include "ui_add.h"
#include "todo_list.h"
#include "globals.h"
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QDebug>

Add::Add(int day, int month, int year, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add),
    day(day),
    month(month),
    year(year)
{
    ui->setupUi(this);
    QDate date(year, month, day);
    QString formatted_date = date.toString("dd.MM.yyyy");
    ui->task_date->setText(formatted_date);
    hours_spinbox = new QSpinBox(this);
    hours_spinbox->setRange(0, 23);
    minutes_spinbox = new QSpinBox(this);
    minutes_spinbox->setRange(0, 59);
    QLabel* label_hours = new QLabel(this);
    QLabel* label_minutes = new QLabel(this);
    ui->task_time->addWidget(label_hours);
    ui->task_time->addWidget(hours_spinbox);
    ui->task_time->addWidget(label_minutes);
    ui->task_time->addWidget(minutes_spinbox);
}

Add::~Add()
{
    delete ui;
    delete hours_spinbox;
    delete minutes_spinbox;
}

void Add::on_ok_button_clicked()
{
    QString title = ui->task_title->text();
    QString time;
    int hours = hours_spinbox->value();
    int minutes = minutes_spinbox->value();
    time = QString::number(hours).rightJustified(2, '0') + ":" + QString::number(minutes).rightJustified(2, '0');
    if (title.isEmpty() || time.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }
    hide();
    Working_With_Files file_manager;
    std::vector<Working_With_Files::TaskData> tasks;
    if (!file_manager.load_tasks_from_file(path_to_tasks, tasks)) {
        tasks.clear();
    }
    int nextId = 1;
    for (const auto &task : tasks) {
        if (task.task_id >= nextId) {
            nextId = task.task_id + 1;
        }
    }
    Working_With_Files::TaskData task;
    task.year = year;
    task.month = month;
    task.day = day;
    task.time = time;
    task.title = title;
    task.checked = false;
    task.user_id = current_user_id;
    task.task_id = nextId;
    tasks.push_back(task);
    if (file_manager.write_all_tasks(path_to_tasks, tasks)) {
        qDebug() << "add.cpp: task added to JSON file, ID:" << task.task_id;
    } else {
        qDebug() << "add.cpp: couldn't add task to JSON file";
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить задачу.");
    }
    ToDo_List* window = qobject_cast<ToDo_List*>(parent());
    if (window) {
        window->load_tasks_from_file(path_to_tasks);
    } else {
        qDebug() << "add.cpp: couldn't get a pointer to TodoList";
    }
}
