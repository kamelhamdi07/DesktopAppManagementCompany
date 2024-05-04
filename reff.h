#ifndef REFF_H
#define REFF_H

#include "arduino1.h"
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QSqlDatabase>
#include <QMainWindow>
#include <QSqlError>
#include "arduino.h"
#include <QDialog>
#include <QDialog>

namespace Ui {
class reff;
}

class reff : public QDialog
{
    Q_OBJECT

public:
    explicit reff(QWidget *parent = nullptr);
    ~reff();
    void Refresh();
    private slots:
    void on_pushButton_clicked();
    void concatRfid();

    void on_tableView_activated(const QModelIndex &index);
    void update_label();
    void recherche();
private:
    Ui::reff *ui;
    Arduino A;
    QByteArray data;
    QString uid;
    QSqlQueryModel* model = new QSqlQueryModel();
};

#endif // REFF_H



/*QT_BEGIN_NAMESPACE
namespace Ui { class reff; }
QT_END_NAMESPACE

class reff : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

void Refresh();
private slots:
void on_pushButton_clicked();
void concatRfid();

void on_tableView_activated(const QModelIndex &index);
void update_label();
void recherche();

private:
    Ui::MainWindow *ui;
    Arduino A;
    QByteArray data;
    QString uid;
    QSqlQueryModel* model = new QSqlQueryModel();
};
#endif // MAINWINDOW_H*/
