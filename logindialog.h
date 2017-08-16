#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_setting_clicked();

    //接收传递过来的数据的槽
    void receiveData_sql(QString str_server, QString str_database, QString str_username, QString str_password);

private:
    Ui::LoginDialog *ui;

    QString m_server, m_database, m_username, m_password;

    QString m_log_username, m_log_password;

public:
    QString Get_Server();
    QString Get_Database();
    QString Get_Username();
    QString Get_Password();

    QString Get_Log_Username();
    QString Get_Log_Password();
};

#endif // LOGINDIALOG_H
