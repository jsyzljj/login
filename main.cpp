#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection())
        return 1;

    MainWindow w;
    LoginDialog dlg;

    if (dlg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
