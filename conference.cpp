#include "conference.h"
#include <QDate>
#include <QtDebug>
#include<QObject>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QtWidgets>
#include "ui_conf.h"
#include "conf.h"

conference::conference()
{
    QDate defDate(01, 01, 1997);
ref="";
nom="";
dates= defDate;
lieu="";
modes="";
}
conference::conference(QString ref,QString nom,QDate dates,QString lieu,QString modes)
{
this->ref=ref;
this->nom=nom;
this->dates=dates;
this->lieu=lieu;
this->modes=modes;
}
QString conference::get_ref()
{
    return ref;
}
QString conference::get_nom()
{
    return nom;
}
QDate conference::get_dates()
{
    return dates;
}
QString conference::get_lieu()
{
    return lieu;
}
QString conference::get_modes()
{
    return modes;
}
void conference::setref(QString ref)
{
    this->ref=ref;
}
void conference::setnom(QString nom)
{
    this->nom=nom;
}
void conference::setdates(QDate dates)
{
    this->dates=dates;
}
void conference::setlieu(QString lieu)
{
    this->lieu=lieu;
}
void conference::setmodes(QString modes)
{
    this->modes=modes;
}
bool conference::Ajouter()
{
    QSqlQuery query;

       // Vérifier si l'ID existe déjà dans la table
       query.prepare("SELECT COUNT(*) FROM CONFERENCE WHERE ref = ?");
       query.bindValue(0, ref);
       query.exec();
       if (query.next()) {
              int count = query.value(0).toInt();
              if (count > 0) {
                  QMessageBox::warning(nullptr, "Erreur", "La reference existe déjà.");
                  return false;
              }
          }

  //PREPARE
         query.prepare("INSERT INTO CONFERENCE (REF,NOM,DATES,LIEU,MODES) "
                       "VALUES (:REF,:NOM,:DATES,:LIEU,:MODES)");
         query.bindValue(":REF",ref);
         query.bindValue(":NOM",nom);
         query.bindValue(":DATES",dates);
         query.bindValue(":LIEU",lieu);
         query.bindValue(":MODES",modes);
      return query.exec();
}

QSqlQueryModel *conference::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM CONFERENCE ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("REF"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATES"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("MODES"));
          return model;
}
bool conference::modifier(QString ref)
{
    QSqlQuery query;
    query.prepare("UPDATE CONFERENCE SET REF=:REF,NOM=:NOM,DATES=:DATES,LIEU=:LIEU,MODES=:MODES WHERE REF=:REF;");
    query.bindValue(":REF",ref);
    query.bindValue(":NOM",nom);
    query.bindValue(":DATES",dates);
    query.bindValue(":LIEU",lieu);
    query.bindValue(":MODES",modes);
    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error executing query: " << query.lastError().text();
        return false;
    }
}

bool conference::Supprime(QString ref)
{
    QSqlQuery query;
             query.prepare("delete from CONFERENCE where REF=:REF");
             query.bindValue(0, ref);
          return query.exec();
}
bool conference::reset()
{
    QSqlQuery query;
         query.prepare("delete from CONFERENCE");
         query.bindValue(0, ref);
      return query.exec();
}

