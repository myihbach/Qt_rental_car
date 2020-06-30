#include "gain.h"
#include "ui_gain.h"

Gain::Gain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gain)
{
    ui->setupUi(this);
    this->setWindowTitle("Resultats");
    ui->tableView_charge->verticalHeader()->hide();
    ui->tableView_produit->verticalHeader()->hide();
    ui->tableView_charge->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_charge->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_charge->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_produit->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_produit->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_produit->setSelectionMode(QAbstractItemView::SingleSelection);
    getModels();
    getTotal();
    ui->tableView_charge->setModel(charge);
    ui->tableView_produit->setModel(produit);
    ui->lcdNumber_gain->display(resultats);

}

Gain::~Gain()
{
    delete ui;
}

void Gain::getModels()
{
        charge = new QSqlQueryModel();
        produit = new QSqlQueryModel();
        charge->setQuery("select strftime('%m',date_entree)  AS Mois, SUM(prix)||' DH' AS charge FROM maintenances GROUP BY strftime('%m',date_entree)");
        produit->setQuery("select strftime('%m',date_location)  AS Mois, SUM(prix)||' DH' AS produit from locations GROUP BY strftime('%m',date_location)");
}

void Gain::getTotal()
{
    QSqlQuery query_charge;
    QSqlQuery query_produit;
    int charges = 0 ;
    int produits = 0;
    if(query_charge.exec("select sum(prix) as 'sum' from maintenances   ;")){
            query_charge.first();
            charges = query_charge.value("sum").toInt();

    }
    else
            qDebug() << "Error : " << query_charge.lastError().text();

    if(query_produit.exec("select sum(prix) as 'sum' from locations  ;")){
            query_produit.first();
            produits = query_produit.value("sum").toInt();

    }
    else
            qDebug() << "Error : " << query_charge.lastError().text();

    resultats = produits- charges;
}
