#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QSpinBox>
#include <QMessageBox>

namespace Ui {
class Add;
}

class Api_Client;

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(int day, int month, int year, QWidget *parent);
    ~Add();
    QMessageBox* create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon);

private slots:
    void on_ok_button_clicked();
    void on_task_created_on_server(int task_id);
    void on_api_error(const QString& error);

private:
    Ui::Add *ui;
    int day, month, year;
    QSpinBox *hours_spinbox;
    QSpinBox *minutes_spinbox;
    Api_Client* apiClient;
    int localTaskIdToUpdate;
    void save_task_locally(const QString& title, const QString& time, int hours, int minutes);
    void save_task_to_server(const QString& title, int hours, int minutes, int local_task_id);
    void update_local_task_with_server_id(int server_task_id);
    void close_window();
};

#endif // ADD_H
