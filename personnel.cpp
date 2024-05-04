#include "personnel.h"
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
person::person()
{
    ID="";
    NOM="";
    PRENOM="";
    GRADE="";
    SALAIRE= 0;
    TEL="";
}
person::person(QString ID,QString NOM,QString PRENOM,QString GRADE,long SALAIRE,QString TEL)
{
    this->ID=ID;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->GRADE=GRADE;
    this->SALAIRE=SALAIRE;
    this->TEL=TEL;
}
QString person::getid()
{
    return ID;
}
QString person::getnom()
{
    return NOM;
}
QString person::getprenom()
{
    return PRENOM;
}
QString person::getgrade()
{
    return GRADE;
}
long person::getsal()
{
    return SALAIRE;
}

QString person::gettel()
{
    return TEL;
}
void person::setid(QString id)
{
    this->ID=id;
}
void person::setnom(QString nom)
{
    this->NOM=nom;
}
void person::setprenom(QString prenom)
{
    this->PRENOM=prenom;

}
void person::setgrade(QString grade)
{
    this->GRADE=grade;

}
void person::setsal(long salaire)
{
    this->SALAIRE=salaire;

}

void person::settel(QString tel)
{
    this->TEL=tel;
}

bool person::Ajouter()
{
         QSqlQuery query;

        // Vérifier si l'ID existe déjà dans la table
        query.prepare("SELECT COUNT(*) FROM PERSONNELS WHERE ID = ?");
        query.bindValue(0, ID);
        query.exec();

        if (query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                QMessageBox::warning(nullptr, "Erreur", "L'ID existe déjà.");
                return false;
            }
        }

        // Ajouter l'entrée dans la table
        QString sal_string = QString::number(SALAIRE);
        query.prepare("INSERT INTO PERSONNELS (ID, NOM, PRENOM, GRADE, SALAIRE, TEL) "
                      "VALUES (?, ?, ?, ?, ?, ?)");
        query.bindValue(0, ID);
        query.bindValue(1, NOM);
        query.bindValue(2, PRENOM);
        query.bindValue(3, GRADE);
        query.bindValue(4, sal_string);
        query.bindValue(5, TEL);

        if (!query.exec()) {
            QMessageBox::warning(nullptr, "Erreur", "Erreur lors de l'ajout des données.");
            return false;
        }

        return true;
    }

QSqlQueryModel *person::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM PERSONNELS ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
          return model;
}
QSqlQueryModel *person::afficher_grade()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM PERSONNELS ORDER BY GRADE ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
          return model;
}
QSqlQueryModel *person::afficher_salaire()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM PERSONNELS ORDER BY SALAIRE ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
          return model;
}
QSqlQueryModel *person::afficher_idi()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM PERSONNELS ORDER BY ID ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
          return model;
}
bool person::Supprime(QString id)
{
    QSqlQuery query;
         query.prepare("delete from PERSONNELS where ID=:id");
         query.bindValue(0, id);
      return query.exec();
}
bool person::modifier(QString ID)
{
QSqlQuery query;
QString sal_string=QString::number(SALAIRE);


query.prepare("UPDATE PERSONNELS SET id=:id,nom=:nom,prenom=:prenom,grade=:grade,salaire=:salaire,tel=:tel WHERE id=:id;");

query.bindValue(":id",ID);
query.bindValue(":nom",NOM);
query.bindValue(":prenom", PRENOM);
query.bindValue(":grade",GRADE);
query.bindValue(":salaire",sal_string);
query.bindValue(":tel",TEL);
return  query.exec();
};
bool person::reset()
{
    QSqlQuery query;
         query.prepare("delete from PERSONNELS");
         query.bindValue(0, ID);
      return query.exec();
}


bool person::verif_alpha(QString str) {
    return std::all_of(str.begin(), str.end(), [](QChar c) { return c.isLetter(); });
}
bool person::verif_num(QString nm) {
    return std::all_of(nm.begin(), nm.end(), [](QChar c1) { return c1.isDigit(); });
}
/*void person::rechercher(QTableView *table,QString cas )
 {
     QSqlQueryModel *model= new QSqlQueryModel();

     QSqlQuery *query=new QSqlQuery;

     query->prepare("SELECT * FROM PERSONNELS WHERE (ID LIKE '%"+cas+"%' or NOM LIKE '%"+cas+"%' or PRENOM Like '%"+cas+"%'or GRADE Like '%"+cas+"%'or SALAIRE  Like '%"+cas+"%'or TEL Like '%"+cas+"%' )");

     query->exec();
     model->setQuery(*query);
     table->setModel(model);
     table->show();

 }*/
