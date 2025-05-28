#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include "todolist.h"

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(int day, int month, int year, QString title, QString time, QWidget *parent);
    ~Edit();
    QLineEdit* getLineEdit() { return lineEdit; }
    QSpinBox* getHourSpinBox() { return hours_spinbox; }
    QSpinBox* getMinuteSpinBox() { return minutes_spinbox; }

private slots:
    void on_ok_clicked();

private:
    Ui::Edit *ui;
    int day, month, year;
    QString oldTitle, oldTime;
    QLineEdit *lineEdit;
    QSpinBox *hours_spinbox;
    QSpinBox *minutes_spinbox;
};

#endif // EDIT_H
