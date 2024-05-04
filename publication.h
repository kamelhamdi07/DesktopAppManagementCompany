#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSystemTrayIcon>

class publication
{
public:
    publication();

    publication(QString,QString,QDate);
   QString getref();
   QString gettype();
   QDate getdate();



   void setref(QString);
   void settype(QString);
   void setdate(QDate);



   bool Ajouter();
   QSqlQueryModel* afficher();


    bool reset();

    QSqlQueryModel* test();
    bool Supprime(QString);

   bool modifier(QString);

private:
    QString ref,type;
    QDate date;
};

#endif // PUBLICATION_H
