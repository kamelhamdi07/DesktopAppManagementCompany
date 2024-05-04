#ifndef CONFERENCE_H
#define CONFERENCE_H
#include<QString>
#include<QDate>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QtSql/QSqlQueryModel>

class conference
{
public:

    //constructeur
    conference();
    conference(QString,QString,QDate,QString,QString);
    // Methodes
    QString get_ref();
    QString get_nom();
    QDate get_dates();
    QString get_lieu();
    QString get_modes();

    //*************
    void setref(QString);
    void setnom(QString);
    void setdates(QDate);
    void setlieu(QString);
    void setmodes(QString);
    //**************************
    bool Ajouter();
     QSqlQueryModel* afficher();
     QSqlQueryModel* test();
     bool modifier(QString);
     bool Supprime(QString);
     bool reset();
     bool createConferenceCalendar();


     //***********


private:

      QString ref,nom,lieu, modes;
      QDate dates;
};

#endif // CONFERENCE_H
