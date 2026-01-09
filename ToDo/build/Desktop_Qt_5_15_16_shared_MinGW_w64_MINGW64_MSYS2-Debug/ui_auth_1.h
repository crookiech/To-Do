/********************************************************************************
** Form generated from reading UI file 'auth_1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTH_1_H
#define UI_AUTH_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Auth
{
public:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;

    void setupUi(QDialog *Auth)
    {
        if (Auth->objectName().isEmpty())
            Auth->setObjectName(QString::fromUtf8("Auth"));
        Auth->resize(400, 300);
        usernameEdit = new QLineEdit(Auth);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setGeometry(QRect(100, 110, 113, 22));
        passwordEdit = new QLineEdit(Auth);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setGeometry(QRect(60, 170, 113, 22));
        loginButton = new QPushButton(Auth);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(210, 230, 75, 24));
        registerButton = new QPushButton(Auth);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setGeometry(QRect(210, 260, 75, 24));

        retranslateUi(Auth);

        QMetaObject::connectSlotsByName(Auth);
    } // setupUi

    void retranslateUi(QDialog *Auth)
    {
        Auth->setWindowTitle(QCoreApplication::translate("Auth", "Dialog", nullptr));
        loginButton->setText(QCoreApplication::translate("Auth", "PushButton", nullptr));
        registerButton->setText(QCoreApplication::translate("Auth", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Auth: public Ui_Auth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTH_1_H
