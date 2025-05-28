#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include "todolist.h"

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(int day, int month, int year, QWidget *parent);
    ~Add();
    QLineEdit* getLineEdit() { return taskTitle; }
    QSpinBox* getHourSpinBox() { return hours_spinbox; }
    QSpinBox* getMinuteSpinBox() { return minutes_spinbox; }

private slots:
    void on_ok_clicked();

private:
    Ui::Add *ui;
    int day;
    int month;
    int year;
    QLineEdit *taskTitle;
    QSpinBox *hours_spinbox;
    QSpinBox *minutes_spinbox;
};

#endif // ADD_H
