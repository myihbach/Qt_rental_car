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
    ui->dateReservation->setDisplayFormat("yyyy-MM-dd");
    ui->dateReservation->setMinimumDate(QDate::currentDate());
    ui->nbr_jours->setMinimum(1);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

    // recuperation des dates ou la voiture est reservée

    QString client_id = ui->client_id->text();
    int nbr_jour = ui->nbr_jours->value();
    QString dateReservation = ui->dateReservation->text();
    QSqlQuery prixVoitureQuery;

    //====================================================
    qDebug() << matricule;
    // voir si la voiture est deja reservé en future
    QSqlQuery query_;
    QString nbr("+"+QString::number(nbr_jour)+" days");
    qDebug() << nbr;

    if(query_.exec("select count(id) from locations where voiture_id = '"+matricule+"' and ( date_location BETWEEN '"+dateReservation+"' and date('"+dateReservation+"','"+nbr+"') or date(date_location,nbr_jour||' days') BETWEEN '"+dateReservation+"' and date('"+dateReservation+"','"+nbr+"') )"))
    {
        qDebug() << " sounds great";
        query_.first();
        if(query_.value(0).toInt() == 0){

            prixVoitureQuery.exec("select prix from voitures where matricule ='"+matricule+"';");
            prixVoitureQuery.first();
            float prix_voiture =prixVoitureQuery.value(0).toInt();
            float prix_location = prix_voiture * nbr_jour ;
            QSqlQuery query;
            if(query.exec("insert into locations (date_location,nbr_jour,client_id,voiture_id,prix) values('"+dateReservation+"','"+QString::number(nbr_jour)+"','"+client_id+"','"+matricule+"','"+QString::number(prix_location)+"');"))
                    qDebug() << "inserted ";
            else
                    qDebug() << "error : "<< query.lastError().text();

            this->close();
        }
        else{
            QMessageBox msg(this);
            msg.setText("La date que vous avez choisi est deja reservée. Svp verifier la liste ci-dessous.");
            msg.exec();
        }
    }
    else
        qDebug() << query_.lastError().text();

}
