#include "publication.h"
#include <QtDebug>
#include<QObject>
#include <QString>
#include <QSqlQuery>
#include<vector>
#include<QDate>
#include<QSystemTrayIcon>
#include<QMessageBox>
publication::publication()

{
    QDate defDate(01, 01, 1900);
    ref="";
    type="";
    date=defDate;

}
publication::publication(QString ref,QString type,QDate date)
{
    this->ref=ref;
    this->type=type;
    this->date=date;
}
QString publication::getref()
{
    return ref;
}
QString publication::gettype()
{
    return type;
}
QDate publication::getdate()
{
    return date;
}


void publication::setref(QString ref)
{
    this->ref=ref;
}
void publication::settype(QString type)
{
    this->type=type;
}
void publication::setdate(QDate date)
{
    this->date=date;

}


bool publication::Ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO PUBLICATION (REFERENCE,TYPE,DATE_PUB) "
                  "VALUES (:REFERENCE,:type,:date_pub)");
    query.bindValue(":REFERENCE",ref);
    query.bindValue(":type",type);
    query.bindValue(":date_pub", date);

    bool success = query.exec();
    if (success) {

        // Create a desktop notification
        QSystemTrayIcon* notifyIcon = new QSystemTrayIcon();
        notifyIcon->setIcon(QIcon(":/images/icon.png"));
        notifyIcon->show();
        notifyIcon->showMessage("Data added successfully!", "New data has been added to the database.");

    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to add data to the database!");
    }
    return success;
}
QSqlQueryModel *publication::afficher()
{
  QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM PUBLICATION ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));

        model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_pub"));

        return model;
}
bool publication::Supprime(QString ref)
{
    QSqlQuery query;
    query.prepare("SELECT REFERENCE FROM PUBLICATION WHERE REFERENCE=:REFERENCE");
    query.bindValue(":REFERENCE", ref);
    if (query.exec() && query.next()) {
        // Record found, delete it
        query.prepare("DELETE FROM PUBLICATION WHERE REFERENCE=:REFERENCE");
        query.bindValue(":REFERENCE", ref);
        return query.exec();
    } else {
        // Record not found
        qDebug() << "Record with reference" << ref << "not found";
        return false;
    }
}

bool publication::modifier(QString ref)
{
    QSqlQuery query;
    query.prepare("SELECT REFERENCE FROM PUBLICATION WHERE REFERENCE=:REFERENCE");
    query.bindValue(":REFERENCE", ref);
    if (query.exec() && query.next()) {
        // Record found, update it
        query.prepare("UPDATE PUBLICATION SET REFERENCE=:ref, type=:type, date_pub=:date_pub WHERE REFERENCE=:ref;");
        query.bindValue(":ref", ref);
        query.bindValue(":type", type);
        query.bindValue(":date_pub", date);
        return query.exec();
    } else {
        // Record not found
        qDebug() << "Record with reference" << ref << "not found";
        return false;
    }
}
