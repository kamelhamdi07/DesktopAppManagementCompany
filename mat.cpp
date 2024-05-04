#include "mat.h"
#include <QtDebug>
#include<QObject>
#include <QString>
#include <QtSql/QSqlQuery>
#include<vector>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <QMessageBox>
#include<QTableView>
mat::mat()
{
   num="";
   nom="";
   prix="";
   etat="";
   quantite=0;
   paiement="";
   categorie="";
}

mat::mat(QString num,QString nom,QString prix,QString etat,int quantite,QString paiement,QString categorie)
{
    this->num=num;
    this->nom=nom;
    this->prix=prix;
    this->etat=etat;
    this->quantite=quantite;
    this->paiement=paiement;
    this->categorie=categorie;
}
QString mat::getnum()
{
    return num;
}
QString mat::getnom()
{
    return nom;
}
QString mat::getprix()
{
    return prix;
}
QString mat::getetat()
{
    return etat;
}
int mat::getquantite()
{
    return quantite;
}
QString mat::getpaiement()
{
    return paiement;
}
QString mat::getcategorie()
{
    return categorie;
}
void mat::setnum(QString num)
{
    this->num=num;
}
void mat::setnom(QString nom)
{
    this->nom=nom;
}
void mat::setprix(QString prix)
{
    this->prix=prix;
}
void mat::setetat(QString etat)
{
    this->etat=etat;
}
void mat::setquantite(int quantite)
{
    this->quantite=quantite;
}
void mat::setpaiement(QString paiement)
{
    this->paiement=paiement;
}
void mat::setcategorie(QString categorie)
{
    this->categorie=categorie;
}
bool mat::Ajouter()
{
         QSqlQuery query;

        // Vérifier si l'ID existe déjà dans la table
        query.prepare("SELECT COUNT(*) FROM MATERILELS WHERE num = ?");
        query.bindValue(0, num);
        query.exec();

        if (query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                QMessageBox::warning(nullptr, "Erreur", "L'num existe déjà.");
                return false;
            }
        }

        // Ajouter l'entrée dans la table
        QString quant_string = QString::number(quantite);
        query.prepare("INSERT INTO MATERILELS (NUM, NOM, PRIX, ETAT, QUANTITE, PAIEMENT ,CATEGORIE ) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.bindValue(0, num);
        query.bindValue(1, nom);
        query.bindValue(2, prix);
        query.bindValue(3, etat);
        query.bindValue(4, quant_string);
        query.bindValue(5, paiement);
                query.bindValue(6, categorie);

        if (!query.exec()) {
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors de l'ajout des données.");
            return false;
        }

        return true;
    }
QSqlQueryModel *mat::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM MATERILELS ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("PAIEMENT"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("CATEGORIE"));
          return model;
}
QSqlQueryModel *mat::afficher_categorie()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM MATERILELS ORDER BY CATEGORIE ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("PAIEMENT"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("CATEGORIE"));
          return model;
}
QSqlQueryModel *mat::afficher_num()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM MATERILELS ORDER BY num ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("ETAT"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("PAIEMENT"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("CATEGORIE"));
          return model;
}
bool mat::Supprime(QString num)
{
    QSqlQuery query;
         query.prepare("delete from MATERILELS where NUM=:num");
         query.bindValue(0, num);
      return query.exec();
}
bool mat::reset()
{
    QSqlQuery query;
         query.prepare("delete from MATERILELS");
         query.bindValue(0, num);
      return query.exec();
}

bool mat::modifier(QString num)
{
QSqlQuery query;
QString quant_string=QString::number(quantite);


query.prepare("UPDATE MATERILELS SET NUM=:NUM,NOM=:NOM,PRIX=:PRIX,ETAT=:ETAT,QUANTITE=:QUANTITE,PAIEMENT=:PAIEMENT,CATEGORIE=:CATEGORIE WHERE NUM=:NUM;");

query.bindValue(":NUM",num);
query.bindValue(":NOM",nom);
query.bindValue(":PRIX", prix);
query.bindValue(":ETAT",etat);
query.bindValue(":QUANTITE",quant_string);
query.bindValue(":PAIEMENT",paiement);
query.bindValue(":CATEGORIE",categorie);
return  query.exec();
}
bool mat::verif_alpha(QString str) {
    return std::all_of(str.begin(), str.end(), [](QChar c) { return c.isLetter(); });
}
bool mat::verif_num(QString nm) {
    return std::all_of(nm.begin(), nm.end(), [](QChar c1) { return c1.isDigit(); });
};
