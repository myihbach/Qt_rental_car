#include "formreservation.h"
#include "ui_formreservation.h"
#include <QDebug>
#include <QDate>

formReservation::formReservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formReservation)
{
    ui->setupUi(this);
    this->setWindowTitle("Reservation formulaire");
    ui->dateReservation->setDisplayFormat("dd/MM/yyyy");
    ui->dateReservation->setMinimumDate(QDate::currentDate());
    ui->nbr_jours->setMinimum(1);
    //this->matricules = matricules;

}

formReservation::~formReservation()
{
    delete ui;
}

QString formReservation::getMatricule()
{
    return matricule;
}

void formReservation::setMAtricule(QString mat)
{
    matricule = mat;
}

Ui::formReservation *formReservation::getUi()
{
    return ui;
}



void formReservation::on_pushButton_reserver_clicked()
{
    QString client_id = ui->client_id->text();
    QString nbr_jour = QString::number(ui->nbr_jours->value());
    QString dateReservation = ui->dateReservation->text();
    qDebug() <<"nbr de jour : "<< nbr_jour ;
    QSqlQuery query;
    if(query.exec("insert into locations (date_location,nbr_jour,client_id,voiture_id) values('"+dateReservation+"','"+nbr_jour+"','"+client_id+"','"+matricule+"');"))
            qDebug() << "inserted ";
    else
            qDebug() << "error : "<< query.lastError().text();
    qDebug() <<"data : "<< client_id << nbr_jour << dateReservation << matricule ;

    this->close();

}
