#ifndef MATERILLE_H
#define MATERILLE_H

#include <QDialog>
#include<QPushButton>
#include<QLabel>
#include "mat.h"
namespace Ui {
class materille;
}

class materille : public QDialog
{
    Q_OBJECT

public:
    explicit materille(QWidget *parent = nullptr);
    ~materille();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();
    void uploadImage();

private:
    Ui::materille *ui;
    mat p;
    QPushButton *uploadButton;
    QLabel *imageLabel;
};

#endif // MATERILLE_H
