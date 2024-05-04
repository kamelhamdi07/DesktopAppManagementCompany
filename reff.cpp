#include "reff.h"
#include "ui_reff.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include<QPrinter>
#include <QPainter>
#include <arduino.h>
#include <QPixmap>
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <iostream>
#include <QTableView>
#include <QSortFilterProxyModel>



reff::reff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::reff)

    {

        ui->setupUi(this);
        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
         //ui->tableView_77->setModel(A.ard());

    }



reff::~reff()
{
    delete ui;
}


void reff::on_pushButton_clicked()
{

}

void reff::concatRfid()
{
    bool found =false;
            QString FNAMEE="",RFID,msg,ref;

            data =A.read_from_arduino();
            qDebug() <<"a=" << data;
            if (data!="#")
                        uid+=data;
                    else {
                        int pos = uid.lastIndexOf(QChar('/'));
                        qDebug() << "uid="<< uid.left(pos);
                        qDebug()  << uid;
                        if (uid=="26C8CA")
                        {
                            ui->label->setText("WELCOME ");
                            qDebug() << "WELCOME " ;

                        }else
                             qDebug() << "HOWAREYOU?" ;
                             ui->label->setText("WHOAREYOU");

                        //ui->label->setText(uid.left(pos));
                        QTableView tableView_amb;
                        QSqlQueryModel * Mod=new  QSqlQueryModel();
                                    QSqlQuery qry;
                                    qry.prepare("select * from UTILISATEURS");
                        qry.exec();
                        Mod->setQuery(qry);
                        tableView_amb.setModel(Mod);
                        const int ligne = tableView_amb.model()->rowCount();
                        for (int var = 0; var < ligne; var++) {
                                        if(tableView_amb.model()->data(tableView_amb.model()->index(var, 7))==uid)
                                        {
                                           ref= tableView_amb.model()->data(tableView_amb.model()->index(var, 0)).toString();

                                           RFID = tableView_amb.model()->data(tableView_amb.model()->index(var, 6)).toString();

                                           qDebug() << ref << "  "<<RFID  << "HERE";


                                           found=true;
                                           var=ligne;
                                        }
                        }
                                        if(found){
                                            //A.writeStringToArduino("Hello");
                                            qDebug()<<"Hello "<<FNAMEE;
                                            ui->label->setText(ref);
                                            //ui->label_3->setText(RFID);

                                            //this->hide();
                                            this->show();


                                        }else{
                                            qDebug()<<"error";
                                           // A.write_To_Arduino("ERROR");
                                            //ui->ER->setText("ERROR");
                                            ui->label->setText(ref);
                                            //ui->label_3->setText(RFID);
                                           // this->hide();
                                            this->show();
                                        }
                                        uid="";

                                                    found = false;
                                                    //qDebug() << uid;
                                         }

}

void reff::update_label()
{

    bool found =false;
            QString FNAMEE="",RFID,msg,ref;

            data =A.read_from_arduino();
            qDebug() <<"a=" << data;
            if (data!="#")
                        uid+=data;
                    else {
                        int pos = uid.lastIndexOf(QChar('/'));
                        qDebug() << "uid="<< uid.left(pos);
                        qDebug()  << uid;
                        if (uid==" 26 C8 CA 12 26 C8 CA 12")
                        {
                            found=true;

                            qDebug() << "WELCOME Kamel" ;
                            Refresh();


                        }else if (uid==" D3 33 A6 1D D3 33 A6 1D")
                        {
                            found=true;

                            qDebug() << "WELCOME Eya" ;
                            Refresh();

                        }else if (uid==" E3 85 2B AD E3 85 2B AD")
                        {
                            found=true;

                            qDebug() << "WELCOME Sarrah" ;
                            Refresh();

                        }else if (uid==" 3B 06 E8 2B 3B 06 E8 2B")
                        {
                            found=true;

                            qDebug() << "WELCOME Zied" ;
                            Refresh();

                        }
                        else
                        {
                             qDebug() << "NOT IDENTIFIED" ;
                             found=false;


                        //ui->label->setText(uid.left(pos));
            }
                        if (found)
                        {
                           ui->label->setText("WELCOME");
                        }else
                        {
                             ui->label->setText("NOT IDENTIFIED");
                        }
                        uid="";
}

}




void reff::Refresh()
{
    model->setQuery("SELECT LOGIN , ROLE FROM UTILISATEURS WHERE ID_REF= '" + uid + "'");
    if(model->lastError().isValid()){
            qDebug() << "Query error: " << model->lastError().text();
        }
        ui->Tab_Aff->setModel(model);
}







