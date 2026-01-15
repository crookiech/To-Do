#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "working_with_files.h"

namespace Ui {
class ToDo_List;
}

class Api_Client;

class ToDo_List : public QDialog
{
    Q_OBJECT

public:
    explicit ToDo_List(int day, int month, int year, QWidget *parent = nullptr);
    void load_tasks_from_file(const QString &filePath);
    ~ToDo_List() override;
    QMessageBox* create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon);

signals:
    void taskAdded();

private slots:
    void on_calendar_button_clicked();
    void on_add_task_clicked();
    void on_edit_task_clicked();
    void on_delete_task_clicked();
    void on_list_tasks_changed(QListWidgetItem *item);
    void on_task_deleted();
    void onApiError(const QString& errorMessage);

private:
    Ui::ToDo_List *ui;
    int day;
    int month;
    int year;
    Working_With_Files file_manager;
    Api_Client* apiClient;
    void deleteTaskFromServer(int task_id);
};

#endif // TODO_LIST_H
