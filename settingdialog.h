#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_pushButton_test_clicked();

    void on_pushButton_save_clicked();

signals:
    void sendData_sql(QString,QString,QString,QString);         //用来传递数据的信号

private:
    Ui::SettingDialog *ui;

    void update_log_info(QString str_server, QString str_database, QString str_username);
};

#endif // SETTINGDIALOG_H
