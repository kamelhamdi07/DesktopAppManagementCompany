#ifndef MAT_H
#define MAT_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QtSql/QSqlQueryModel>
#include<QTableView>
class mat
{
public:
    mat();
     mat(QString,QString,QString,QString,int,QString,QString);
     QString getnum();
     QString getnom();
     QString getprix();
     QString getetat();
     int getquantite();
     QString getpaiement();
     QString getcategorie();

     void setnum(QString);
     void setnom(QString);
     void setprix(QString);
     void setetat(QString);
     void setquantite(int);
     void setpaiement(QString);
     void setcategorie(QString);

     bool Ajouter();
     QSqlQueryModel* afficher();
      QSqlQueryModel* afficher_categorie();
       QSqlQueryModel* afficher_num();
     bool Supprime(QString);
     bool modifier(QString);
     bool verif_alpha(QString);
     bool verif_num(QString);
      bool reset();
      private:
      QString num,nom,prix,etat,paiement,categorie;
      int quantite;

};

#endif // MAT_H
