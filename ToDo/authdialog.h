#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Auth;
}

class ApiClient;

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    ~AuthDialog();
    QMessageBox* create_message_box(QWidget* parent, const QString& title, const QString& text, QMessageBox::Icon icon);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void onLoginSuccess();
    void onRegistrationSuccess();
    void onUserChecked(bool exists);
    void onLoginError(const QString& errorMessage);
    void onRegistrationError(const QString& errorMessage);
    void onApiError(const QString& errorMessage);

private:
    Ui::Auth *ui;
    ApiClient* apiClient;
    QString currentUsername;
    QString currentPassword;
    bool isProcessing;
};

#endif // AUTHDIALOG_H
