/********************************************************************************
** Form generated from reading UI file 'calendar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDAR_H
#define UI_CALENDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Calendar
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QCalendarWidget *calendarWidget;

    void setupUi(QDialog *Calendar)
    {
        if (Calendar->objectName().isEmpty())
            Calendar->setObjectName(QString::fromUtf8("Calendar"));
        Calendar->resize(800, 600);
        Calendar->setStyleSheet(QString::fromUtf8("background-color: #333F51;\n"
""));
        gridLayout = new QGridLayout(Calendar);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 29, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        calendarWidget = new QCalendarWidget(Calendar);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setMinimumSize(QSize(700, 500));
        calendarWidget->setStyleSheet(QString::fromUtf8("QCalendarWidget QWidget#qt_calendar_navigationbar {\n"
"    background-color: #FFD8BA;\n"
"    color: #333F51;\n"
"    font-size: 18pt;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QCalendarWidget QToolButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    color: #950505;\n"
"    icon-size: 30px;\n"
"}\n"
"\n"
"QCalendarWidget QAbstractItemView {\n"
"    background-color: #333F51;\n"
"    border: none;\n"
"    outline: none;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QCalendarWidget QAbstractItemView::item {\n"
"    background-color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    width: 30px;\n"
"    height: 30px;\n"
"    text-align: center;\n"
"    margin: 3px;\n"
"}\n"
"\n"
"QCalendarWidget QAbstractItemView::item:selected {\n"
"    background-color: #FFD8BA;\n"
"    color: #333F51;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QCalendarWidget QAbstractItemView::item:hover {\n"
"    background-color: white;\n"
"    border: 4px solid #FFD8BA;\n"
"}\n"
""
                        "\n"
"QCalendarWidget QTableView QHeaderView::section {\n"
"    color: #1E90FF;\n"
"    background-color: #FFD8BA;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_yearbutton,\n"
"QCalendarWidget QWidget#qt_calendar_monthbutton {\n"
"    color: #950505;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_yearbutton:hover,\n"
"QCalendarWidget QWidget#qt_calendar_monthbutton:hover {\n"
"    background-color: rgba(255, 255, 255, 0.1);\n"
"}\n"
"\n"
"QCalendarWidget:focus {\n"
"    outline: none;\n"
"}\n"
"\n"
"QCalendarWidget QMenu {\n"
"    background-color: #333F51;\n"
"    border: 1px solid #950505;\n"
"}\n"
"\n"
"QCalendarWidget QMenu::item {\n"
"    background-color: #FFD8BA;\n"
"    color: #950505;\n"
"    padding: 5px 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QCalendarWidget QMenu::item:selected {\n"
"    background-color: #FFD8BA;\n"
"    color: #950505; \n"
"    "
                        "border: 2px solid #950505;\n"
"}\n"
"\n"
"QCalendarWidget QMenu::item:hover {\n"
"    background-color: #FFD8BA;\n"
"    color: #950505; \n"
"    border: 2px solid #950505;\n"
"}\n"
""));
        calendarWidget->setFirstDayOfWeek(Qt::Monday);

        gridLayout->addWidget(calendarWidget, 2, 1, 2, 1);


        retranslateUi(Calendar);

        QMetaObject::connectSlotsByName(Calendar);
    } // setupUi

    void retranslateUi(QDialog *Calendar)
    {
        Calendar->setWindowTitle(QCoreApplication::translate("Calendar", "\320\232\320\260\320\273\320\265\320\275\320\264\320\260\321\200\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calendar: public Ui_Calendar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDAR_H