bool conference::createConferenceCalendar() {
    QSqlQuery query;
    query.prepare("SELECT ref, nom, dates, lieu, modes FROM CONFERENCE");
    if (!query.exec()) {
        qDebug() << "Failed to retrieve conferences from database:" << query.lastError().text();
        return false;
    }

    QDate minDate, maxDate;
    //bool first = true;

    // Get the minimum and maximum dates from the conferences in the database
    while (query.next()) {
        //QDate dates = query.value(2).toDate();

        /*if (first) {
            minDate = dates;
            maxDate = dates;
            first = false;
        } else {
            if (dates < minDate) {
                minDate = dates;
            }
            if (dates > maxDate) {
                maxDate = dates;
            }
        }*/
    }

    // Create the calendar widget and set its minimum and maximum dates
    QCalendarWidget *calendar = new QCalendarWidget();
    calendar->setMinimumDate(minDate);
    calendar->setMaximumDate(maxDate);

    // Reset the query to retrieve the conferences again
    if (!query.exec()) {
        qDebug() << "Failed to retrieve conferences from database:" << query.lastError().text();
        return false;
    }
    // Add the conferences to the calendar
    while (query.next()) {
        QString ref = query.value(0).toString();
        QString nom = query.value(1).toString();
        QDate dates = query.value(2).toDate();
        QString lieu = query.value(3).toString();
        QString modes = query.value(4).toString();

        // Create a new Conference object from the retrieved data
        conference c(ref, nom, dates, lieu, modes);

        // Set the background color of the date corresponding to the conference
        QTextCharFormat format;
        QString tooltip = QString("Conference : %1\nNom : %2\nLieu : %3\nModes : %4").arg(ref).arg(nom).arg(lieu).arg(modes);
        if (modes == "présentiel") {
            format.setToolTip(tooltip);
            format.setBackground(Qt::yellow);
        } else if (modes == "en ligne") {
            format.setToolTip(tooltip);
            format.setBackground(Qt::green);
        }
        calendar->setDateTextFormat(dates, format);

        // Disable editing of the date corresponding to the conference
        calendar->setDateEditEnabled(false);
    }
    // Show the calendar widget
        calendar->show();
    // Connect the calendar's clicked signal to the showConferenceInfo slot
    QObject::connect(calendar, &QCalendarWidget::clicked, [=](const QDate &date){
       /* QBoxLayout *layout = new QVBoxLayout();
        QWidget *widget = new QWidget();
        widget->setLayout(layout);
        QPushButton *addButton = new QPushButton("Ajouter une conférence");
        QPushButton *deleteButton = new QPushButton("Supprimer la conférence sélectionnée");

        layout->addWidget(addButton);
        layout->addWidget(deleteButton);
        QObject::connect(addButton, &QPushButton::clicked, [=](){
        QString ref, nom, lieu, modes;
        bool ok;
        ref = QInputDialog::getText(nullptr, "Ajouter une conférence", "Référence :", QLineEdit::Normal, "", &ok);
        nom = QInputDialog::getText(nullptr, "Ajouter une conférence", "nom :", QLineEdit::Normal, "", &ok);
        lieu = QInputDialog::getText(nullptr, "Ajouter une conférence", "lieu :", QLineEdit::Normal, "", &ok);
        QStringList modesList = {"présentiel", "en ligne"};
        modes = QInputDialog::getItem(nullptr, "Ajouter une conférence", "Mode :", modesList, 0, false, &ok);
        QSqlQuery query;




     if (ok && !ref.isEmpty()) {
            // Check if a conference already exists on the selected date
            QSqlQuery query;
            query.prepare("SELECT ref, nom, dates, lieu, modes FROM CONFERENCE WHERE dates = ?");
            query.addBindValue(dates);
            if (query.exec() && query.next()) {
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                    QObject::tr("A conference already exists on this date.\nClick Cancel to exit."), QMessageBox::Cancel);
                return;
            }
             query.prepare("INSERT INTO CONFERENCE (ref, nom, dates, lieu, modes) VALUES (?, ?, ?, ?, ?)");

            // Add the new conference to the database
            conference F(ref, nom, date, lieu, modes);
            if (F.Ajouter()) {
                QMessageBox::information(nullptr, QObject::tr("Add Successful"),
                    QObject::tr("Conference added successfully.\nClick Cancel to exit."), QMessageBox::Cancel);

                // Add the conference to the calendar
                QTextCharFormat format;
                QString tooltip = QString("Conference : %1\nNom : %2\nLieu : %3\nModes : %4").arg(ref).arg(nom).arg(lieu).arg(modes);
                if (modes == "présentiel") {
                       format.setToolTip(tooltip);
                       format.setBackground(Qt::yellow);
                   } else if (modes == "en ligne") {
                       format.setToolTip(tooltip);
                       format.setBackground(Qt::green);
                   }
                calendar->setDateTextFormat(date, format);
                calendar->setDateEditEnabled(false);
            } else {
                QMessageBox::critical(nullptr, QObject::tr("Add Error"),
                    QObject::tr("Failed to add conference.\nClick Cancel to exit."), QMessageBox::Cancel);
            }
        }});
        QObject::connect(deleteButton, &QPushButton::clicked, [=](){*/
            //QDate date = calendar->selectedDate();
                QString ref, nom, lieu, modes;
                QSqlQuery query;

                // Retrieve the selected conference from the database
                query.prepare("SELECT ref, nom, dates, lieu, modes FROM CONFERENCE WHERE dates = ?");
                query.addBindValue(date);
                if (!query.exec() || !query.next()) {
                    QMessageBox::critical(nullptr, QObject::tr("Error"),
                        QObject::tr("Failed to retrieve conference from database: %1").arg(query.lastError().text()));
                    return;
                }

                ref = query.value(0).toString();
                nom = query.value(1).toString();
                lieu = query.value(3).toString();
                modes = query.value(4).toString();

                // Ask the user to confirm the deletion
                QMessageBox::StandardButton confirm = QMessageBox::question(nullptr, "Confirmation",
                    QString("Êtes-vous sûr de vouloir supprimer la conférence \"%1\" qui a lieu le %2 ?").arg(nom).arg(date.toString("dd/MM/yyyy")),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

                if (confirm == QMessageBox::No) {
                    return;
                }

                // Delete the conference from the database
                query.prepare("DELETE FROM CONFERENCE WHERE ref = ?");
                query.addBindValue(ref);
                if (!query.exec()) {
                    QMessageBox::critical(nullptr, QObject::tr("Error"),
                        QObject::tr("Failed to delete conference from database: %1").arg(query.lastError().text()));
                    return;
                }

                // Remove the conference from the calendar
                QTextCharFormat format;
                format.setBackground(Qt::white);
                calendar->setDateTextFormat(date, format);
        });


   /* });*/
    return true;
}
