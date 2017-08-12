#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

#include <QSqlQuery>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    //if(ui->lineEdit_username->text().trimmed() == tr("ljj-win7") && ui->lineEdit_password->text() == tr("123456"))
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
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("Waring"), tr("password error!"), QMessageBox::Yes);

        ui->lineEdit_password->clear();
        ui->lineEdit_password->setFocus();
    }
}
