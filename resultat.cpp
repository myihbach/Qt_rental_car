#include "resultat.h"
#include "ui_resultat.h"

Resultat::Resultat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultat)
{
    ui->setupUi(this);
    //model->setQuery("SELECT A.Month as Mois , TotalIncomes as Location, TotalExpenses as Maintenace,  TotalIncomes- TotalExpenses AS Resultat FROM (select strftime('%m',date_location) AS Month, SUM(prix) AS TotalIncomes from locations GROUP BY strftime('%m',date_location)) Aleft JOIN (select strftime('%m',date_entree) AS Month, SUM(prix) AS TotalExpenses FROM maintenances GROUP BY strftime('%m',date_entree)) BON A.Month = B.Month;");
    //ui->tableView->setModel(model);
}

Resultat::~Resultat()
{
    delete ui;
}
