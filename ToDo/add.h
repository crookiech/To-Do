#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include "todo_list.h"

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(int day, int month, int year, QWidget *parent);
    ~Add();

private slots:
    void on_ok_button_clicked();

private:
    Ui::Add *ui;
    int day;
    int month;
    int year;
    QSpinBox *hours_spinbox;
    QSpinBox *minutes_spinbox;
};

#endif // ADD_H
