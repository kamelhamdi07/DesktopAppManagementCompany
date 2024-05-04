#ifndef DIALOG_H
#define DIALOG_H
#include "publication.h"
#include <QDialog>
#include <arduino.h>
#include <incendie.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_rech_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked(bool checked);

    void on_pushButton_5_clicked();

    void on_bn_android_7_clicked();


    void on_label_7_linkActivated(const QString &link);

    void on_bn_cloud_4_clicked();

    void on_myPushButton_clicked();

    void on_noti_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Dialog *ui;
    publication p;
    arduino A ;
       QByteArray data;

};

#endif // DIALOG_H
