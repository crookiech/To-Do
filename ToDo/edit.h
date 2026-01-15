#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Edit;
}

class Api_Client;

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(int day, int month, int year, QString title, QString time, int task_id, QWidget *parent = nullptr);
    ~Edit();
    QMessageBox* create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon);

private slots:
    void on_ok_button_clicked();
    void on_task_updated();
    void on_api_error(const QString& error_message);

private:
    void close_window();

    Ui::Edit *ui;
    int day, month, year;
    QString old_title, old_time;
    int task_id;
    class QSpinBox *hours_spinbox, *minutes_spinbox;
    Api_Client* api_client;
};

#endif // EDIT_H
