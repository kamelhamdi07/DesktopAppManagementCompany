#include "materille.h"
#include "ui_materille.h"
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
#include <QtCharts/QPieSeries>
#include <QtCharts/QtCharts>
#include <QPushButton>

materille::materille(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::materille)
{
    ui->setupUi(this);
     ui->tableView->setModel(p.afficher()) ;
     QIcon icon("D:/Downloads/cc.jpg");
            uploadButton = new QPushButton("", this);
            uploadButton->setGeometry(QRect(QPoint(385, 365), QSize(70, 30)));
            uploadButton->setIcon(icon);
            uploadButton->setText("upload");
            uploadButton->setIconSize(QSize(100, 100));

            // Créer une étiquette pour afficher l'image
            imageLabel = new QLabel(this);

            imageLabel->setGeometry(QRect(QPoint(350, 250), QSize(100, 100)));

            // Connecter le bouton à une fonction pour gérer l'upload de l'image
            connect(uploadButton, &QPushButton::clicked, this, &materille::uploadImage);
}

materille::~materille()
{
    delete ui;
}

void materille::on_pushButton_3_clicked()
{
    QString num=ui->lineEdit ->text();
        QString nom=ui->lineEdit_2->text();
        QString prix=ui->lineEdit_3->text();
        QString etat=ui->comboBox->currentText();
        long quantiter=ui->spinBox->text().toInt();
       QString paiement=ui->comboBox_2->currentText();
       QString categorie=ui->comboBox_3->currentText();

       if (((!p.verif_num(num))&&(num.length()<=6))||(num==""))
       {
            QMessageBox::critical(nullptr, QObject::tr("probleme en num"),
                        QObject::tr("verifier num\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if((!p.verif_alpha(nom))||(nom==""))
          {
            QMessageBox::critical(nullptr, QObject::tr("probleme en nom"),
                        QObject::tr("verifier nom\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
       else  if ((p.verif_alpha(prix))||(prix==""))
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme en prix"),
                        QObject::tr("verifier prix\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (etat=="")
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme en etat"),
                        QObject::tr("verifier etat\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (quantiter <=0)
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme quantiter"),
                        QObject::tr("verifier quantiter\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (paiement=="")
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme paiement"),
                        QObject::tr("verifier paiement\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
       else if (categorie=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("probleme categorie"),
                       QObject::tr("verifier categorie\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
        else
        {
            mat P(num,nom,prix,etat,quantiter,paiement,categorie);
            bool test=P.Ajouter();
            if(test)
             {    QMessageBox::information(nullptr, QObject::tr("Materiels est ajoutée"),
                                           QObject::tr("Ajout Terminer.\n"
                                                       "Cliquer Ok pour Continuer."), QMessageBox::Ok);
                ui->tableView->setModel(P.afficher());
                {  /*clear after ajouter*/

                    ui->lineEdit ->clear();
                     ui->lineEdit_2->clear();
                           ui->lineEdit_3->clear();



                       }

          }
       }
}

void materille::on_pushButton_4_clicked()
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
            int num = index.sibling(index.row(), 0).data().toInt(); // Remplacez "0" par l'index de votre colonne d'identifiant unique

            // Supprimer la ligne correspondante dans la base de données
            QSqlQuery query;
            query.prepare("DELETE FROM MATERILELS where num=:num");
            query.bindValue(":num", num);
            query.exec();

            // Mettre à jour le table view pour refléter les modifications
            ui->tableView->setModel(p.afficher());
}
        }
}

void materille::on_pushButton_5_clicked()
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
void materille::on_pushButton_clicked()
{
    QString num = ui->lineEdit_4->text();

               // Effectuer la requête SELECT pour récupérer les données correspondantes dans la base de données
               QSqlQuery query;
               query.prepare("SELECT * FROM MATERILELS WHERE num = ?");
               query.bindValue(0, num);
               query.exec();

               if (query.next()) {
                   // Récupérer les valeurs de chaque colonne
                   QString num = query.value("num").toString();
                   QString nom = query.value("nom").toString();
                   QString prix = query.value("prix").toString();
                   QString etat = query.value("etat").toString();
                   int quantiter = query.value("QUANTITE").toInt();
                   QString paiement = query.value("PAIEMENT").toString();
                   QString categorie = query.value("CATEGORIE").toString();

                   // Afficher les valeurs récupérées dans les champs correspondants de l'interface graphique


                       ui->lineEdit_2->setText(nom);
                       ui->lineEdit_3->setText(prix);
                       ui->comboBox->setCurrentText(etat);
                      ui->spinBox->setValue(quantiter);
                    ui->comboBox_2->setCurrentText(paiement);
                      ui->comboBox_3->setCurrentText(categorie);

               } else {
                   // Afficher un message d'erreur si aucune donnée n'a été trouvée pour la référence donnée
                   QMessageBox::critical(this, "Erreur", "Aucune donnée trouvée pour la référence donnée.");
               }
}


void materille::on_pushButton_2_clicked()
{
    QString num=ui->lineEdit_4 ->text();
        QString nom=ui->lineEdit_2->text();
        QString prix=ui->lineEdit_3->text();
        QString etat=ui->comboBox->currentText();
        int quantite=ui->spinBox->text().toInt();
       QString paiement=ui->comboBox_2->currentText();
       QString categorie=ui->comboBox_3->currentText();

       if (((!p.verif_num(num))&&(num.length()<=6))||(num==""))
       {
            QMessageBox::critical(nullptr, QObject::tr("probleme en num"),
                        QObject::tr("verifier num\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
  else if((!p.verif_alpha(nom))||(nom==""))
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme en nom"),
                        QObject::tr("verifier nom\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
       else  if ((p.verif_alpha(prix))||(prix==""))
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme en prix"),
                        QObject::tr("verifier prix\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (etat=="")
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme en etat"),
                        QObject::tr("verifier etat\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (quantite <=0)
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme quantiter"),
                        QObject::tr("verifier quantiter\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (paiement=="")
        {
            QMessageBox::critical(nullptr, QObject::tr("probleme paiement"),
                        QObject::tr("verifier paiement\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
       else if (categorie=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("probleme categorie"),
                       QObject::tr("verifier categorie\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
        else
        {
        mat m(num,nom,prix,etat,quantite,paiement,categorie);
        bool test=m.modifier(num);
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


void materille::on_lineEdit_5_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM MATERILELS WHERE num  LIKE'"+arg1+"%' ");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("n'exsiste pas !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_5->clear();}
}

void materille::on_pushButton_6_clicked()
{
    QSqlDatabase db;

                                QTableView tableView;
                                QSqlQueryModel * Modal=new  QSqlQueryModel();

                                QSqlQuery qry;
                                 qry.prepare("SELECT* FROM MATERILELS");
                                 qry.exec();
                                 Modal->setQuery(qry);
                                 tableView.setModel(Modal);

                                 db.close();

                                 QString strStream;
                                 QTextStream out(&strStream);

                                 const int rowCount = tableView.model()->rowCount();
                                 const int columnCount =  tableView.model()->columnCount();

                                 const QString strTitle ="Listedesmaterilles";

                                 out <<  "<html>\n"
                                         "<img src='C:/Users/kamel/Downloads/logo.png' height='155' width='140'/>"
                                     "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     <<  QString("<title>%1</title>\n").arg(strTitle)
                                     <<  "</head>\n"
                                     "<body bgcolor=#ffffff link=#5000A0>\n"
                                    << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES materilles")
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

                                 QTextDocument *ListeDesmaterilles = new QTextDocument();
                                 ListeDesmaterilles->setHtml(strStream);

                                 QPrinter printer;
                                 QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                 if (dialog->exec() == QDialog::Accepted)
                                 {

                                     ListeDesmaterilles->print(&printer);
                                 }
                                 printer.setOutputFormat(QPrinter::PdfFormat);
                                 printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName("/tmp/Produit.pdf");
                                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                 delete ListeDesmaterilles;
}

void materille::on_pushButton_7_clicked()
{

        // Récupérer les statistiques des conférences
            QSqlQueryModel model;
            model.setQuery("SELECT COUNT(*) as paiement FROM MATERILELS GROUP BY PAIEMENT;");

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
            chart->setTitle("Statistiques des paiement");
            chart->setAnimationOptions(QChart::AllAnimations);
            chart->legend()->setAlignment(Qt::AlignRight);
            chart->legend()->setFont(QFont("Arial", 10));

            // Afficher le graphique dans une boîte de dialogue
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setMinimumSize(822, 622);

            QDialog *dialog = new QDialog();
            QVBoxLayout *layout = new QVBoxLayout(dialog);
            layout->addWidget(chartView);
            dialog->setWindowTitle("Statistiques des paiement");
            dialog->exec();

            // Nettoyer les objets alloués dynamiquement
          //  delete series;
           // delete chart;
           // delete chartView;
           // delete dialog;
    }


void materille::on_pushButton_9_clicked()
{
     ui->tableView->setModel(p.afficher_categorie());
}

void materille::on_pushButton_8_clicked()
{
    ui->tableView->setModel(p.afficher_num());
}

void materille::on_pushButton_10_clicked()
{
    //connect(ui->image22, &QPushButton::clicked, image, &Image::uploadImage);
       // Ouvrir une boîte de dialogue pour sélectionner l'image à uploader
       QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg)");

       // Afficher l'image sélectionnée dans l'étiquette
       QPixmap pixmap(filePath);
       imageLabel->setPixmap(pixmap);
       imageLabel->setScaledContents(true);
}
void materille::uploadImage()
{
    // Ouvrir une boîte de dialogue pour sélectionner l'image à uploader
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg)");

    // Afficher l'image sélectionnée dans l'étiquette
    QPixmap pixmap(filePath);
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);
}
