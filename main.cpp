#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "logindialog.h"
#include "connection.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QApplication a(argc, argv);

    LoginDialog dlg;

    if (dlg.exec() == QDialog::Accepted)
    {
        //qDebug() << dlg.Get_Server() << dlg.Get_Database() << dlg.Get_Username() << dlg.Get_Password() ;
        MainWindow *w = new MainWindow;

        w->mp_server = dlg.Get_Server();
        w->mp_database = dlg.Get_Database();
        w->mp_username = dlg.Get_Username();
        w->mp_password = dlg.Get_Password();

        w->mp_log_username = dlg.Get_Log_Username();

        qDebug() << "w->mp_log_username = " <<w->mp_log_username;

        w->show();
        //return a.exec();
    }
    else
    {
        return 0;
    }

    return a.exec();

}
