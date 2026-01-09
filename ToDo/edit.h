#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include "todo_list.h"

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(int day, int month, int year, QString title, QString time, int task_id, QWidget *parent);
    ~Edit();

private slots:
    void on_ok_button_clicked();

private:
    Ui::Edit *ui;
    int day, month, year;
    QString old_title, old_time;
    int task_id;
    QLineEdit *edit;
    QSpinBox *hours_spinbox;
    QSpinBox *minutes_spinbox;
};

#endif // EDIT_H
