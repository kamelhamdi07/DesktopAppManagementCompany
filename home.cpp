#include "home.h"
#include "ui_home.h"
#include "ui_perso.h"
#include"perso.h"
#include"conf.h"
#include"QMessageBox"
#include"personnel.h"
#include "login.h"
#include "admin.h"
#include "materille.h"
#include "mat.h"
#include"QDebug"
#include"dialog.h"
#include<QString>
#include "reff.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    // Create an instance of the login window
        //loginWindow = new login(this);

        // Connect the signal from the login window to the slot in the main window
       // QObject::connect(loginWindow, SIGNAL(userConnected(QString)),
                      //   this, SLOT(displayMessage(QString)));
//connect(loginWindow, &login::userConnected, this, &Home::displayMessage);
    // Connexion du signal clicked() du bouton Valider à un slot
   // connect(ui->pushButton_valide_2, &QPushButton::clicked, this, &void login::on_pushButton_valide_2_clicked);
}

Home::~Home()
{
    delete ui;
}

void Home::on_bn_pers_clicked()
{ perso pers;
    pers.setModal(true);
    pers.exec();
}


/*void MainWindow::on_home_clicked()
{ login login;
    login.setModal(true);
    login.exec();

}*/
void Home::displayMessage(QString message)
{  message="Beinvenue";
    ui->label_message->setText(message);
}
void Home::setAdminButtonsVisible(bool visible) {
    ui->bn_pers->setVisible(visible);
    ui->bn_mat->setVisible(visible);
    ui->bn_conf->setVisible(visible);
    ui->bn_cher->setVisible(visible);
    ui->bn_pub->setVisible(visible);
}
void Home::settechButtonsVisible(bool visible) {
    ui->bn_pers->setVisible(!visible);
    ui->bn_mat->setVisible(visible);
    ui->bn_conf->setVisible(!visible);
    ui->bn_cher->setVisible(!visible);
    ui->bn_pub->setVisible(!visible);
}
void Home::setsecButtonsVisible(bool visible) {
    ui->bn_pers->setVisible(!visible);
    ui->bn_mat->setVisible(!visible);
    ui->bn_conf->setVisible(visible);
    ui->bn_cher->setVisible(!visible);
    ui->bn_pub->setVisible(!visible);
}

void Home::on_bn_pub_clicked()
{
    Dialog pers;
        pers.setModal(true);
        pers.exec();
}

void Home::on_bn_mat_clicked()
{
    materille pers;
        pers.setModal(true);
        pers.exec();
}

void Home::on_bn_conf_clicked()
{
    conf pers;
        pers.setModal(true);
        pers.exec();
}

void Home::on_bn_help_clicked()
{
    reff pers;
    pers.setModal(true);
    pers.exec();
}
