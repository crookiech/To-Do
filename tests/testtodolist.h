#ifndef TESTTODOLIST_H
#define TESTTODOLIST_H

#include <QtTest>
#include <QListWidget>
#include <QMessageBox>
#include "todolist.h"

class TestToDo : public QObject
{
    Q_OBJECT

public:
    TestToDo();
    ~TestToDo();

private slots:
    void testAddNewTask();
    void testEditTask();
    void testDeleteTask();
    void testTaskCompletion();
    void addTestTask(const QString& title, const QString& time);
    void cleanupTestData();

private:
    ToDoList* todo;
};

#endif // TESTTODOLIST_H
