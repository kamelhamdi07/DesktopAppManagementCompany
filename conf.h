#ifndef CONF_H
#define CONF_H

#include <QDialog>
#include "conference.h"

namespace Ui {
class conf;
}

class conf : public QDialog
{
    Q_OBJECT

public:
    explicit conf(QWidget *parent = nullptr);
    ~conf();

private slots:
    void on_Ajout_2_clicked();

    //void on_modify_2_clicked();

    void on_suprim_2_clicked();

    void on_reset_clicked();

    void on_rech_textChanged(const QString &arg1);

    //void on_Ajout_3_clicked();

    void on_impr_clicked();

    void on_pushButton_2_clicked();

    //void on_recupererButton_2_clicked();

   // void on_recupererButton_clicked();

   // void on_recupererButton_3_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

private:
    Ui::conf *ui;
    //Mailing L;
    conference C;

};

#endif // CONF_H
