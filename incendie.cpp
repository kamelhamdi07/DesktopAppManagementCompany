#include "incendie.h"
#include "ui_incendie.h"
#include <QTimer>
#include <QDialog>
#include <QDebug>



incendie::incendie(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::incendie)
{
    ui->setupUi(this);

    int ret=A.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to :"<<A.getarduino_port_name();
        break ;
    case(1):qDebug()<<"arduino is available and connected to :"<<A.getarduino_port_name();
        break ;
    case(-1):qDebug()<<"arduino is not available";
    }

    ui->label_1->setText("OFF");

}




incendie::~incendie()
{
    delete ui;
}



int incendie::lire_flamme()
{   int data1=0 ;

    A.write_to_arduino("1") ;

    do
    {
        A.serial->waitForReadyRead() ;
    }
    while(A.serial->bytesAvailable()!=2) ;

         data = A.read_from_arduino();


    if ( data == "10" )
    {
    data1 = 1 ;

    }
    else if ( data =="20")
    data1 =0;

   return data1 ;

}


void incendie::flamme()
{

{   int  flamme = lire_flamme();


   if (( flamme == 1 ) && (test==0) )
    {
       A.write_to_arduino("2") ;
       ui->label_1->setText("ON");
       QTime Time  =QTime::currentTime() ;
       Date1 = Time.toString("H:m:s a") ;
       test=1 ;

    }

   else if ((flamme == 0  ) && (test==1) )
    {
       A.write_to_arduino("3") ;
       QTime Time  =QTime::currentTime() ;
       Date2 = Time.toString("H:m:s a") ;
       ui->label_1->setText("OFF");

       ajouter() ;
       ui->tableView_date->setModel(afficher());


       test=0 ;

    }
}
}


void incendie::on_commencer_clicked()
{

    QTimer *timer = new QTimer(this) ;
    connect(timer,SIGNAL(timeout()),this,SLOT(flamme()) ) ;
    timer->start(500);


}



bool incendie::ajouter()
{

    QSqlQuery query;

    query.prepare("insert into incendie (DATE_INCENDIE, DATE_ARRET ) values (:DATE_ACTIVATION, :DATE_ARRET)" );
    query.bindValue(":DATE_ACTIVATION", Date1);
    query.bindValue(":DATE_ARRET", Date2);

    return query.exec();

};

QSqlQueryModel * incendie:: afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from incendie" );
    return model;
};



bool incendie::supprimerTout()
{
    QSqlQuery query;

    query.prepare("delete from incendie ");

    return query.exec();

}




void incendie::on_supprimer_date_clicked()
{
    supprimerTout() ;
    ui->tableView_date->setModel(afficher());
}
