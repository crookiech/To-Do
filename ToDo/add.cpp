#include "add.h"
#include "ui_add.h"
#include "todolist.h"
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
    QString formattedDate = date.toString("dd.MM.yyyy");
    ui->taskDate->setText(formattedDate);
    taskTitle = ui->taskTitle;
    hours_spinbox = new QSpinBox(this);
    hours_spinbox->setRange(0, 23);
    minutes_spinbox = new QSpinBox(this);
    minutes_spinbox->setRange(0, 59);
    QLabel* hoursLabel = new QLabel(this);
    QLabel* minutesLabel = new QLabel(this);
    ui->taskTime->addWidget(hoursLabel);
    ui->taskTime->addWidget(hours_spinbox);
    ui->taskTime->addWidget(minutesLabel);
    ui->taskTime->addWidget(minutes_spinbox);
}

Add::~Add()
{
    delete ui;
    delete hours_spinbox;
    delete minutes_spinbox;
}

void Add::on_ok_clicked()
{
    QString title = ui->taskTitle->text();
    QString time;
    int hours = hours_spinbox->value();
    int minutes = minutes_spinbox->value();
    time = QString::number(hours).rightJustified(2, '0') + ":" + QString::number(minutes).rightJustified(2, '0');
    if (title.isEmpty() || time.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }
    QString formattedDate = QString("%1.%2.%3").arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0')).arg(year);
    hide();
    QFile file(pathToTasks);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << formattedDate << "|" << title << "|" << time << "|0\n";
        file.close();
        qDebug() << "add.cpp: written to a file: " << formattedDate << "|" << title << "|" << time;
    } else {
        qDebug() << "add.cpp: couldn't open the file: " << pathToTasks;
    }
    ToDoList* window = qobject_cast<ToDoList*>(parent());
    if (window) {
       window->loadTasksFromFile(pathToTasks);
    } else {
       qDebug() << "add.cpp: couldn't get a pointer to TodoList";
    }
}
