#include "authdialog.h"
#include "ui_auth.h"
#include "apiclient.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "calendar.h"
#include "globals.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth),
    apiClient(new ApiClient(this))
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    connect(apiClient, &ApiClient::loginSuccess, this, &AuthDialog::onLoginSuccess);
    connect(apiClient, &ApiClient::registrationSuccess, this, &AuthDialog::onRegistrationSuccess);
    connect(apiClient, &ApiClient::userChecked, this, &AuthDialog::onUserChecked);
    connect(ui->loginButton, &QPushButton::clicked, this, &AuthDialog::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &AuthDialog::on_registerButton_clicked);
    connect(apiClient, &ApiClient::loginError, this, &AuthDialog::onLoginError);
    connect(apiClient, &ApiClient::registrationError, this, &AuthDialog::onRegistrationError);
    connect(apiClient, &ApiClient::apiError, this, &AuthDialog::onApiError);
    isProcessing = false;
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

QMessageBox* AuthDialog::create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox* msgBox = new QMessageBox(parent);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet("background-color: white; color: black;");
    msgBox->setIcon(icon);
    return msgBox;
}

void AuthDialog::on_loginButton_clicked()
{
    if (isProcessing) {
        return;
    }
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox* msgBox = create_message_box(this, "Ошибка", "Заполните все поля", QMessageBox::Information);
        msgBox->show();
        return;
    }
    isProcessing = true;
    currentUsername = username;
    currentPassword = password;
    apiClient->checkUserExists(username);
}

void AuthDialog::on_registerButton_clicked()
{
    if (isProcessing) {
        return;
    }
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox* msgBox = create_message_box(this, "Ошибка", "Заполните все поля", QMessageBox::Information);
        msgBox->show();
        return;
    }
    isProcessing = true;
    currentUsername = username;
    currentPassword = password;
    apiClient->registerUser(username, password);
}

void AuthDialog::onLoginSuccess()
{
    isProcessing = false;
    accept();
    Calendar calendarWindow;
    calendarWindow.exec();
}

void AuthDialog::onRegistrationSuccess()
{
    apiClient->loginUser(currentUsername, currentPassword);
}

void AuthDialog::onUserChecked(bool exists)
{
    if (!exists) {
        isProcessing = false;
        QMessageBox* msgBox = create_message_box(this, "Ошибка", "Пользователь с таким именем не зарегистрирован", QMessageBox::Critical);
        msgBox->show();
    } else {
        apiClient->loginUser(currentUsername, currentPassword);
    }
}

void AuthDialog::onLoginError(const QString& errorMessage)
{
    isProcessing = false;
    static bool errorShown = false;
    if (!errorShown) {
        errorShown = true;
        QMessageBox* msgBox = create_message_box(this, "Ошибка при входе", errorMessage, QMessageBox::Critical);
        msgBox->show();
        errorShown = false;
    }
}

void AuthDialog::onRegistrationError(const QString& errorMessage)
{
    isProcessing = false;
    static bool errorShown = false;
    if (!errorShown) {
        errorShown = true;
        QMessageBox* msgBox = create_message_box(this, "Ошибка при регистрации", errorMessage, QMessageBox::Critical);
        msgBox->show();
        errorShown = false;
    }
}

void AuthDialog::onApiError(const QString& errorMessage)
{
    isProcessing = false;
    static bool errorShown = false;
    if (!errorShown) {
        errorShown = true;
        QMessageBox* msgBox = create_message_box(this, "Ошибка соединения с сервером", errorMessage, QMessageBox::Critical);
        msgBox->show();
        errorShown = false;
    }
}
