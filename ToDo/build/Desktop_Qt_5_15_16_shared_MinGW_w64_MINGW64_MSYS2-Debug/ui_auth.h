/********************************************************************************
** Form generated from reading UI file 'auth.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTH_H
#define UI_AUTH_H

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

class Ui_Auth
{
public:
    QFrame *frame;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *usernameEdit;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;

    void setupUi(QDialog *Auth)
    {
        if (Auth->objectName().isEmpty())
            Auth->setObjectName(QString::fromUtf8("Auth"));
        Auth->resize(800, 600);
        Auth->setStyleSheet(QString::fromUtf8("background-color: #333F51;\n"
""));
        frame = new QFrame(Auth);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(110, 70, 601, 471));
        frame->setStyleSheet(QString::fromUtf8("background-color: #FFFFFF;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 601, 471));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(111, 31));
        label->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        usernameEdit = new QLineEdit(layoutWidget);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setMinimumSize(QSize(325, 42));
        usernameEdit->setStyleSheet(QString::fromUtf8("background-color: #FFD8BA;\n"
"font-size: 16pt;\n"
"border-radius: 8px;"));

        gridLayout->addWidget(usernameEdit, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(131, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe UI\";\n"
"color: #950505;"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        passwordEdit = new QLineEdit(layoutWidget);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setMinimumSize(QSize(325, 42));
        passwordEdit->setStyleSheet(QString::fromUtf8("background-color: #FFD8BA;\n"
"font-size: 16pt;\n"
"border-radius: 8px;"));

        gridLayout->addWidget(passwordEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 4, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        loginButton = new QPushButton(layoutWidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setMinimumSize(QSize(131, 42));
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout->addWidget(loginButton);

        registerButton = new QPushButton(layoutWidget);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setMinimumSize(QSize(201, 42));
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout->addWidget(registerButton);


        gridLayout_2->addLayout(verticalLayout, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 4, 1, 1);

        layoutWidget1 = new QWidget(Auth);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(Auth);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        layoutWidget->raise();
        layoutWidget->raise();
        frame->raise();

        retranslateUi(Auth);

        QMetaObject::connectSlotsByName(Auth);
    } // setupUi

    void retranslateUi(QDialog *Auth)
    {
        Auth->setWindowTitle(QCoreApplication::translate("Auth", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Auth", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("Auth", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        loginButton->setText(QCoreApplication::translate("Auth", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        registerButton->setText(QCoreApplication::translate("Auth", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Auth: public Ui_Auth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTH_H
