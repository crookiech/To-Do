/********************************************************************************
** Form generated from reading UI file 'todo_list.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODO_LIST_H
#define UI_TODO_LIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ToDo_List
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *add_task;
    QSpacerItem *verticalSpacer_3;
    QPushButton *edit_task;
    QSpacerItem *verticalSpacer_2;
    QPushButton *delete_task;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer;
    QPushButton *calendar_button;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_2;
    QLabel *label_date;
    QListWidget *list_tasks;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_7;

    void setupUi(QDialog *ToDo_List)
    {
        if (ToDo_List->objectName().isEmpty())
            ToDo_List->setObjectName(QString::fromUtf8("ToDo_List"));
        ToDo_List->resize(800, 600);
        ToDo_List->setStyleSheet(QString::fromUtf8("#ToDoList{\n"
"background-color: #333F51;}\n"
""));
        gridLayout_2 = new QGridLayout(ToDo_List);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_5 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 0, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(ToDo_List);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(131, 450));
        frame->setMaximumSize(QSize(131, 450));
        frame->setStyleSheet(QString::fromUtf8("background-color: #FFFFFF;\n"
"border-radius: 8px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_8 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_8, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(8, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        add_task = new QPushButton(frame);
        add_task->setObjectName(QString::fromUtf8("add_task"));
        add_task->setMinimumSize(QSize(75, 75));
        add_task->setMaximumSize(QSize(75, 75));

        verticalLayout_2->addWidget(add_task);

        verticalSpacer_3 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        edit_task = new QPushButton(frame);
        edit_task->setObjectName(QString::fromUtf8("edit_task"));
        edit_task->setMinimumSize(QSize(75, 75));
        edit_task->setMaximumSize(QSize(75, 75));

        verticalLayout_2->addWidget(edit_task);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        delete_task = new QPushButton(frame);
        delete_task->setObjectName(QString::fromUtf8("delete_task"));
        delete_task->setMinimumSize(QSize(75, 75));
        delete_task->setMaximumSize(QSize(75, 75));

        verticalLayout_2->addWidget(delete_task);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(4, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_10, 2, 1, 1, 1);


        verticalLayout->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        calendar_button = new QPushButton(ToDo_List);
        calendar_button->setObjectName(QString::fromUtf8("calendar_button"));
        calendar_button->setMinimumSize(QSize(131, 61));
        calendar_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  font: 700 14pt \"Segoe UI\";\n"
"  background-color: #FFD8BA; \n"
"  border: 1px solid gray;\n"
"  border-radius: 8px;\n"
"  color: #333F51;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #ebc7ab;\n"
"}\n"
""));

        verticalLayout->addWidget(calendar_button);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frame_2 = new QFrame(ToDo_List);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(560, 500));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FFFFFF;\n"
"border-radius: 8px;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_date = new QLabel(frame_2);
        label_date->setObjectName(QString::fromUtf8("label_date"));
        label_date->setGeometry(QRect(220, 490, 111, 31));
        label_date->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\";\n"
"color: rgba(61, 61, 61, 0.6);\n"
""));
        list_tasks = new QListWidget(frame_2);
        list_tasks->setObjectName(QString::fromUtf8("list_tasks"));
        list_tasks->setGeometry(QRect(59, 59, 441, 411));
        list_tasks->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: #950505;"));

        horizontalLayout->addWidget(frame_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 2, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 2, 2, 1, 1);


        retranslateUi(ToDo_List);

        QMetaObject::connectSlotsByName(ToDo_List);
    } // setupUi

    void retranslateUi(QDialog *ToDo_List)
    {
        ToDo_List->setWindowTitle(QCoreApplication::translate("ToDo_List", "To Do", nullptr));
        add_task->setText(QString());
        edit_task->setText(QString());
        delete_task->setText(QString());
        calendar_button->setText(QCoreApplication::translate("ToDo_List", "\320\272\320\260\320\273\320\265\320\275\320\264\320\260\321\200\321\214", nullptr));
        label_date->setText(QCoreApplication::translate("ToDo_List", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">05.04.2025</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToDo_List: public Ui_ToDo_List {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODO_LIST_H
