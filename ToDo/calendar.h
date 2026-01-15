#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>

namespace Ui {
class Calendar;
}

class Calendar : public QDialog
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    ~Calendar();

private:
    Ui::Calendar *ui;

private slots:
    void on_date_clicked();
};

#endif // CALENDAR_H
