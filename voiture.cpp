#include "voiture.h"
#include "ui_voiture.h"

#include "formreservation.h"
#include "ui_formreservation.h"
#include "formupdatevoiture.h"
#include "ui_formupdatevoiture.h"


Voiture::Voiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voiture)
{
    ui->setupUi(this);
    ui->tableView_dispo->verticalHeader()->hide();
    ui->tableView_reserv->verticalHeader()->hide();
    ui->tableView_dispo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_reserv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_dispo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_dispo->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setWindowTitle("Voitures");
    voiture_dispo = new QSqlQueryModel();
    voiture_reserv = new QSqlQueryModel();
    getModels();
    ui->tableView_dispo->setCurrentIndex(QModelIndex(ui->tableView_dispo->model()->index(-1,1)));// pour eviter la selection par defaut
    //ui->tableView_dispo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView_reserv->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Voiture::~Voiture()
{
    delete ui;
}





void Voiture::on_pushButton_clicked()
{
        formAjoutVoiture = new formVoiture(this);
        formAjoutVoiture->setModal(true);
        formAjoutVoiture->exec();
        //refreshDB();
        getModels();


}

void Voiture::on_pushButton_reserver_clicked()
{
        int position = ui->tableView_dispo->currentIndex().row();// reccuperer la position de ligne selectionner
// je boucle sur toutes les elements de la lignes (les colonnes = 5 )
   /* for(int i=0;i<5;i++){

        QModelIndex newIndex = ui->tableView_dispo->model()->index(position,i); // index de chaque case de la ligne
        ui->tableView_dispo->selectionModel()->select(newIndex, QItemSelectionModel::Select);// selection la case
        QString itemText = newIndex.data(Qt::DisplayRole).toString();// reccuperer la valeur de la case reccuperée
        qDebug() << itemText ; // afficher la case
    } */
        if(position != -1){
            QModelIndex newIndex = ui->tableView_dispo->model()->index(position,1);
            ui->tableView_dispo->selectionModel()->select(newIndex, QItemSelectionModel::Select);
            QString mat = newIndex.data(Qt::DisplayRole).toString();

            QSqlQueryModel * reserved_in = new QSqlQueryModel();
            reserved_in->setQuery("SELECT date_location as 'Reservée de ' , date(date_location,nbr_jour||' days') as ' A ' FROM locations where voiture_id='"+mat+"' and date_location > date('now') order by id desc;");
            formReservation form(this);
            form.setMAtricule(mat);
            form.setModal(true);
            form.getUi()->tableView->setModel(reserved_in);
            form.exec();
            getModels();
            //refreshDB();
        }



}

/*void Voiture::refreshDB()
{
    // getModels();
     voiture_dispo->setQuery("select m.nom ,v.matricule, v.modele , v.prix,v.couleur  from voitures v join marques m on v.marque_id=m.id");
     voiture_reserv->setQuery("select m.nom ,v.matricule, v.modele,  v.prix,v.couleur  from voitures v join marques m on v.marque_id=m.id");
     ui->tableView_dispo->setModel(voiture_dispo);
     ui->tableView_reserv->setModel(voiture_reserv);
     ui->tableView_dispo->verticalHeader()->hide();
     ui->tableView_reserv->verticalHeader()->hide();
     ui->tableView_dispo->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_dispo->setSelectionMode(QAbstractItemView::SingleSelection);
}*/

void Voiture::getModels(){
    voiture_dispo->setQuery("select mr.nom ,v.matricule, v.modele , v.prix,v.couleur  from voitures v join marques mr on v.marque_id=mr.id where v.matricule  not in (select voiture_id from maintenances where date('now') Between date_entree and date_sortie) and v.matricule not in ( select voiture_id from locations where date('now') Between date_location and date(date_location,'+'||nbr_jour||' day')) order by mr.nom;");
    voiture_reserv->setQuery("select mr.nom ,v.matricule, v.modele , v.prix,v.couleur  from voitures v join marques mr on v.marque_id=mr.id where v.matricule in (select voiture_id from maintenances where date('now') Between date_entree and date_sortie) or v.matricule in ( select voiture_id from locations where date('now') Between date_location and date(date_location,'+'||nbr_jour||' day')) order by id desc;");
    ui->tableView_dispo->setModel(voiture_dispo);
    ui->tableView_reserv->setModel(voiture_reserv);
    ui->tableView_dispo->setColumnHidden(1, true);// la colonne de matricule est cachée
    ui->tableView_reserv->setColumnHidden(1, true);// idem

}





void Voiture::on_pushButton_supprimer_clicked()
{
        int position = ui->tableView_dispo->currentIndex().row();// reccuperer la position de ligne selectionner
        if(position != -1){

            QModelIndex newIndex = ui->tableView_dispo->model()->index(position,1);
            ui->tableView_dispo->selectionModel()->select(newIndex, QItemSelectionModel::Select);
            QString mat = newIndex.data(Qt::DisplayRole).toString();
            QSqlQuery query;
            if(query.exec("delete from voitures where matricule='"+mat+"'"))
                    qDebug() << "deleted";
            else
                    qDebug() << "Error : "<< query.lastError().text();
            getModels();

        }

}

void Voiture::on_pushButton_modifier_clicked()
{
        int position = ui->tableView_dispo->currentIndex().row();// reccuperer la position de ligne selectionner
        if(position != -1){

            QModelIndex newIndex = ui->tableView_dispo->model()->index(position,1);
            ui->tableView_dispo->selectionModel()->select(newIndex, QItemSelectionModel::Select);
            QString mat = newIndex.data(Qt::DisplayRole).toString();
            QSqlQuery query;
            QString matricule=mat,modele,couleur,categorie_id,marque_id,prix;
            if(query.exec("select modele , couleur ,categorie_id , marque_id, prix from voitures where matricule='"+mat+"';")){
                    query.first();
                    qDebug() << "we get the item";
                    modele = query.value("modele").toString();
                    couleur = query.value("couleur").toString();
                    categorie_id = query.value("categorie_id").toString();
                    marque_id = query.value("marque_id").toString();
                    prix = query.value("prix").toString();

            }
            else
                    qDebug() << "Error : " << query.lastError().text();

                    QSqlQuery cat ;
                    cat.exec("select nom from categories where id ='"+categorie_id+"'");
                    cat.first();

                    QSqlQuery mar ;
                    mar.exec("select nom from marques where id ='"+marque_id+"'");
                    mar.first();


                    formUpdateVoi = new formUpdateVoiture(this);
                    formUpdateVoi->setModal(true);
                    formUpdateVoi->getUi()->comboBox_categorie->setCurrentText(cat.value(0).toString());
                    formUpdateVoi->getUi()->comboBox_marque->setCurrentText(mar.value(0).toString());
                    formUpdateVoi->getUi()->input_matricule->setText(matricule);
                    formUpdateVoi->getUi()->input_modele->setText(modele);
                    formUpdateVoi->getUi()->input_prix->setText(prix);
                    formUpdateVoi->getUi()->input_couleur->setText(couleur);
                    formUpdateVoi->exec();

                    getModels();
        }

}
