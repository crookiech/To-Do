#include "auth_dialog.h"
#include "ui_auth.h"
#include "api_client.h"
#include "calendar.h"
#include "globals.h"
#include <QMessageBox>

Auth_Dialog::Auth_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth),
    api_client(new Api_Client(this))
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    connect(api_client, &Api_Client::login_success, this, &Auth_Dialog::on_login_success);
    connect(api_client, &Api_Client::registration_success, this, &Auth_Dialog::on_registration_success);
    connect(api_client, &Api_Client::user_checked, this, &Auth_Dialog::on_user_checked);
    connect(ui->loginButton, &QPushButton::clicked, this, &Auth_Dialog::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &Auth_Dialog::on_registerButton_clicked);
    connect(api_client, &Api_Client::login_error, this, &Auth_Dialog::on_login_error);
    connect(api_client, &Api_Client::registration_error, this, &Auth_Dialog::on_registration_error);
    connect(api_client, &Api_Client::api_error, this, &Auth_Dialog::on_api_error);
    is_processing = false;
}

Auth_Dialog::~Auth_Dialog()
{
    delete ui;
}

QMessageBox* Auth_Dialog::create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox* msg_box = new QMessageBox(parent);
    msg_box->setWindowTitle(title);
    msg_box->setText(text);
    msg_box->setStyleSheet("background-color: white; color: black;");
    msg_box->setIcon(icon);
    return msg_box;
}

void Auth_Dialog::on_loginButton_clicked()
{
    if (is_processing) {
        return;
    }
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox* msg_box = create_message_box(this, "Ошибка", "Заполните все поля", QMessageBox::Information);
        msg_box->show();
        return;
    }
    is_processing = true;
    current_username = username;
    current_password = password;
    api_client->check_user_exists(username);
}

void Auth_Dialog::on_registerButton_clicked()
{
    if (is_processing) {
        return;
    }
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox* msg_box = create_message_box(this, "Ошибка", "Заполните все поля", QMessageBox::Information);
        msg_box->show();
        return;
    }
    is_processing = true;
    current_username = username;
    current_password = password;
    api_client->register_user(username, password);
}

void Auth_Dialog::on_login_success(int user_id)
{
    is_processing = false;
    current_user_id = user_id;
    current_username = current_username;
    accept();
    Calendar calendar_window;
    calendar_window.exec();
}

void Auth_Dialog::on_registration_success()
{
    api_client->login_user(current_username, current_password);
}

void Auth_Dialog::on_user_checked(bool exists)
{
    if (!exists) {
        is_processing = false;
        QMessageBox* msg_box = create_message_box(this, "Ошибка", "Пользователь с таким именем не зарегистрирован", QMessageBox::Critical);
        msg_box->show();
    } else {
        api_client->login_user(current_username, current_password);
    }
}

void Auth_Dialog::on_login_error(const QString& error_message)
{
    is_processing = false;
    static bool error_shown = false;
    if (!error_shown) {
        error_shown = true;
        QMessageBox* msg_box = create_message_box(this, "Ошибка при входе", error_message, QMessageBox::Critical);
        msg_box->show();
        error_shown = false;
    }
}

void Auth_Dialog::on_registration_error(const QString& error_message)
{
    is_processing = false;
    static bool error_shown = false;
    if (!error_shown) {
        error_shown = true;
        QMessageBox* msg_box = create_message_box(this, "Ошибка при регистрации", error_message, QMessageBox::Critical);
        msg_box->show();
        error_shown = false;
    }
}

void Auth_Dialog::on_api_error(const QString& error_message)
{
    is_processing = false;
    static bool error_shown = false;
    if (!error_shown) {
        error_shown = true;
        QMessageBox* msg_box = create_message_box(this, "Ошибка соединения с сервером", error_message, QMessageBox::Critical);
        msg_box->show();
        error_shown = false;
    }
}
