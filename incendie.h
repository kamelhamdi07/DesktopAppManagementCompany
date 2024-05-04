#ifndef INCENDIE_H
#define INCENDIE_H
#include <iostream>
#include <string>

#include <QDialog>
#include "arduino.h"

#include<QTime>
#include <iostream>
#include <QThread>
#include"arduino.h"
#include <QSerialPort>
#include<QTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QThread>

using namespace std;


namespace Ui {
class incendie;
}

class incendie : public QDialog
{
    Q_OBJECT

public:

    explicit incendie(QDialog *parent = nullptr);
    ~incendie();



private slots:


    int lire_flamme();

    void flamme();


    void on_commencer_clicked();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimerTout() ;

    void on_supprimer_date_clicked();


private:

    Ui::incendie *ui;

    QByteArray data ;

    int test=0 ;

    QString Date1 ;
    QString Date2 ;

    arduino A ;


};







#endif // INCENDIE_H







