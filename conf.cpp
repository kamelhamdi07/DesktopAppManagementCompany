#include "conf.h"
#include"conference.h"
#include "ui_conf.h"
#include"QMessageBox"
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QDesktopServices>
#include <QtCharts/QtCharts>
#include <shellapi.h>
#include <QtCharts/QPieSeries>



conf::conf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::conf)
{
    ui->setupUi(this);
    ui->tableView->setModel(C.afficher());
}

conf::~conf()
{
    delete ui;
}

void conf::on_Ajout_2_clicked()
{

    QString REF=ui->ref_ajout->text();
        QString NOM=ui->nom_ajout->text();
        QDate DATES=ui->date_ajout->date();
        QString LIEU=ui->lieu_ajout->text();
        QString MODES=ui->mode_ajout->currentText();



       if (REF=="")
       {
            QMessageBox::critical(nullptr, QObject::tr("problem id"),
                        QObject::tr("verifier id\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if(NOM=="")
        {
            QMessageBox::critical(nullptr, QObject::tr("problem Nom"),
                        QObject::tr("verifier nom\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
       /*else  if (DATES==)
        {
            QMessageBox::critical(nullptr, QObject::tr("problem prenom"),
                        QObject::tr("verifier prenom\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }*/
        else if (LIEU== "" )
        {
            QMessageBox::critical(nullptr, QObject::tr("problem lieu"),
                        QObject::tr("verifier lieu\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }

        else if (MODES=="")
        {
            QMessageBox::critical(nullptr, QObject::tr("problem tel"),
                        QObject::tr("verifier tel\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        {
            conference F(REF,NOM,DATES,LIEU,MODES);
            bool test=F.Ajouter();
            if(test)
                             {    QMessageBox::information(nullptr, QObject::tr("vetement est ajoutée"),
                                                           QObject::tr("Ajout Terminer.\n"
                                                                       "Cliquer Ok pour Continuer."), QMessageBox::Ok);
                                ui->tableView->setModel(F.afficher());
                                {  /*clear after ajouter*/
                                    ui->ref_ajout->clear();
                                    ui->nom_ajout->clear();
                                    //ui->date_ajout->clear();
                                    //ui->grade_ajout->clear();
                                    ui->lieu_ajout->clear();
                                    //ui->mode_ajout->clear();

                                       }

                          }
                       }


}



void conf::on_suprim_2_clicked()
{
    // Récupérer l'élément sélectionné dans le table view
        QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {
            // Demander à l'utilisateur de confirmer la suppression
            QMessageBox::StandardButton confirmation;
            confirmation = QMessageBox::question(this, "Confirmer la suppression", "Êtes-vous sûr de vouloir supprimer cette ligne ?", QMessageBox::Yes|QMessageBox::No);

            if (confirmation == QMessageBox::Yes) {
                // Récupérer l'identifiant unique de la ligne à supprimer
                QModelIndex index = selectedIndexes.at(0); // Utilisez l'index approprié ici si vous avez plusieurs colonnes dans votre table view
                QString ref = index.sibling(index.row(), 0).data().toString(); // Remplacez "0" par l'index de votre colonne d'identifiant unique

                // Supprimer la ligne correspondante dans la base de données
                QSqlQuery query;
                query.prepare("DELETE FROM CONFERENCE where REF=:ref");
                query.bindValue(":ref", ref);
                query.exec();

                // Mettre à jour le table view pour refléter les modifications
                ui->tableView->setModel(C.afficher());
    }
            }


        }



void conf::on_impr_clicked()
{
    QSqlDatabase db;

                                QTableView tableView;
                                QSqlQueryModel * Modal=new  QSqlQueryModel();

                                QSqlQuery qry;
                                 qry.prepare("SELECT* FROM CONFERENCE");
                                 qry.exec();
                                 Modal->setQuery(qry);
                                 tableView.setModel(Modal);

                                 db.close();

                                 QString strStream;
                                 QTextStream out(&strStream);

                                 const int rowCount = tableView.model()->rowCount();
                                 const int columnCount =  tableView.model()->columnCount();

                                 const QString strTitle ="Listedesconferences";

                                 out <<  "<html>\n"
                                         "<img src='C:/Users/PC-Ridha/Downloads/logo.png' height='155' width='140'/>"
                                     "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     <<  QString("<title>%1</title>\n").arg(strTitle)
                                     <<  "</head>\n"
                                     "<body bgcolor=#ffffff link=#5000A0>\n"
                                    << QString("<h3 style=\" font-size: 100px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES CONFERENCES")
                                    <<"<br>"

                                    <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                                 out << "<thead><tr bgcolor=#f0f0f0>";
                                 for (int column = 0; column < columnCount; column++)
                                     if (!tableView.isColumnHidden(column))
                                         out << QString("<th>%1</th>").arg(tableView.model()->headerData(column, Qt::Horizontal).toString());
                                 out << "</tr></thead>\n";

                                 for (int row = 0; row < rowCount; row++)
                                 {
                                     out << "<tr>";
                                     for (int column = 0; column < columnCount; column++)
                                     {
                                         if (!tableView.isColumnHidden(column))
                                         {
                                             QString data = tableView.model()->data(tableView.model()->index(row, column)).toString().simplified();
                                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                         }
                                     }
                                     out << "</tr>\n";
                                 }
                                 out <<  "</table>\n"
                                         "<br><br>"
                                         <<"<br>"
                                         <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                                     out << "<thead><tr bgcolor=#f0f0f0>";

                                         out <<  "</table>\n"

                                     "</body>\n"
                                     "</html>\n";

                                 QTextDocument *ListeDesConferences = new QTextDocument();
                                 ListeDesConferences->setHtml(strStream);

                                 QPrinter printer;
                                 QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                 if (dialog->exec() == QDialog::Accepted)
                                 {

                                     ListeDesConferences->print(&printer);
                                 }
                                 printer.setOutputFormat(QPrinter::PdfFormat);
                                 printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName("/tmp/Produit.pdf");
                                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                 delete ListeDesConferences;
}

void conf::on_pushButton_2_clicked()
{
    // Récupérer les statistiques des conférences
        QSqlQueryModel model;
        model.setQuery("SELECT COUNT(*) as nb_conferences, modes FROM conference GROUP BY modes;");

        // Calculer le total des conférences
        int total = 0;
        while (model.canFetchMore())
            model.fetchMore();
        for (int i = 0; i < model.rowCount(); ++i) {
            total += model.data(model.index(i, 0)).toInt();
        }

        // Créer un graphique à secteurs pour représenter les statistiques
        QPieSeries *series = new QPieSeries();
        for (int i = 0; i < model.rowCount(); ++i) {
            QString mode = model.data(model.index(i, 1)).toString();
            int nb_conferences = model.data(model.index(i, 0)).toInt();
            qreal percentage = (qreal) nb_conferences / total * 100.0;
            QString label = QString("%1 (%2%)").arg(mode).arg(QString::number(percentage, 'f', 2));
            series->append(label, nb_conferences);
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des conférences");
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setFont(QFont("Arial", 10));

        // Afficher le graphique dans une boîte de dialogue
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(800, 600);

        QDialog *dialog = new QDialog();
        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(chartView);
        dialog->setWindowTitle("Statistiques des conférences");
        dialog->exec();

        // Nettoyer les objets alloués dynamiquement
      //  delete series;
       // delete chart;
       // delete chartView;
       // delete dialog;
}





void conf::on_reset_clicked()
{
    QMessageBox::StandardButton confirmMsg;
           confirmMsg = QMessageBox::question(this, "Confirmation",
                       "Êtes-vous sûr de vouloir supprimer", QMessageBox::Yes|QMessageBox::No);
           if(confirmMsg == QMessageBox::Yes)
           {
               bool t = C.reset();
               if(t)
               {
                   QMessageBox::information(nullptr, QObject::tr("suppression est faite"),
                                             QObject::tr("suppression avec succes.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);
                   ui->tableView->setModel(C.afficher());
               }
               else
               {
                   QMessageBox::critical(nullptr, QObject::tr("sup erreur"),
                                             QObject::tr("suppresion est echoue.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);
               }
           }
}

void conf::on_rech_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT * FROM CONFERENCE WHERE REF  LIKE'"+arg1+"%' ");
             query->exec();
             if (query->next()) {
             model->setQuery(*query);
             ui->tableView->setModel(model);
             }
             else {
                 QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                                 QObject::tr("CATEGORIE n'exsiste pas!.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
                 ui->rech->clear();}
}



void conf::on_pushButton_3_clicked()
{
    QString ref = ui->ref_modif->text();

           // Effectuer la requête SELECT pour récupérer les données correspondantes dans la base de données
           QSqlQuery query;
           query.prepare("SELECT * FROM CONFERENCE WHERE ref = ?");
           query.bindValue(0, ref);
           query.exec();

           if (query.next()) {
               // Récupérer les valeurs de chaque colonne
               QString nom = query.value("nom").toString();
               QDate dates = query.value("dates").toDate();
               QString lieu = query.value("lieu").toString();
               QString modes = query.value("modes").toString();

               // Afficher les valeurs récupérées dans les champs correspondants de l'interface graphique
               ui->nom_ajout->setText(nom);
               ui->date_ajout->setDate(dates);
               ui->lieu_ajout->setText(lieu);
               ui->mode_ajout->setCurrentText(modes);
           } else {
               // Afficher un message d'erreur si aucune donnée n'a été trouvée pour la référence donnée
               QMessageBox::critical(this, "Erreur", "Aucune donnée trouvée pour la référence donnée.");
           }
}

void conf::on_pushButton_4_clicked()
{
    QString REF=ui->ref_modif->text();
            QString NOM=ui->nom_ajout->text();
            QDate DATES=ui->date_ajout->date();
             QString LIEU=ui->lieu_ajout->text();
           QString MODES=ui->mode_ajout->currentText();
          /*
           if (num == "" )
           {
               QMessageBox::critical(nullptr, QObject::tr("problem num"),
                           QObject::tr("verifier num\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
           else if (nom=="" )
           {
               QMessageBox::critical(nullptr, QObject::tr("problem nom"),
                           QObject::tr("verifier nom\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
          else  if (prix == ""  )
           {
               QMessageBox::critical(nullptr, QObject::tr("problem prix"),
                           QObject::tr("verifier prix\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
           else  if (etat == ""  )
            {
                QMessageBox::critical(nullptr, QObject::tr("problem etat"),
                            QObject::tr("verifier etat\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
           else if (quantiter <= 0 )
           {
               QMessageBox::critical(nullptr, QObject::tr("problem quantiter"),
                           QObject::tr("verifier quantiter\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
           else  if (paiement == ""  )
            {
                QMessageBox::critical(nullptr, QObject::tr("problem paiement"),
                            QObject::tr("verifier paiement\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
           else  if (categorie == ""  )
            {
                QMessageBox::critical(nullptr, QObject::tr("problem categorie"),
                            QObject::tr("verifier categorie\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }*/


                    conference c(REF,NOM,DATES,LIEU,MODES);
                    bool test=c.modifier(REF);
                    if(test)
                     {    QMessageBox::information(nullptr, QObject::tr("modify avec succes"),
                                                   QObject::tr("modify successful.\n"
                                                               "Click Cancel to exit."), QMessageBox::Cancel);
                        ui->tableView->setModel(c.afficher());

                               }
                                   else
                                       QMessageBox::critical(nullptr, QObject::tr("modify error"),
                                                   QObject::tr("modify failed.\n"
                                                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void conf::on_pushButton_5_clicked()
{

           C.createConferenceCalendar();
           /*if(t)
            {    QMessageBox::information(nullptr, QObject::tr("supp avec succes"),
                                          QObject::tr("sup successful.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableView->setModel(C.afficher());
                      }
                          else
                              QMessageBox::critical(nullptr, QObject::tr("sup errer"),
                                          QObject::tr("sup failed.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);*/
}



/*void conf::on_pushButton_clicked()
{
    livestream L;
    L.setModal(true);
    L.exec();
}
*/

/*void conf::on_pushButton_clicked()
{
  Mailing m;

}
*/


