#include "calendar.h"
#include "ui_calendar.h"
#include "todolist.h"
#include <QTextCharFormat>
#include <QPalette>

Calendar::Calendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &Calendar::onDateClicked);
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::onDateClicked()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    int day = selectedDate.day();
    int month = selectedDate.month();
    int year = selectedDate.year();
    hide();
    ToDoList window(day, month, year, this);
    window.setModal(true);
    window.exec();
}
