#include "testtodolist.h"
#include <QtTest>
#include <QSignalSpy>
#include <QLineEdit>
#include <QMetaObject>
#include <QPushButton>
#include "todolist.h"
#include "add.h"
#include "edit.h"
#include "workingwithfiles.h"

QString pathToTask = "C:/programming_tech/project/ToDo/tasks.txt";

TestToDo::TestToDo()
{
    todo = new ToDoList(21, 5, 2025);
}

void TestToDo::addTestTask(const QString& title, const QString& time)
{
    Add addDialog(21, 5, 2025, todo);
    addDialog.setModal(true);
    QLineEdit* taskTitle = addDialog.getLineEdit();
    QVERIFY(taskTitle != nullptr);
    taskTitle->setText(title);
    QSpinBox* hourSpinBox = addDialog.getHourSpinBox();
    QSpinBox* minuteSpinBox = addDialog.getMinuteSpinBox();
    QVERIFY(hourSpinBox != nullptr);
    QVERIFY(minuteSpinBox != nullptr);
    QStringList timeParts = time.split(":");
    hourSpinBox->setValue(timeParts[0].toInt());
    minuteSpinBox->setValue(timeParts[1].toInt());
    QPushButton* okButton = addDialog.findChild<QPushButton*>("ok");
    QVERIFY(okButton != nullptr);
    QMetaObject::invokeMethod(&addDialog, "on_ok_clicked");
}

void TestToDo::testAddNewTask() {
    Add *addDialog = new Add(21, 5, 2025, todo);
    addDialog->setModal(true);
    QLineEdit *taskTitle = addDialog->getLineEdit();
    taskTitle->setText("added task 1");
    QSpinBox *hourSpinBox = addDialog->getHourSpinBox();
    QSpinBox *minuteSpinBox = addDialog->getMinuteSpinBox();
    QVERIFY(hourSpinBox != nullptr);
    QVERIFY(minuteSpinBox != nullptr);
    hourSpinBox->setValue(12);
    minuteSpinBox->setValue(30);
    QPushButton *okButton = addDialog->findChild<QPushButton*>("ok");
    QVERIFY(okButton != nullptr);
    QMetaObject::invokeMethod(addDialog, "on_ok_clicked");
    bool taskFound = false;
    for (int i = 0; i < todo->taskCount(); ++i) {
        QListWidgetItem *item = todo->getItem(i);
        if (item->text().contains("added task 1") && item->text().contains("12:30")) {
            taskFound = true;
            break;
        }
    }
    QVERIFY(taskFound);
    delete addDialog;
}

void TestToDo::testEditTask()
{
    int initialCount = todo->taskCount();
    const QString originalTitle = "added task 2";
    const QString originalTime = "12:30";
    addTestTask(originalTitle, originalTime);
    QListWidget* taskList = todo->findChild<QListWidget*>();
    QVERIFY(taskList != nullptr);
    int targetRow = -1;
    for (int i = 0; i < taskList->count(); ++i) {
        if ((taskList->item(i)->data(Qt::UserRole + 2).toString() == originalTitle) &&
            (taskList->item(i)->data(Qt::UserRole + 3).toString() == originalTime)) {
            targetRow = i;
            break;
        }
    }
    QVERIFY(targetRow != -1);
    taskList->setCurrentRow(targetRow);
    Edit* editDialog = new Edit(21, 5, 2025, originalTitle, originalTime, todo);
    editDialog->setModal(true);
    QLineEdit* taskTitle = editDialog->findChild<QLineEdit*>("taskTitle");
    QVERIFY(taskTitle != nullptr);
    QCOMPARE(taskTitle->text(), originalTitle);
    const QString newTitle = "edited task 2";
    taskTitle->setText(newTitle);
    QList<QSpinBox*> spinBoxes = editDialog->findChildren<QSpinBox*>();
    spinBoxes[0]->setValue(13);
    spinBoxes[1]->setValue(30);
    QPushButton* okButton = editDialog->findChild<QPushButton*>("ok");
    QVERIFY(okButton != nullptr);
    QMetaObject::invokeMethod(editDialog, "on_ok_clicked");
    QCOMPARE(todo->taskCount(), initialCount + 1);
    delete editDialog;
}

