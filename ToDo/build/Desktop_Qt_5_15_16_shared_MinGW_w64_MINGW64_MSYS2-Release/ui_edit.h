/********************************************************************************
** Form generated from reading UI file 'edit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_H
#define UI_EDIT_H

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

class Ui_Edit
{
public:
    QGridLayout *gridLayout_7;
    QSpacerItem *verticalSpacer_14;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QLabel *task_date;
    QSpacerItem *verticalSpacer_12;
    QFrame *frame_5;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *ok_button;
    QSpacerItem *horizontalSpacer_8;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_task;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_time;
    QFrame *frame_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *task_time;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_9;
    QLineEdit *task_title;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_13;

    void setupUi(QDialog *Edit)
    {
        if (Edit->objectName().isEmpty())
            Edit->setObjectName(QString::fromUtf8("Edit"));
        Edit->resize(800, 600);
        Edit->setStyleSheet(QString::fromUtf8("background-color: #333F51;\n"
""));
        gridLayout_7 = new QGridLayout(Edit);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        verticalSpacer_14 = new QSpacerItem(20, 63, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_14, 0, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(67, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_11, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frame_4 = new QFrame(Edit);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setMinimumSize(QSize(622, 51));
        frame_4->setMaximumSize(QSize(622, 51));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: #FFD8BA;\n"
"border-radius: 8px;"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        task_date = new QLabel(frame_4);
        task_date->setObjectName(QString::fromUtf8("task_date"));
        task_date->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;\n"
"qproperty-alignment: 'AlignCenter';"));

        gridLayout_5->addWidget(task_date, 0, 0, 1, 1);


        verticalLayout_4->addWidget(frame_4);

        verticalSpacer_12 = new QSpacerItem(7, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_12);

        frame_5 = new QFrame(Edit);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setMinimumSize(QSize(622, 361));
        frame_5->setMaximumSize(QSize(622, 361));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: #FFFFFF;\n"
"border-radius: 8px;"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_5);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_11, 4, 2, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_10, 2, 2, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_10, 3, 3, 1, 2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_6, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        ok_button = new QPushButton(frame_5);
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

        gridLayout_6->addWidget(ok_button, 3, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_8, 1, 4, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_task = new QLabel(frame_5);
        label_task->setObjectName(QString::fromUtf8("label_task"));
        label_task->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;"));

        verticalLayout_2->addWidget(label_task);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);

        label_time = new QLabel(frame_5);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;"));

        verticalLayout_2->addWidget(label_time);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 3, 1);

        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setMinimumSize(QSize(325, 40));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 216, 186);\n"
"font-size: 16pt;"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_2 = new QWidget(frame_6);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 321, 41));
        task_time = new QHBoxLayout(horizontalLayoutWidget_2);
        task_time->setObjectName(QString::fromUtf8("task_time"));
        task_time->setContentsMargins(0, 0, 0, 0);

        gridLayout_2->addWidget(frame_6, 2, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 1, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_9, 1, 2, 1, 1);

        task_title = new QLineEdit(frame_5);
        task_title->setObjectName(QString::fromUtf8("task_title"));
        task_title->setMinimumSize(QSize(325, 40));
        task_title->setStyleSheet(QString::fromUtf8("background-color: #FFD8BA;\n"
"font-size: 16pt;"));

        gridLayout_2->addWidget(task_title, 0, 2, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 1, 1, 1, 3);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_9, 3, 0, 1, 2);


        verticalLayout_4->addWidget(frame_5);


        gridLayout_7->addLayout(verticalLayout_4, 1, 1, 2, 1);

        horizontalSpacer_12 = new QSpacerItem(67, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_12, 2, 2, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 63, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_13, 3, 1, 1, 1);


        retranslateUi(Edit);

        QMetaObject::connectSlotsByName(Edit);
    } // setupUi

    void retranslateUi(QDialog *Edit)
    {
        Edit->setWindowTitle(QCoreApplication::translate("Edit", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\267\320\260\320\264\320\260\321\207\320\270", nullptr));
        task_date->setText(QCoreApplication::translate("Edit", "05.04.2025", nullptr));
        ok_button->setText(QCoreApplication::translate("Edit", "\320\236\320\232", nullptr));
        label_task->setText(QCoreApplication::translate("Edit", "\320\227\320\260\320\264\320\260\321\207\320\260:", nullptr));
        label_time->setText(QCoreApplication::translate("Edit", "\320\222\321\200\320\265\320\274\321\217:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edit: public Ui_Edit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_H
