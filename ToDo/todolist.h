#ifndef TODOLIST_H
#define TODOLIST_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "workingwithfiles.h"

namespace Ui {
class ToDoList;
}

class ToDoList : public QDialog
{
    Q_OBJECT

public:
    explicit ToDoList(int day, int month, int year, QWidget *parent = nullptr);
    void loadTasksFromFile(const QString &filePath);
    ~ToDoList() override;
    QMessageBox* createMessageBox(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon);
    QListWidgetItem* getItem(int n) const;
    int taskCount() const;

signals:
    void taskAdded();

private slots:
    void on_calendar_clicked();
    void on_addTask_clicked();
    void on_editTask_clicked();
    void on_deleteTask_clicked();
    void on_listItemChanged(QListWidgetItem *item);

private:
    Ui::ToDoList *ui;
    int day;
    int month;
    int year;
    WorkingWithFiles fileManager;
    void updateTaskInFile(const QString &filePath, const QString &date, const QString &title, const QString &time, int checked);
};

#endif // TODOLIST_H