void TestToDo::testDeleteTask()
{
    const QString taskTitle = "added task 3";
    const QString taskTime = "12:30";
    addTestTask(taskTitle, taskTime);
    int initialCount = todo->taskCount();
    QListWidget* taskList = todo->findChild<QListWidget*>("taskList");
    taskList->setCurrentRow(0);
    QPushButton* deleteButton = todo->findChild<QPushButton*>("deleteTask");
    QVERIFY(deleteButton != nullptr);
    QMetaObject::invokeMethod(todo, "on_deleteTask_clicked");
    QCOMPARE(todo->taskCount(), initialCount - 1);
}

void TestToDo::testTaskCompletion()
{
    addTestTask("task to complete", "12:30");
    QListWidget* taskList = todo->findChild<QListWidget*>();
    QVERIFY(taskList != nullptr);

    // Find the target item
    QListWidgetItem* targetItem = nullptr;
    for (int i = 0; i < taskList->count(); ++i) {
        if ((taskList->item(i)->data(Qt::UserRole + 2).toString() == "task to complete") &&
            (taskList->item(i)->data(Qt::UserRole + 3).toString() == "12:30")) {
            targetItem = taskList->item(i);
            break;
        }
    }
    QVERIFY(targetItem != nullptr);

    // Set check state and process events to ensure signal is handled
    targetItem->setCheckState(Qt::Checked);
    QCoreApplication::processEvents(); // Process pending events

    // Use the same path as the application
    WorkingWithFiles fileManager;
    std::vector<WorkingWithFiles::TaskData> tasks;
    fileManager.loadTasksFromFile(pathToTask, tasks); // Use pathToTasks instead of pathToTask

    bool found = false;
    for (const auto& task : tasks) {
        if ((task.title == "task to complete") &&
            (task.time == "12:30") &&
            (task.checked == 1)) {
            found = true;
            break;
        }
    }
    QVERIFY(found);
    cleanupTestData();
}

// void TestToDo::testTaskCompletion()
// {
//     addTestTask("task to complete", "12:30");
//     QListWidget* taskList = todo->findChild<QListWidget*>();
//     QVERIFY(taskList != nullptr);
//     QListWidgetItem* targetItem = nullptr;
//     for (int i = 0; i < taskList->count(); ++i) {
//         if ((taskList->item(i)->data(Qt::UserRole + 2).toString() == "task to complete") &&
//             (taskList->item(i)->data(Qt::UserRole + 3).toString() == "12:30")) {
//             targetItem = taskList->item(i);
//             break;
//         }
//     }
//     QVERIFY(targetItem != nullptr);
//     targetItem->setCheckState(Qt::Checked);
//     WorkingWithFiles fileManager;
//     std::vector<WorkingWithFiles::TaskData> tasks;
//     fileManager.loadTasksFromFile(pathToTask, tasks);
//     bool found = false;
//     for (const auto& task : tasks) {
//         if ((task.title == "task to complete") && (task.time == "12:30")  &&  (task.checked == 1)) {
//             found = true;
//             break;
//         }
//     }
//     QVERIFY(found);
//     cleanupTestData();
// }

void TestToDo::cleanupTestData()
{
    WorkingWithFiles fileManager;
    std::vector<WorkingWithFiles::TaskData> tasks;
    fileManager.loadTasksFromFile(pathToTask, tasks);
    auto newEnd = std::remove_if(tasks.begin(), tasks.end(), [this](const WorkingWithFiles::TaskData& task) {
        return task.date == "21.05.2025" && task.title.contains("task");
    });
    tasks.erase(newEnd, tasks.end());
    fileManager.writeAllTasks(pathToTask, tasks);
}

TestToDo::~TestToDo()
{
    cleanupTestData();
    delete todo;
}

QTEST_MAIN(TestToDo)
#include "moc_testtodolist.cpp"
