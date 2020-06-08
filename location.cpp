#include "location.h"
#include "ui_location.h"


Location::Location(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Location)
{
    ui->setupUi(this);
    this->setWindowTitle("Locations");
    getLocations();
    ui->tableView->setModel(locations);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


}

Location::~Location()
{
    delete ui;
}

void Location::getLocations()
{
    locations = new QSqlQueryModel;
    locations->setQuery("select l.id,v.modele ,l.date_location , l.nbr_jour from locations l join voitures v on l.voiture_id=v.matricule");
    ui->tableView->verticalHeader()->hide();
}


void Location::on_pushButton_modifier_clicked()
{
        int position = ui->tableView->currentIndex().row();// reccuperer la position de ligne selectionner
        QModelIndex newIndex = ui->tableView->model()->index(position,0);
        ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
        QString id = newIndex.data(Qt::DisplayRole).toString();
        QSqlQuery query;
        QString date_location,nbr_jour,client_id ,matricule;
        if(query.exec("select date_location, nbr_jour ,client_id,voiture_id from locations where id='"+id+"';")){
                query.first();
                qDebug() << "we get the item";
                date_location = query.value("date_location").toString();
                nbr_jour = query.value("nbr_jour").toString();
                client_id = query.value("client_id").toString();
                matricule = query.value("voiture_id").toString();
        }
        else
                qDebug() << "Error : " << query.lastError().text();


        formUpdateReserv = new formUpdateReservation(this);
        formUpdateReserv->setModal(true);
        formUpdateReserv->getUi()->input_client->setText(id);
        formUpdateReserv->getUi()->input_matricule->setText(matricule);
        formUpdateReserv->getUi()->nbr_jour->setValue(nbr_jour.toInt());
        formUpdateReserv->getUi()->date_reservation->setDate(QDate::fromString(date_location,"yyyy-MM-dd"));
        formUpdateReserv->setId(id);
        formUpdateReserv->exec();
        refreshDB();

}


void Location::on_pushButton_supprimer_clicked()
{
    int position = ui->tableView->currentIndex().row();// reccuperer la position de ligne selectionner

        QModelIndex newIndex = ui->tableView->model()->index(position,0);
        ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
        QString id = newIndex.data(Qt::DisplayRole).toString();
        qDebug() << "id : "<<id ;
        QSqlQuery query;
        if(query.exec("delete from locations where id='"+id+"';"))
                qDebug() << "deleted";
        else
                qDebug() << "Error : "<< query.lastError().text();
        refreshDB();

}

void Location::refreshDB()
{
    getLocations();
    ui->tableView->setModel(locations);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}
