#include "auth_dialog.h"
#include "globals.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initialize_paths();
    current_user_id = -1;
    current_username = "";
    Auth_Dialog auth_dialog;
    auth_dialog.exec();
    return 0;
}
