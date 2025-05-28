#include "edit.h"
#include "ui_edit.h"
#include "todolist.h"
#include "globals.h"
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QDebug>

Edit::Edit(int day, int month, int year, QString title, QString time, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit),
    day(day),
    month(month),
    year(year),
    oldTitle(title),
    oldTime(time)
{
    ui->setupUi(this);
    QDate date(year, month, day);
    QString formattedDate = date.toString("dd.MM.yyyy");
    ui->taskDate->setText(formattedDate);
    hours_spinbox = new QSpinBox(this);
    hours_spinbox->setRange(0, 23);
    minutes_spinbox = new QSpinBox(this);
    minutes_spinbox->setRange(0, 59);
    QStringList timeParts = time.split(":");
    if (timeParts.size() == 2) {
        bool okHours, okMinutes;
        int hours = timeParts[0].toInt(&okHours);
        int minutes = timeParts[1].toInt(&okMinutes);
        if (okHours && okMinutes) {
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
    QLabel* hoursLabel = new QLabel("",this);
    QLabel* minutesLabel = new QLabel("",this);
    ui->taskTime->addWidget(hours_spinbox);
    ui->taskTime->addWidget(hoursLabel);
    ui->taskTime->addWidget(minutes_spinbox);
    ui->taskTime->addWidget(minutesLabel);
    ui->taskTitle->setText(title);
}

Edit::~Edit()
{
    delete ui;
    delete hours_spinbox;
    delete minutes_spinbox;
}

void Edit::on_ok_clicked()
{
    QString newTitle = ui->taskTitle->text();
    QString newTime;
    int hours = hours_spinbox->value();
    int minutes = minutes_spinbox->value();
    newTime = QString::number(hours).rightJustified(2, '0') + ":" + QString::number(minutes).rightJustified(2, '0');
    QString formattedDate = QString("%1.%2.%3").arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0')).arg(year);
    if (newTitle.isEmpty() || newTime.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }
    hide();
    QFile file(pathToTasks);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "edit.cpp: couldn't open the file: " << pathToTasks;
        return;
    }
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();
    QString oldTaskLine;
    QStringList lines = fileContent.split("\n");
    for (const QString &line : lines) {
        QStringList parts = line.split("|");
        if (parts.size() == 4) {
            QString date = parts[0];
            QString title = parts[1];
            QString time = parts[2];
            if (date == formattedDate && title == oldTitle && time == oldTime) {
                oldTaskLine = line;
                break;
            }
        }
    }
    if (!oldTaskLine.isEmpty()) {
        QString newTaskLine = formattedDate + "|" + newTitle + "|" + newTime + "|0";
        fileContent.replace(oldTaskLine, newTaskLine);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            qDebug() << "edit.cpp: couldn't open the file for writing: " << pathToTasks;
            return;
        }
        QTextStream out(&file);
        out << fileContent;
        file.close();
        qDebug() << "edit.cpp: the task has been changed in the file: " << newTaskLine;
    } else {
        qDebug() << "edit.cpp: the old task was not found in the file";
    }
    ToDoList* window = qobject_cast<ToDoList*>(parent());
    if (window) {
       window->loadTasksFromFile(pathToTasks);
    } else {
       qDebug() << "edit.cpp: couldn't get a pointer to TodoList";
    }
}
