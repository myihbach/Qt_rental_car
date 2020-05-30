#ifndef FORMRESERVATION_H
#define FORMRESERVATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class formReservation;
}

class formReservation : public QDialog
{
    Q_OBJECT

public:
    explicit formReservation(QWidget *parent = nullptr);
    ~formReservation();
    QString getMatricule();
    void setMAtricule(QString);
    Ui::formReservation * getUi();

private:
    Ui::formReservation *ui;
protected :
    QString matricule;
private slots:
    void on_pushButton_reserver_clicked();
};

#endif // FORMRESERVATION_H
