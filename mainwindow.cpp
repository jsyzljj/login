#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"

#include <QDebug>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = mp_server;
    m_database = mp_database;
    m_username = mp_username;
    m_password = mp_password;

    m_log_username = mp_log_username;

    qDebug() <<"m_log_username = " << m_log_username;
    qDebug() <<"m_log_password = " << m_log_password;

    // login user
    QString str_log_username = "Login User : " + m_log_username;
    // login time
    m_time_login = QDateTime::currentDateTime();
    m_str_time_login =m_time_login.toString("yyyy-MM-dd hh:mm:ss ddd");
    QString str_label_log_time = "Login Time : " + m_str_time_login;
    // login duration
    m_time_now = QDateTime::currentDateTime();
    m_str_time_duration = Change_to_two_numbers( QString::number(m_time_login.msecsTo(m_time_now)%3600000/60000) )
            + " : "
            + Change_to_two_numbers( QString::number(m_time_login.msecsTo(m_time_now)%60000/1000) );
    QString str_label_log_duration = "Login Duration : " + m_str_time_duration;

    // set label
    ui->label_log_username->setText(str_log_username);
    ui->label_log_time->setText(str_label_log_time);
    ui->label_log_duration->setText(str_label_log_duration);

    /*timer*/
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);

    /*id_time_logout*/
    id_time_logout = startTimer(125000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerUpdate()
{
   m_time_now = QDateTime::currentDateTime();

   m_str_time_duration = Change_to_two_numbers( QString::number(m_time_login.msecsTo(m_time_now)%3600000/60000) )
           + " : "
           + Change_to_two_numbers( QString::number(m_time_login.msecsTo(m_time_now)%60000/1000) );

   QString str_label_log_duration = "Login Duration : " + m_str_time_duration;
   ui->label_log_duration->setText(str_label_log_duration);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
   if (event->timerId() == id_time_logout)
   {
       //on_pushButton_logout_clicked();
   }
   else
   {
       qApp->quit();
   }
}

//void MainWindow::closeEvent(QCloseEvent *event)
//{
//    LoginDialog dlg;

//    if (dlg.exec() == QDialog::Accepted)
//    {
//        MainWindow *w = new MainWindow;
//        w->show();
//    }
//}

void MainWindow::on_pushButton_logout_clicked()
{
    LoginDialog dlg;

    if (dlg.exec() == QDialog::Accepted)
    {
        MainWindow *w = new MainWindow;
        w->show();
    }
}

QString MainWindow::Change_to_two_numbers(QString str_in)
{
    QString str_temp, str_out;
    int num = str_in.toInt();
    if (num / 10)
    {
        str_temp = "";
    }
    else
    {
        str_temp = "0";
    }

    str_out = str_temp + str_in;

    return str_out;
}
