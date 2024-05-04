#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include"login.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();
public slots:
     void displayMessage(QString message);
     void setAdminButtonsVisible(bool visible);
     void settechButtonsVisible(bool visible);
     void setsecButtonsVisible(bool visible);
private slots:
    void on_bn_pers_clicked();

 //   void on_home_clicked();


    void on_bn_pub_clicked();

    void on_bn_mat_clicked();

    void on_bn_conf_clicked();

    void on_bn_help_clicked();

private:
    Ui::Home *ui;
    login* loginWindow;
};
#endif // HOME_H
