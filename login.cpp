#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QPixmap>
#include "admin.h"
#include"personnel.h"
#include"home.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include "perso.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include<QString>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{



    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    ui->lineEdit_login_2->setPlaceholderText("username");
    ui->lineEdit_password_2->setPlaceholderText("Password ");


}
void login::showTime()
{
    QTime time=QTime ::currentTime();
    QString time_texte=time.toString("hh : mm : ss");
    if((time.second() % 2)==0)
    { time_texte[3]= ' ';
        time_texte[8]= ' ';
    }
    ui->Digital_clock->setText(time_texte);
}
login::~login()
{
    delete ui;

}


/*void login::on_pushButton_valide_2_clicked()
{
    user l;
        Home w;

        l.setLogin(ui->lineEdit_login_2->text());
        l.setPassword(ui->lineEdit_password_2->text());

        // Vérification des informations d'identification à partir de la base de données
        QSqlQuery query;
        query.prepare("SELECT  ROLE FROM utilisateurs WHERE login = :login");
        query.bindValue(":login", l.Getlogin());
        if (query.exec() && query.next()) {
            QString password = query.value(0).toString();
            QString ROLE = query.value(0).toString();
            QMessageBox::information(this, "Bienvenue",ROLE);
            if ((password == l.GetPassword()&&(ROLE == "Admin"))) {
                hide();
                w.setAdminButtonsVisible(true);
                w.settechButtonsVisible(false);
                w.show();
                w.setAdminButtonsVisible(true);
                w.settechButtonsVisible(false);
            }
            else if (ROLE == "technicien"){
                hide();
                //w.setAdminButtonsVisible(false);
                //w.settechButtonsVisible(true);
               // QMessageBox::information(this, "Bienvenue","Vous êtes connecté en tant qu'tech.");
                w.show();
                w.setAdminButtonsVisible(false);
               w.settechButtonsVisible(true);
             //  QMessageBox::information(this, "Bienvenue","Vous êtes connecté en tant qu'tech.");
              // w.show();
           } else {
                int rep = QMessageBox::question(this, "Message d'erreur", "mots de passe ou login incorrecte?", QMessageBox ::Yes | QMessageBox::No);
                if (rep == QMessageBox::No) {
                    QMessageBox::information(this, "Sorry", "tu peut pas accéder à cette application!");
                    close();
                } else if (rep == QMessageBox::Yes) {
                    QMessageBox::critical(this, "Attention", "faire attention une autre fois ");
                }
            }
        } else {
            QMessageBox::warning(this, "yo yo ", "il faux saisir login & Password");
        }
    }
*/

// Connexion du signal clicked() du bouton Valider à un slot
//connect(ui->pushButton_valide_2, &QPushButton::clicked, this, &void login::on_pushButton_valide_2_clicked);
//connect(ui->pushButton_valide_2, &QPushButton::clicked, this, &login::on_pushButton_valide_2_clicked);

// Définition du slot pour le bouton Valider
/*void login::on_pushButton_valide_2_clicked() {
    //connect(ui->pushButton_valide_2, &QPushButton::clicked, this, &login::on_pushButton_valide_2_clicked());
    connect(ui->pushButton_valide_2, &QPushButton::clicked, this, &login::on_pushButton_valide_2_clicked);
*/
    void login::on_pushButton_valide_2_clicked()
    {
        user l;
        Home *w = new Home();  // create a new instance of Home

        l.setLogin(ui->lineEdit_login_2->text());
        l.setPassword(ui->lineEdit_password_2->text());

        // Vérification des informations d'identification à partir de la base de données
        QSqlQuery query;
        query.prepare("SELECT ROLE FROM utilisateurs WHERE login = :login");
        query.bindValue(":login", l.Getlogin());

        if (query.exec() && query.next()) {
            QString password = query.value(0).toString();
            QString ROLE = query.value(0).toString();
            QMessageBox::information(this, "Bienvenue", ROLE);

            if ((password == l.GetPassword() && ROLE == "Admin")) {
                hide();
                w->setAdminButtonsVisible(true);
                w->settechButtonsVisible(false);
            } else if (ROLE == "technicien") {
                hide();
                w->setAdminButtonsVisible(false);
                w->settechButtonsVisible(true);
            }else if (ROLE == "secretaire") {
                hide();
                w->setAdminButtonsVisible(false);
                w->settechButtonsVisible(false);
                w->setsecButtonsVisible(true);
            }
            else {
                int rep = QMessageBox::question(this, "Message d'erreur", "mots de passe ou login incorrecte?", QMessageBox::Yes | QMessageBox::No);
                if (rep == QMessageBox::No) {
                    QMessageBox::information(this, "Sorry", "tu peut pas accéder à cette application!");
                    close();
                } else if (rep == QMessageBox::Yes) {
                    QMessageBox::critical(this, "Attention", "faire attention une autre fois ");
                }
            }

            w->show();  // show the Home window
        } else {
            QMessageBox::warning(this, "yo yo ", "il faux saisir login & Password");
        }
    }

void login::on_pushButton_Q_2_clicked()
{

int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur tu veux quitter?", QMessageBox ::Yes | QMessageBox::No);

if (reponse == QMessageBox::Yes)
{
    QMessageBox::critical(this, "Message", "A la prochaine !");
    close();
}
else if (reponse == QMessageBox::No)
{
    QMessageBox::information(this, "Helloo", "Alors bienvenue!");
}
}
