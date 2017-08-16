#include "settingdialog.h"
#include "ui_settingdialog.h"

#include "connection.h"

#include <QtXml>
#include <QDebug>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    // xml
    QFile file("F:/work/qt/login/config.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file";
        return ;
    }
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        qDebug() << "Failed to doc.setContent";
        return ;
    }
    file.close();

    //返回根节点及其子节点的元素标记名
    QDomElement docElem = doc.documentElement();  //返回根元素
    QDomNode n = docElem.firstChild();   //返回根节点的第一个子节点
    while(!n.isNull())  //如果节点不为空
    {
        if (n.isElement() && n.toElement().tagName() == "log") //如果节点是元素
        {
            QDomElement e = n.toElement(); //将其转换为元素

            QDomNodeList list = e.childNodes();
            for(int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                {
                    if (node.toElement().tagName() == "server")
                    {
                        ui->lineEdit_server->setText(node.toElement().text());
                    }
                    else if (node.toElement().tagName() == "database")
                    {
                        ui->lineEdit_database->setText(node.toElement().text());
                    }
                    else if (node.toElement().tagName() == "username")
                    {
                        ui->lineEdit_username->setText(node.toElement().text());
                    }
                }
            }
        }
        n = n.nextSibling();  //下一个兄弟节点
    }

    ui->lineEdit_password->setFocus();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButton_test_clicked()
{
    QString str_server, str_database, str_username, str_password;

    str_server = ui->lineEdit_server->text();
    str_database = ui->lineEdit_database->text();
    str_username = ui->lineEdit_username->text();
    str_password = ui->lineEdit_password->text();

    emit sendData_sql(str_server, str_database, str_username, str_password);

    if (createConnection(str_server, str_database, str_username, str_password))
    {
        QMessageBox::information(0, qApp->tr("Connectting success"),
            qApp->tr("Able to establish a database connection."
                      ), QMessageBox::Cancel);
        update_log_info(str_server, str_database, str_username);
    }
    else
    {
        QMessageBox::critical(0, qApp->tr("Connectting failure"),
            qApp->tr("Unable to establish a database connection."
                      ), QMessageBox::Cancel);
    }
}

void SettingDialog::on_pushButton_save_clicked()
{
    QString str_server, str_database, str_username, str_password;

    str_server = ui->lineEdit_server->text();
    str_database = ui->lineEdit_database->text();
    str_username = ui->lineEdit_username->text();
    str_password = ui->lineEdit_password->text();

    emit sendData_sql(str_server, str_database, str_username, str_password);

    if (createConnection(str_server, str_database, str_username, str_password))
    {
        update_log_info(str_server, str_database, str_username);
        QMessageBox::information(0, qApp->tr("Connectting success"),
            qApp->tr("Save database info success."
                      ), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(0, qApp->tr("Connectting failure"),
            qApp->tr("Unable to establish a database connection."
                      ), QMessageBox::Cancel);
    }
}

void SettingDialog::update_log_info(QString str_server, QString str_database, QString str_username)
{
    QFile file("F:/work/qt/login/config.xml");
    if (!file.open(QIODevice::ReadOnly))
        return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName("log");

    // 以标签名进行查找
    for(int i=0; i<list.count(); i++)
    {
        QDomNodeList child = list.at(i).childNodes();

        child.at(0).toElement().firstChild().setNodeValue(str_server);
        child.at(1).toElement().firstChild().setNodeValue(str_database);
        child.at(2).toElement().firstChild().setNodeValue(str_username);
        QFile file("F:/work/qt/login/config.xml");     //保存更改
        if(!file.open(QIODevice::WriteOnly))
           return ;
        QTextStream out(&file);
        doc.save(out,4);   //保存文档，4为子元素缩进字符数
        file.close();
    }
}
