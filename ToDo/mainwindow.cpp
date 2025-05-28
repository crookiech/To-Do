#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include "calendar.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap img(":/resources/resources/notebook.png");
    if (!img.isNull()) {
        QPixmap scaledimg = img.scaled(ui->icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->icon->setPixmap(scaledimg);
    } else {
        qDebug() << "calendar.cpp: Couldn't upload image";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    hide();
    Calendar window;
    window.setModal(true);
    window.exec();
}


