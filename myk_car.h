#ifndef MYK_CAR_H
#define MYK_CAR_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QtSql>
#include "voiture.h"
#include "location.h"
#include "maintenance.h"
#include "client.h"
#include "formvoiture.h"
#include "gain.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MYK_CAR; }
QT_END_NAMESPACE

class MYK_CAR : public QMainWindow
{
    Q_OBJECT

public:
    MYK_CAR(QWidget *parent = nullptr);
    ~MYK_CAR();

private slots:


    void on_pushButton_voitures_clicked();

    void on_pushButton_clients_clicked();

    void on_pushButton_maintenance_clicked();

    void on_pushButton_locations_clicked();



    void on_pushButton_gain_clicked();

private:
    Ui::MYK_CAR *ui;
    QSqlDatabase db;
    void connectionToDB();
    void setBackgroundImage();
};
#endif // MYK_CAR_H
