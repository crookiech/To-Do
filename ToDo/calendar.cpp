#include "calendar.h"
#include "ui_calendar.h"
#include "todo_list.h"

Calendar::Calendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &Calendar::on_date_clicked);
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::on_date_clicked()
{
    QDate selected_date = ui->calendarWidget->selectedDate();
    int day = selected_date.day();
    int month = selected_date.month();
    int year = selected_date.year();
    hide();
    ToDo_List window(day, month, year, this);
    window.setModal(true);
    window.exec();
}
