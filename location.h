#ifndef LOCATION_H
#define LOCATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>
#include "formupdatereservation.h"
#include "ui_formupdatereservation.h"

namespace Ui {
class Location;
}

class Location : public QDialog
{
    Q_OBJECT

public:
    explicit Location(QWidget *parent = nullptr);
    ~Location();
    void getLocations();

private slots:
    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

private:
    Ui::Location *ui;
    QSqlQueryModel * locations;
    void refreshDB();
    formUpdateReservation * formUpdateReserv;

};

#endif // LOCATION_H
