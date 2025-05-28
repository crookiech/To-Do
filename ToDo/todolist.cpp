#include "todolist.h"
#include "ui_todolist.h"
#include "calendar.h"
#include "add.h"
#include "edit.h"
#include "globals.h"
#include "workingwithfiles.h"
#include <QDate>
#include <QString>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>

ToDoList::ToDoList(int day, int month, int year, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToDoList),
    day(day),
    month(month),
    year(year),
    fileManager(this)
{
    ui->setupUi(this);
    QSize iconSize(75, 75);
    ui->addTask->setIcon(QIcon(":/resources/resources/plusik.png"));
    ui->addTask->setIconSize(iconSize);
    ui->editTask->setIcon(QIcon(":/resources/resources/pen.png"));
    ui->editTask->setIconSize(iconSize);
    ui->deleteTask->setIcon(QIcon(":/resources/resources/cal.png"));
    ui->deleteTask->setIconSize(iconSize);
    ui->date->setText(QString(QDate(year, month, day).toString("dd.MM.yyyy")));
    loadTasksFromFile(pathToTasks);
    connect(ui->taskList, &QListWidget::itemChanged, this, &ToDoList::on_listItemChanged);
}

ToDoList::~ToDoList()
{
    delete ui;
}

int ToDoList::taskCount() const
{
    return ui->taskList->count();
}


QListWidgetItem* ToDoList::getItem(int n) const
{
    return ui->taskList->item(n);
}

void ToDoList::on_calendar_clicked()
{
    hide();
    Calendar window;
    window.setModal(true);
    window.exec();
}

QMessageBox* ToDoList::createMessageBox(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox* msgBox = new QMessageBox(parent);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet("background-color: white; color: black;");
    msgBox->setIcon(icon);
    return msgBox;
}

void ToDoList::on_addTask_clicked()
{
    Add window(day, month, year, this);
    window.setModal(true);
    window.exec();
    loadTasksFromFile(pathToTasks);
    emit taskAdded();
}

void ToDoList::on_editTask_clicked()
{
    QListWidgetItem *selectedItem = ui->taskList->currentItem();
    if (selectedItem) {
        QString title = selectedItem->data(Qt::UserRole + 2).toString();
        QString time = selectedItem->data(Qt::UserRole + 3).toString();
        Edit window(day, month, year, title, time, this);
        window.setModal(true);
        if (window.exec() == QDialog::Accepted) {
            loadTasksFromFile(pathToTasks);
        }
    } else {
        QMessageBox* msgBox = createMessageBox(this, "Редактирование задачи", "Выберите задачу для редактирования", QMessageBox::Information);
        msgBox->show();
    }
}

void ToDoList::on_deleteTask_clicked()
{
    QListWidgetItem *selectedItem = ui->taskList->currentItem();
    if (selectedItem) {
        QMessageBox confirmBox(this);
        confirmBox.setWindowTitle("Подтверждение удаления");
        confirmBox.setText("Вы действительно хотите удалить эту задачу?");
        confirmBox.setStyleSheet("background-color: white; color: black;");
        confirmBox.setIcon(QMessageBox::Question);
        confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmBox.setDefaultButton(QMessageBox::No);
        if (confirmBox.exec() == QMessageBox::No) {
            return;
        }
        WorkingWithFiles::TaskData task;
        task.date = selectedItem->data(Qt::UserRole + 1).toString();
        task.title = selectedItem->data(Qt::UserRole + 2).toString();
        task.time = selectedItem->data(Qt::UserRole + 3).toString();
        task.checked = selectedItem->data(Qt::UserRole + 4).toInt();
        if (fileManager.deleteTaskFromFile(pathToTasks, task)) {
            delete selectedItem;
            QMessageBox* msgBox = createMessageBox(this, "Удаление задачи", "Задача успешно удалена", QMessageBox::Information);
            msgBox->show();
        } else {
            QMessageBox* msgBox = createMessageBox(this, "Ошибка", "Не удалось удалить задачу", QMessageBox::Critical);
            msgBox->show();
        }
    } else {
        QMessageBox* msgBox = createMessageBox(this, "Удаление задачи", "Выберите задачу для удаления", QMessageBox::Information);
        msgBox->show();
    }

}

void ToDoList::loadTasksFromFile(const QString &filePath)
{
    std::vector<WorkingWithFiles::TaskData> tasks;
    if (fileManager.loadTasksFromFile(filePath, tasks)) {
        ui->taskList->clear();
        QString currentDate = QString("%1.%2.%3").arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0')).arg(year);
        for (const auto &task : tasks) {
            if (task.date == currentDate) {
                QString taskText = QString("%1%2").arg(task.title, -20).arg(task.time, 10);
                QListWidgetItem *item = new QListWidgetItem(taskText);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(task.checked ? Qt::Checked : Qt::Unchecked);
                QFont font = item->font();
                font.setStrikeOut(task.checked);
                item->setFont(font);
                item->setData(Qt::UserRole + 1, task.date);
                item->setData(Qt::UserRole + 2, task.title);
                item->setData(Qt::UserRole + 3, task.time);
                item->setData(Qt::UserRole + 4, task.checked);
                ui->taskList->addItem(item);
            }
        }
    } else {
        qDebug() << "todolist.cpp: error loading tasks from a file";
    }
}

void ToDoList::on_listItemChanged(QListWidgetItem *item)
{
    if (!item) return;
    WorkingWithFiles::TaskData task;
    task.date = item->data(Qt::UserRole + 1).toString();
    task.title = item->data(Qt::UserRole + 2).toString();
    task.time = item->data(Qt::UserRole + 3).toString();
    task.checked = (item->checkState() == Qt::Checked) ? 1 : 0;
    if (!fileManager.updateTaskInFile(pathToTasks, task)) {
        qDebug() << "todolist.cpp: failed to update the task in the file";
        return;
    }
    QFont font = item->font();
    font.setStrikeOut(item->checkState() == Qt::Checked);
    item->setFont(font);
}
