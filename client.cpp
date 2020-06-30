#include "client.h"
#include "ui_client.h"
#include "formclient.h"
#include "ui_formclient.h"

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowTitle("Clients");
    model = new QSqlQueryModel();
    getModels();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setColumnHidden(0, true);// cacher la colone des ids
    this->setWindowTitle("Client");
    ui->tableView->setCurrentIndex(QModelIndex(ui->tableView->model()->index(-1,1)));

}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_ajouter_clicked()
{
    formClient form;
    form.setModal(true);
    form.getUi()->pushButton->setText("Ajouter");
    form.exec();
    getModels();
}

void Client::getModels()
{
    model->setQuery("select id , nom || ' ' || prenom as 'Nom',mail as 'Email' ,tel as 'Telephone' from clients order by nom");
    ui->tableView->setModel(model);

}

void Client::on_pushButton_modifier_clicked()
{
    int position = ui->tableView->currentIndex().row();// reccuperer la position de ligne selectionner
    if( position != -1 ){
            QModelIndex newIndex = ui->tableView->model()->index(position,0);//colone 0 Qui contient les ID des cliets
            ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
            QString id = newIndex.data(Qt::DisplayRole).toString();

            QSqlQuery query;

            formClient form;
            form.setId(id);
            form.setModal(true);
            form.getUi()->pushButton->setText("Modifier");
            if(query.exec("select nom , prenom ,address , tel, dateNaissance , mail from clients where id='"+id+"';")){
                    query.first();
                    qDebug() << "we got the client";
                    form.getUi()->input_nom->setText(query.value("nom").toString());
                    form.getUi()->input_prenom->setText(query.value("prenom").toString());
                    form.getUi()->input_tel->setText( query.value("tel").toString());
                    form.getUi()->input_adress->setText( query.value("address").toString());
                    form.getUi()->input_mail->setText(query.value("mail").toString());
                    qDebug() << query.value("dateNaissance");
                    form.getUi()->input_date->setDate(QDate::fromString(query.value("dateNaissance").toString(),"yyyy-MM-dd"));

            }
            form.exec();
            getModels();
    }
}

void Client::on_pushButton_supprimer_clicked()
{
    int position = ui->tableView->currentIndex().row();// reccuperer la position de ligne selectionner
    if( position != -1 ){
        QModelIndex newIndex = ui->tableView->model()->index(position,0); // la colonne 0 contient les ids en mode hidden
        ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
        QString id = newIndex.data(Qt::DisplayRole).toString();
        QSqlQuery query;
        if(query.exec("delete from clients where id='"+id+"'"))
                qDebug() << "deleted";
        else
                qDebug() << "Error : "<< query.lastError().text();
        getModels();
    }

}
