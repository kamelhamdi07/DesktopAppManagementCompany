#ifndef PERSO_H
#define PERSO_H

#include "personnel.h"
#include <QDialog>

namespace Ui {
class perso;
}

class perso : public QDialog
{
    Q_OBJECT

public:
    explicit perso(QWidget *parent = nullptr);
    ~perso();

private slots:
    void on_ajout_clicked();

    void on_suprim_2_clicked();

    void on_modify_2_clicked();

    void on_reset_clicked();

    void on_rech_textChanged(const QString &arg1);

   // void on_TRI_clicked();


    //void on_Ajout_3_clicked();

    void on_imp_clicked();

    //void on_pushButton_clicked();

    void on_anuuler_clicked();

    //void on_id_modif_textChanged(const QString &arg1);

   // void on_bn_pers_2_clicked();

    //void on_bn_perso_2_clicked();

    void on_recupere_clicked();

    void on_act_clicked();

    void on_idi_clicked();

    void on_salary_clicked();

    void on_grade_clicked();

    void on_chatbot_clicked();

    void on_bn_pub_2_clicked();

private:
    Ui::perso *ui;
    person p;
};
#endif // PERSO_H
