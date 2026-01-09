#include "main_window.h"
#include "ui_main_window.h"
#include <QPixmap>
#include <QDebug>
#include "calendar.h"

Main_Window::Main_Window(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Main_Window)
{
    ui->setupUi(this);
    QPixmap img(":/resources/resources/notebook.png");
    if (!img.isNull()) {
        QPixmap scaled_img = img.scaled(ui->icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->icon->setPixmap(scaled_img);
    } else {
        qDebug() << "calendar.cpp: Couldn't upload image";
    }
}

Main_Window::~Main_Window()
{
    delete ui;
}


void Main_Window::on_start_button_clicked()
{
    hide();
    Calendar window;
    window.setModal(true);
    window.exec();
}


