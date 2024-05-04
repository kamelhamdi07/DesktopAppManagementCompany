#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QtSql/QSqlQueryModel>
#include<QTableView>
class person
{
   public:
   //CONSTRUCTEURS
       person();
       person(QString,QString,QString,QString,long,QString);
       //GETTERS
      QString getid();
      QString getnom();
      QString getprenom();
      QString getgrade();
      long getsal();
      QString gettel();

      //SETTERS
      void setid(QString);
       void setnom(QString);
      void setprenom(QString);
      void setgrade(QString);
      void setsal(long);
      void settel(QString);
//METHODS
      bool Ajouter();
       QSqlQueryModel* afficher();
       QSqlQueryModel* afficher_grade();
       QSqlQueryModel* afficher_salaire();
       QSqlQueryModel* afficher_idi();
       QSqlQueryModel* test();
       bool Supprime(QString);
       bool modifier(QString);
       bool reset();
       bool verif_alpha(QString);
       bool verif_num(QString);
     //  void rechercher(QTableView,QString);

private:
       QString ID,NOM,PRENOM,GRADE,TEL;
          long SALAIRE;
   };

#endif // PERSONNEL_H
