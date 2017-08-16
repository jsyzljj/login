#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString mp_server, mp_database, mp_username, mp_password;
    QString mp_log_username, mp_log_password;

private:
    Ui::MainWindow *ui;

    QString m_server, m_database, m_username, m_password;
    QString m_log_username, m_log_password;
    QString m_str_time_login, m_str_time_now, m_str_time_duration;
    QDateTime m_time_login, m_time_now, m_time_duration;
    int id_time_logout;

    QString Change_to_two_numbers(QString str_in);

private slots:
    void timerUpdate();
    void on_pushButton_logout_clicked();

protected:
    void timerEvent(QTimerEvent *);
    //void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
