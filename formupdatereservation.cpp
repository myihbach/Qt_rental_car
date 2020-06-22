#include "formupdatereservation.h"
#include "ui_formupdatereservation.h"

formUpdateReservation::formUpdateReservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formUpdateReservation)
{
    ui->setupUi(this);
    ui->date_reservation->setDisplayFormat("yyyy-MM-dd");
    ui->date_reservation->setMinimumDate(QDate::currentDate());


}

formUpdateReservation::~formUpdateReservation()
{
    delete ui;
}

Ui::formUpdateReservation *formUpdateReservation::getUi()
{
    return ui;
}

void formUpdateReservation::setId(QString id)
{
    this->id=id;
}

void formUpdateReservation::on_pushButton_modifier_clicked()
{
    QString client_id = ui->input_client->text();
    QString matricule = ui->input_matricule->text();
    QString nbr_jour = QString::number(ui->nbr_jour->value());
    QString dateReservation = ui->date_reservation->text();

    qDebug() <<"nbr de jour : "<< nbr_jour ;
    QSqlQuery query;
    if(query.exec("update locations set date_location='"+dateReservation+"' , nbr_jour='"+nbr_jour+"' , client_id='"+client_id+"' , voiture_id='"+matricule+"' where id='"+this->id+"' ;"))
            qDebug() << "Updated ";
    else
            qDebug() << "error : "<< query.lastError().text();
    qDebug() <<"data : "<< client_id << nbr_jour << dateReservation << matricule ;

    this->close();
}
