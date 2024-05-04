#include "perso.h"
#include"personnel.h"
#include "ui_perso.h"
#include"QMessageBox"
#include"QString"
#include"c++/cctype"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include<QTextDocument>
#include <QTextDocument>
#include<QtPrintSupport/QtPrintSupport>
#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include"chat.h"

perso::perso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::perso)
{
    ui->setupUi(this);
    ui->tableView->setModel(p.afficher()) ;
}

perso::~perso()
{
    delete ui;
}

void perso::on_ajout_clicked()
{

        QString ID=ui->id_ajout_2 ->text();
            QString NOM=ui->nom_ajout_2->text();
            QString PRENOM=ui->prenom_ajout_2->text();
            QString GRADE=ui->grade_ajout->currentText();
            long SALAIRE=ui->salaire_ajout_2->text().toInt();
           QString TEL=ui->tel_ajout_2->text();

           if (((!p.verif_num(ID))&&(ID.length()<=6))||(ID==""))
           {
                QMessageBox::critical(nullptr, QObject::tr("probleme en ID"),
                            QObject::tr("verifier id\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else if((!p.verif_alpha(NOM))||(NOM==""))
            {
                QMessageBox::critical(nullptr, QObject::tr("probleme en Nom"),
                            QObject::tr("verifier nom\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
           else  if ((!p.verif_alpha(PRENOM))||(PRENOM==""))
            {
                QMessageBox::critical(nullptr, QObject::tr("probleme en prenom"),
                            QObject::tr("verifier prenom\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else if (GRADE=="")
            {
                QMessageBox::critical(nullptr, QObject::tr("probleme en grade"),
                            QObject::tr("verifier grade\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else if (SALAIRE <=0)
            {
                QMessageBox::critical(nullptr, QObject::tr("probleme salaire"),
                            QObject::tr("verifier salaire\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else if (((!p.verif_num(TEL))&&(TEL.length()<= 10)))
            {
                QMessageBox::critical(nullptr, QObject::tr("probleme tel"),
                            QObject::tr("verifier tel\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            {
                person P(ID,NOM,PRENOM,GRADE,SALAIRE,TEL);
                bool test=P.Ajouter();
                if(test)
                 {    QMessageBox::information(nullptr, QObject::tr("Personnels est ajoutée"),
                                               QObject::tr("Ajout Terminer.\n"
                                                           "Cliquer Ok pour Continuer."), QMessageBox::Ok);
                    ui->tableView->setModel(P.afficher());
                    {  /*clear after ajouter*/
                        ui->id_ajout_2->clear();
                        ui->nom_ajout_2->clear();
                        ui->prenom_ajout_2->clear();
                        //ui->grade_ajout->clear();
                        ui->salaire_ajout_2->clear();
                        ui->tel_ajout_2->clear();

                           }

              }
           }
 }

void perso::on_anuuler_clicked()
{
    ui->id_ajout_2->clear();
    ui->nom_ajout_2->clear();
    ui->prenom_ajout_2->clear();
    ui->grade_ajout->clear();
    ui->salaire_ajout_2->clear();
    ui->tel_ajout_2->clear();
}


void perso::on_suprim_2_clicked()
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
            int id = index.sibling(index.row(), 0).data().toInt(); // Remplacez "0" par l'index de votre colonne d'identifiant unique

            // Supprimer la ligne correspondante dans la base de données
            QSqlQuery query;
            query.prepare("DELETE FROM PERSONNELS where ID=:id");
            query.bindValue(":id", id);
            query.exec();

            // Mettre à jour le table view pour refléter les modifications
            ui->tableView->setModel(p.afficher());
}
        }
}
void perso::on_recupere_clicked()
{
    QString id = ui->id_modif->text();

               // Effectuer la requête SELECT pour récupérer les données correspondantes dans la base de données
               QSqlQuery query;
               query.prepare("SELECT * FROM PERSONNELS WHERE ID = ?");
               query.bindValue(0, id);
               query.exec();

               if (query.next()) {
                   // Récupérer les valeurs de chaque colonne
                   QString ID = query.value("ID").toString();
                   QString NOM = query.value("NOM").toString();
                   QString PRENOM = query.value("PRENOM").toString();
                   QString GRADE = query.value("GRADE").toString();
                   long SALAIRE = query.value("SALAIRE").toInt();
                   QString TEL = query.value("TEL").toString();

                   // Afficher les valeurs récupérées dans les champs correspondants de l'interface graphique
                   ui->nom_ajout_2->setText(NOM);
                   ui->prenom_ajout_2->setText(PRENOM);
                   ui->grade_ajout->setCurrentText(GRADE);
                   ui->salaire_ajout_2->setText(QString::number(SALAIRE));
                   ui->tel_ajout_2->setText(TEL);

               } else {
                   // Afficher un message d'erreur si aucune donnée n'a été trouvée pour la référence donnée
                   QMessageBox::critical(this, "Erreur", "Aucune donnée trouvée pour la référence donnée.");
               }
}

void perso::on_modify_2_clicked()
{
    QString ID=ui->id_modif->text();
    QString NOM=ui->nom_ajout_2->text();
    QString PRENOM=ui->prenom_ajout_2->text();
    QString GRADE=ui->grade_ajout->currentText();
    long SALAIRE=ui->salaire_ajout_2->text().toInt();
    QString TEL=ui->tel_ajout_2->text();

    if (((!p.verif_num(ID))&&(ID.length()<=6))||(ID==""))
   {
       QMessageBox::critical(nullptr, QObject::tr("probleme id"),
                   QObject::tr("verifier id\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else if((!p.verif_alpha(NOM))||(NOM==""))
   {
       QMessageBox::critical(nullptr, QObject::tr("probleme Nom"),
                   QObject::tr("verifier nom\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
  else  if ((!p.verif_alpha(PRENOM))||(PRENOM==""))
   {
       QMessageBox::critical(nullptr, QObject::tr("probleme prenom"),
                   QObject::tr("verifier prenom\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else if (GRADE == "" )
   {
       QMessageBox::critical(nullptr, QObject::tr("probleme grade"),
                   QObject::tr("verifier grade\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else if (SALAIRE <= 0 )
   {
       QMessageBox::critical(nullptr, QObject::tr("probleme salaire"),
                   QObject::tr("verifier salaire\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else if (((!p.verif_num(TEL))&&(TEL.length()<= 10)))
   {
       QMessageBox::critical(nullptr, QObject::tr("probleme tel"),
                   QObject::tr("verifier tel\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
        else
        {
        person m(ID,NOM,PRENOM,GRADE,SALAIRE,TEL);
        bool test=m.modifier(ID);
        if(test)
         {    QMessageBox::information(nullptr, QObject::tr("modify avec succes"),
                                       QObject::tr("modify successful.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(m.afficher());

                   }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("modify error"),
                                       QObject::tr("modify failed.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
      }
}


void perso::on_reset_clicked()
{
    QMessageBox::StandardButton confirmMsg;
       confirmMsg = QMessageBox::question(this, "Confirmation",
                   "Êtes-vous sûr de vouloir supprimer", QMessageBox::Yes|QMessageBox::No);
       if(confirmMsg == QMessageBox::Yes)
       {
           bool t = p.reset();
           if(t)
           {
               QMessageBox::information(nullptr, QObject::tr("suppression est faite"),
                                         QObject::tr("suppression avec succes.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
               ui->tableView->setModel(p.afficher());
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("sup erreur"),
                                         QObject::tr("suppresion est echoue.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
           }
       }
}

void perso::on_rech_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM PERSONNELS WHERE ID  LIKE'"+arg1+"%' ");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("n'exsiste pas !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->rech->clear();}
}



void perso::on_imp_clicked()
{
    QSqlDatabase db;

                                QTableView tableView;
                                QSqlQueryModel * Modal=new  QSqlQueryModel();

                                QSqlQuery qry;
                                 qry.prepare("SELECT* FROM PERSONNELS");
                                 qry.exec();
                                 Modal->setQuery(qry);
                                 tableView.setModel(Modal);

                                 db.close();

                                 QString strStream;
                                 QTextStream out(&strStream);

                                 const int rowCount = tableView.model()->rowCount();
                                 const int columnCount =  tableView.model()->columnCount();

                                 const QString strTitle ="ListedesPersonnels";

                                 out <<  "<html>\n"
                                         "<img src='C:/Users/Trabe/Downloads/Icon/log-removebg-preview.png' height='155' width='140'/>"
                                     "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     <<  QString("<title>%1</title>\n").arg(strTitle)
                                     <<  "</head>\n"
                                     "<body bgcolor=#ffffff link=#5000A0>\n"
                                    << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES PERSSONELS")
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

                                 QTextDocument *ListeDesPersonnels = new QTextDocument();
                                 ListeDesPersonnels->setHtml(strStream);

                                 QPrinter printer;
                                 QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                 if (dialog->exec() == QDialog::Accepted)
                                 {

                                     ListeDesPersonnels->print(&printer);
                                 }
                                 printer.setOutputFormat(QPrinter::PdfFormat);
                                 printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName("/tmp/Produit.pdf");
                                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                 delete ListeDesPersonnels;
}


void perso::on_act_clicked()
{
  ui->tableView->setModel(p.afficher()) ;
}

void perso::on_idi_clicked()
{
    ui->tableView->setModel(p.afficher_idi());
}

void perso::on_salary_clicked()
{
 ui->tableView->setModel(p.afficher_salaire());
}

void perso::on_grade_clicked()
{
  ui->tableView->setModel(p.afficher_grade());
}

void perso::on_chatbot_clicked()
{
    chat chat;
        chat.setModal(true);
        chat.exec();
}

void perso::on_bn_pub_2_clicked()
{

}
