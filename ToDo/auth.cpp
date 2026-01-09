// #include "auth.h"
// #include "ui_auth_1.h"
// #include <QMessageBox>

// Auth::Auth(QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::Auth),
//     m_apiClient(new Api_Client(this))
// {
//     ui->setupUi(this);

//     connect(m_apiClient, &Api_Client::loginSuccess, this, &Auth::on_loginSuccess);
//     connect(m_apiClient, &Api_Client::registerSuccess, this, &Auth::on_registerSuccess);
//     connect(m_apiClient, &Api_Client::loginError, this, &Auth::on_error);
//     connect(m_apiClient, &Api_Client::registerError, this, &Auth::on_error);
//     connect(m_apiClient, &Api_Client::error, this, &Auth::on_error);
// }

// Auth::~Auth() {
//     delete ui;
// }

// void Auth::on_loginButton_clicked() {
//     QString username = ui->usernameEdit->text();
//     QString password = ui->passwordEdit->text();

//     if (username.isEmpty() || password.isEmpty()) {
//         QMessageBox::warning(this, "Ошибка", "Заполните все поля");
//         return;
//     }

//     m_apiClient->loginUser(username, password);
// }

// void Auth::on_registerButton_clicked() {
//     QString username = ui->usernameEdit->text();
//     QString password = ui->passwordEdit->text();

//     if (username.isEmpty() || password.isEmpty()) {
//         QMessageBox::warning(this, "Ошибка", "Заполните все поля");
//         return;
//     }

//     m_apiClient->registerUser(username, password);
// }

// void Auth::on_loginSuccess(int userId, const QString &username) {
//     emit authenticated(userId, username);
//     accept();
// }

// void Auth::on_registerSuccess(int userId, const QString &username) {
//     QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
//     emit authenticated(userId, username);
//     accept();
// }

// void Auth::on_error(const QString &error) {
//     QMessageBox::critical(this, "Ошибка", error);
// }
