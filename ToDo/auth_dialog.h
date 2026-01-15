#ifndef AUTH_DIALOG_H
#define AUTH_DIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Auth;
}

class Api_Client;

class Auth_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Auth_Dialog(QWidget *parent = nullptr);
    ~Auth_Dialog();
    QMessageBox* create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_login_success(int user_id);
    void on_registration_success();
    void on_user_checked(bool exists);
    void on_login_error(const QString& error_message);
    void on_registration_error(const QString& error_message);
    void on_api_error(const QString& error_message);

private:
    Ui::Auth *ui;
    Api_Client* api_client;
    QString current_username;
    QString current_password;
    bool is_processing;
};

#endif // AUTH_DIALOG_H
