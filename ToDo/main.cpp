#include "authdialog.h"
#include "globals.h"
#include "calendar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthDialog authDialog;
    authDialog.exec();
    return 0;


    // QApplication a(argc, argv);
    // AuthDialog authDialog;
    // authDialog.show();
    // return a.exec();
}
