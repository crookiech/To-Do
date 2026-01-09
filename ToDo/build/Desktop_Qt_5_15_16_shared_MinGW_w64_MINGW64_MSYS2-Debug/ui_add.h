/********************************************************************************
** Form generated from reading UI file 'add.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_H
#define UI_ADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *task_date;
    QSpacerItem *verticalSpacer_8;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_task;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_time;
    QFrame *frame_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *task_time;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLineEdit *task_title;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QPushButton *ok_button;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *Add)
    {
        if (Add->objectName().isEmpty())
            Add->setObjectName(QString::fromUtf8("Add"));
        Add->resize(800, 600);
        Add->setStyleSheet(QString::fromUtf8("background-color: #333F51;\n"
""));
        gridLayout_2 = new QGridLayout(Add);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(Add);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(622, 51));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #FFD8BA;\n"
"border-radius: 8px;\n"
"qproperty-alignment: 'AlignCenter';"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        task_date = new QLabel(frame_2);
        task_date->setObjectName(QString::fromUtf8("task_date"));
        task_date->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;\n"
"qproperty-alignment: 'AlignCenter';"));

        gridLayout_3->addWidget(task_date, 0, 0, 1, 1);


        verticalLayout_3->addWidget(frame_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);

        frame = new QFrame(Add);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(619, 361));
        frame->setStyleSheet(QString::fromUtf8("background-color: #FFFFFF;\n"
"border-radius: 8px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_5, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_task = new QLabel(frame);
        label_task->setObjectName(QString::fromUtf8("label_task"));
        label_task->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;"));

        verticalLayout->addWidget(label_task);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_time = new QLabel(frame);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;"));

        verticalLayout->addWidget(label_time);


        gridLayout->addLayout(verticalLayout, 0, 0, 3, 1);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(325, 40));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 216, 186);\n"
"font-size: 16pt;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget = new QWidget(frame_3);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 321, 41));
        task_time = new QHBoxLayout(horizontalLayoutWidget);
        task_time->setObjectName(QString::fromUtf8("task_time"));
        task_time->setContentsMargins(0, 0, 0, 0);

        gridLayout->addWidget(frame_3, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 1);

        task_title = new QLineEdit(frame);
        task_title->setObjectName(QString::fromUtf8("task_title"));
        task_title->setMinimumSize(QSize(325, 40));
        task_title->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 216, 186);\n"
"font-size: 16pt;"));

        gridLayout->addWidget(task_title, 0, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout, 1, 1, 1, 3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 2, 2, 1, 1);

        ok_button = new QPushButton(frame);
        ok_button->setObjectName(QString::fromUtf8("ok_button"));
        ok_button->setMinimumSize(QSize(131, 40));
        ok_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  font: 700 18pt \"Segoe UI\";\n"
"  background-color: #FFD8BA; \n"
"  border: 1px solid gray;\n"
"  border-radius: 8px;\n"
"  color: #333F51;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #ebc7ab;\n"
"}\n"
""));

        gridLayout_4->addWidget(ok_button, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 4, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 3, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 3, 3, 1, 2);


        verticalLayout_3->addWidget(frame);


        gridLayout_2->addLayout(verticalLayout_3, 1, 1, 2, 1);

        horizontalSpacer_6 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 2, 2, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 98, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 3, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 99, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 0, 1, 1, 1);


        retranslateUi(Add);

        QMetaObject::connectSlotsByName(Add);
    } // setupUi

    void retranslateUi(QDialog *Add)
    {
        Add->setWindowTitle(QCoreApplication::translate("Add", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\320\264\320\260\321\207\320\270", nullptr));
        task_date->setText(QCoreApplication::translate("Add", "05.04.2025", nullptr));
        label_task->setText(QCoreApplication::translate("Add", "\320\227\320\260\320\264\320\260\321\207\320\260:", nullptr));
        label_time->setText(QCoreApplication::translate("Add", "\320\222\321\200\320\265\320\274\321\217:", nullptr));
        ok_button->setText(QCoreApplication::translate("Add", "\320\236\320\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add: public Ui_Add {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_H
