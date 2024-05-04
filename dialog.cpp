#include "dialog.h"
#include "publication.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QDate>
#include<QtPrintSupport/QtPrintSupport>
#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QtCharts/QtCharts>
#include <arduino.h>
#include "incendie.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)

{  arduino A;
    ui->setupUi(this);
        ui->tableView->setModel(p.afficher());

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString ref=ui->lineEdit_3->text();
        QString type=ui->comboBox->currentText();
        QDate date=ui->dateEdit->date();
        QDate defDate(01, 01, 2002);


        if (ref == "" )
        {
            QMessageBox::critical(nullptr, QObject::tr("problem ref"),
                        QObject::tr("verifier ref\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else if (type=="" )
        {
            QMessageBox::critical(nullptr, QObject::tr("problem nom"),
                        QObject::tr("verifier nom\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
       else if (date== defDate  )
        {
            QMessageBox::critical(nullptr, QObject::tr("problem date"),
                        QObject::tr("verifier date\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }

        else
        {
            publication E(ref,type,date);
            bool test=E.Ajouter();
          if(test)
           {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                         QObject::tr("ajout successful.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
              ui->tableView->setModel(E.afficher());

              QString okd="";

}
        }
        QPushButton* bouton = ui->noti;
        bouton->setStyleSheet("background-color: red;");

}

void Dialog::on_pushButton_3_clicked()
{
    publication e1;
    e1.setref(ui->lineEdit->text());
    bool test;
    test=e1.Supprime(e1.getref());
    if(e1.getref()==8)
     {     QMessageBox::critical(nullptr, QObject::tr("sup errer"),
                                 QObject::tr("referance n'existe pas.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if(test)
     {    QMessageBox::information(nullptr, QObject::tr("supp avec succes"),
                                   QObject::tr("suppression successful.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView->setModel(e1.afficher());
               }
                   else
                       QMessageBox::critical(nullptr, QObject::tr("sup errer"),
                                   QObject::tr("suppression failed.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void Dialog::on_pushButton_2_clicked()
{
    QString ref=ui->lineEdit_2->text();
    QString type=ui->comboBox->currentText();
    QDate date=ui->dateEdit->date();
    QDate defDate(01, 01, 2002);


    if (ref == "" )
    {
        QMessageBox::critical(nullptr, QObject::tr("problem ref"),
                    QObject::tr("verifier ref\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if (type=="" )
    {
        QMessageBox::critical(nullptr, QObject::tr("problem nom"),
                    QObject::tr("verifier nom\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
   else if (date== defDate  )
    {
        QMessageBox::critical(nullptr, QObject::tr("problem date"),
                    QObject::tr("verifier date\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
            else
            {
            publication m(ref,type,date);
            bool test=m.modifier(ref);
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







void Dialog::on_rech_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT * FROM PUBLICATION WHERE REFERENCE  LIKE'"+arg1+"%' ");
             query->exec();
             if (query->next()) {
             model->setQuery(*query);
             ui->tableView->setModel(model);
             }
             else {
                 QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                                 QObject::tr("publication n'exsiste pas!.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
                 ui->rech->clear();}


}

void Dialog::on_pushButton_4_clicked()
{
    ui->lineEdit_3->clear();
    //ui->comboBox->clear();
   ui->dateEdit->clear();
}

void Dialog::on_pushButton_5_clicked()
{
    QString ref = ui->lineEdit_2->text();

               // Effectuer la requête SELECT pour récupérer les données correspondantes dans la base de données
               QSqlQuery query;
               query.prepare("SELECT * FROM PUBLICATION WHERE REFERENCE = ?");
               query.bindValue(0, ref);
               query.exec();

               if (query.next()) {
                   // Récupérer les valeurs de chaque colonne
                   QString type = query.value("type").toString();
                   QDate date_pub = query.value("date_pub").toDate();


                   // Afficher les valeurs récupérées dans les champs correspondants de l'interface graphique
                   ui->comboBox->setCurrentText(type);
                   ui->dateEdit->setDate(date_pub);

               } else {
                   // Afficher un message d'erreur si aucune donnée n'a été trouvée pour la référence donnée
                   QMessageBox::critical(this, "Erreur", "Aucune donnée trouvée pour la référence donnée.");
}
}

void Dialog::on_bn_android_7_clicked()
{
    QSqlDatabase db;

                                QTableView tableView;
                                QSqlQueryModel * Modal=new  QSqlQueryModel();

                                QSqlQuery qry;
                                 qry.prepare("SELECT* FROM PUBLICATION");
                                 qry.exec();
                                 Modal->setQuery(qry);
                                 tableView.setModel(Modal);

                                 db.close();

                                 QString strStream;
                                 QTextStream out(&strStream);

                                 const int rowCount = tableView.model()->rowCount();
                                 const int columnCount =  tableView.model()->columnCount();

                                 const QString strTitle ="Listepublication";

                                 out <<  "<html>\n"
                                         "<img src='C:/Users/user/Desktop/c++/projet/log.png' height='155' width='140'/>"
                                     "<head>\n"
                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                     <<  QString("<title>%1</title>\n").arg(strTitle)
                                     <<  "</head>\n"
                                     "<body bgcolor=#ffffff link=#5000A0>\n"
                                    << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES PUBLICATION")
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

                                 QTextDocument *ListeDespublication = new QTextDocument();
                                 ListeDespublication->setHtml(strStream);

                                 QPrinter printer;
                                 QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                 if (dialog->exec() == QDialog::Accepted)
                                 {

                                     ListeDespublication->print(&printer);
                                 }
                                 printer.setOutputFormat(QPrinter::PdfFormat);
                                 printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName("/tmp/Produit.pdf");
                                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                 delete ListeDespublication;
}








void Dialog::on_noti_clicked()
{
    QString ref=ui->lineEdit_3->text();
        QString type=ui->comboBox->currentText();
        QDate date=ui->dateEdit->date();
        QDate defDate(01, 01, 2002);
        QMessageBox::StandardButton confirmMsg;
        confirmMsg=QMessageBox::warning(this,"This ref has been added","REF :"+ref+" TYPE :"+type+" DATE :"+date.toString("yyyy/dd/MM"),QMessageBox::Ok);
        if(confirmMsg == QMessageBox::Ok)
        { QPushButton* bouton = ui->noti;
            bouton->setStyleSheet("background-color: grey;");}
        ui->lineEdit_3->clear();
        ui->comboBox->clear();
        ui->dateEdit->clear();
}

void Dialog::on_pushButton_6_clicked()
{/*
    // Récupérer les statistiques des conférences
            QSqlQueryModel model;
            model.setQuery("SELECT COUNT(*) as type, type FROM PUBLICATION GROUP BY type;");

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
                int categories = model.data(model.index(i, 0)).toInt();
                qreal percentage = (qreal) categories / total * 100.0;
                QString label = QString("%1 (%2%)").arg(mode).arg(QString::number(percentage, 'f', 2));
                series->append(label, categories);
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des type");
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
            dialog->setWindowTitle("Statistiques des type");
            dialog->exec();

            // Nettoyer les objets alloués dynamiquement
          //  delete series;
           // delete chart;
           // delete chartView;
           // delete dialog; */
    incendie inc;
        inc.exec();
}
