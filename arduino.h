#ifndef ARDUINO_H
#define ARDUINO_H
#include "QtSerialPort/QSerialPort"
#include "QtSerialPort/qserialportinfo.h"
#include<QDebug>
#include<QSqlQueryModel>




class arduino
{
public:

    arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort* getserial(){return serial;};
    QString getarduino_port_name(){return arduino_port_name;};
   // QSqlQueryModel * afficher() ;

public:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 0x1A86;
      static const quint16 arduino_uno_product_id = 0x7523;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data ;


};




#endif // ARDUINO_H
