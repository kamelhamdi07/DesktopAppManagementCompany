#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"perso.h"
#include"personnel.h"
//#include <mainwindow.h>
#include<QString>
//#include <signal.h>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    //login *log;

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void showTime();
    void on_pushButton_valide_2_clicked();

    void on_pushButton_Q_2_clicked();
signals:
    void userConnected(QString message);
private:
    Ui::login *ui;

};

#endif // LOGIN_H
