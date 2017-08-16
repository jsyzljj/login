#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

#include <QSqlQuery>
#include <QDebug>

#include "settingdialog.h"
#include "mainwindow.h"
#include "connection.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    m_server = "";
    m_database = "";
    m_username = "";
    m_password = "";

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    //if(ui->lineEdit_username->text().trimmed() == tr("ljj-win7") && ui->lineEdit_password->text() == tr("123456"))
    if (!createConnection(m_server, m_database, m_username, m_password))
    {
        QMessageBox::critical(0, qApp->tr("Connectting failure"),
            qApp->tr("Unable to establish a database connection."
                      ), QMessageBox::Cancel);
        return;
    }

    QString str_username = ui->lineEdit_username->text();
    QString str_password = "";
    bool flag_username = true;

    QSqlQuery query;
    query.exec("select * from log");
    while(query.next())
    {
        if (query.value(1).toString() == str_username)
        {
            str_password = query.value(2).toString();
            flag_username = false;
            break;
        }
    }

    if (flag_username)
    {
        QMessageBox::warning(this, tr("Waring"), tr("user name is not available !"), QMessageBox::Yes);

        ui->lineEdit_username->clear();
        ui->lineEdit_username->setFocus();
        ui->lineEdit_password->clear();
    }
    else if(ui->lineEdit_password->text() == str_password)
    {
        m_log_username = ui->lineEdit_username->text();
        m_log_password = ui->lineEdit_password->text();
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("Waring"), tr("password error!"), QMessageBox::Yes);

        ui->lineEdit_password->clear();
        ui->lineEdit_password->setFocus();
    }
}

void LoginDialog::on_pushButton_setting_clicked()
{
    SettingDialog *dlg = new SettingDialog;
    connect(dlg, SIGNAL(sendData_sql(QString,QString,QString,QString)),
            this, SLOT(receiveData_sql(QString,QString,QString,QString)));
    dlg->exec();
}

void LoginDialog::receiveData_sql(QString str_server, QString str_database, QString str_username, QString str_password)
{
    m_server = str_server;
    m_database = str_database;
    m_username = str_username;
    m_password = str_password;

    //qDebug() << m_server << m_database << m_username << m_password ;
}

QString LoginDialog::Get_Server()
{
    return m_server;
}

QString LoginDialog::Get_Database()
{
    return m_database;
}

QString LoginDialog::Get_Username()
{
    return m_username;
}

QString LoginDialog::Get_Password()
{
    return m_password;
}

QString LoginDialog::Get_Log_Username()
{
    return m_log_username;
}

QString LoginDialog::Get_Log_Password()
{
    return m_log_password;
}
