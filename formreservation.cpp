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
    int nbr_jour = ui->nbr_jours->value();
    QString dateReservation = ui->dateReservation->text();
    QSqlQuery prixVoitureQuery;

    prixVoitureQuery.exec("select prix from voitures where matricule ='"+matricule+"';");
    prixVoitureQuery.first();
    float prix_voiture =prixVoitureQuery.value(0).toInt();
    float prix_location = prix_voiture * nbr_jour ;
    qDebug() <<"nbr de jour : "<< nbr_jour ;
    qDebug() <<"prix voiture : "<< prix_voiture ;
    qDebug() <<"prix location : "<< prix_location ;
    qDebug() <<"data : "<<dateReservation << nbr_jour <<client_id << matricule << prix_location  ;

    QSqlQuery query;
    if(query.exec("insert into locations (date_location,nbr_jour,client_id,voiture_id,prix) values('"+dateReservation+"','"+QString::number(nbr_jour)+"','"+client_id+"','"+matricule+"','"+QString::number(prix_location)+"');"))
            qDebug() << "inserted ";
    else
            qDebug() << "error : "<< query.lastError().text();

    this->close();

}
