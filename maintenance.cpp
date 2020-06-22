#include "maintenance.h"
#include "ui_maintenance.h"
#include "formmaintenance.h"
#include "ui_formmaintenance.h"

Maintenance::Maintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Maintenance)
{
    ui->setupUi(this);
    this->setWindowTitle("Maintenance");
    model = new QSqlQueryModel();
    getModel();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

Maintenance::~Maintenance()
{
    delete ui;
}

void Maintenance::getModel()
{
    model->setQuery("select m.id , m.description , v.modele ,m.date_sortie , m.prix from maintenances m join voitures v on m.voiture_id = v.matricule ");
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);// la colonne des Id est cachée

}



void Maintenance::on_pushButton_ajouter_clicked()
{
    formMaintenance form(this);
    form.getUi()->pushButton->setText("Ajouter");
    form.setModal(true);
    form.exec();
    getModel();
}

void Maintenance::on_pushButton_modifier_clicked()
{

    int position = ui->tableView->currentIndex().row();// reccuperer la position de ligne selectionner
    QModelIndex newIndex = ui->tableView->model()->index(position,0);//colone 0 Qui contient les ID des cliets
    ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
    QString id = newIndex.data(Qt::DisplayRole).toString();

    QSqlQuery query;

    formMaintenance form(this);
    form.setId(id);
    form.getUi()->pushButton->setText("Modifier");
    form.setModal(true);
    if(query.exec("select description , date_entree ,date_sortie , voiture_id, prix from maintenances where id='"+id+"';")){
            query.first();
            qDebug() << "we got the maintenances";
            form.getUi()->input_prix->setText(query.value("prix").toString());
            form.getUi()->input_matricule->setText(query.value("voiture_id").toString());
            form.getUi()->input_description->setText( query.value("description").toString());
            form.getUi()->input_date_entree->setDate(QDate::fromString(query.value("date_entree").toString(),"yyyy-MM-dd"));
            form.getUi()->input_date_sortie->setDate(QDate::fromString(query.value("date_sortie").toString(),"yyyy-MM-dd"));

    }
    form.exec();
    getModel();
}

void Maintenance::on_pushButton_supprimer_clicked()
{
    int position = ui->tableView->currentIndex().row();// reccuperer la position de ligne selectionner
    QModelIndex newIndex = ui->tableView->model()->index(position,0); // la colonne 0 contient les ids en mode hidden
    ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
    QString id = newIndex.data(Qt::DisplayRole).toString();
    QSqlQuery query;
    if(query.exec("delete from maintenances where id='"+id+"'"))
            qDebug() << "deleted";
    else
            qDebug() << "Error : "<< query.lastError().text();
    getModel();
}
