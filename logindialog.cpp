#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

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
    //accept();
    //if(ui->lineEdit_username->text().trimmed() == tr("ljj-win7") && ui->lineEdit_password->text() == tr("123456"))
    if(ui->lineEdit_username->text() == tr("ljj-win7") && ui->lineEdit_password->text() == tr("123456"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("Waring"), tr("user name or password error!"), QMessageBox::Yes);

        //ui->lineEdit_username->clear();
        //ui->lineEdit_username->setFocus();
        ui->lineEdit_password->clear();
        ui->lineEdit_password->setFocus();
    }
}
