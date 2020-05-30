#ifndef FORMUPDATERESERVATION_H
#define FORMUPDATERESERVATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class formUpdateReservation;
}

class formUpdateReservation : public QDialog
{
    Q_OBJECT

public:
    explicit formUpdateReservation(QWidget *parent = nullptr);
    ~formUpdateReservation();
    Ui::formUpdateReservation * getUi();
    void setId(QString);

private slots:
    void on_pushButton_modifier_clicked();

private:
    Ui::formUpdateReservation *ui;
    QString id;
};

#endif // FORMUPDATERESERVATION_H
