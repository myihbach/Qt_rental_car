#include "voiture.h"
#include "ui_voiture.h"
#include "formvoiture.h"
#include "ui_formvoiture.h"

formVoiture::formVoiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formVoiture)
{
    ui->setupUi(this);
    //QObject::connect(this,SIGNAL(rejected()),this,SLOT(refreshDBSlot()));
    this->setWindowTitle("Voiture formulaire");
    ui->input_prix->setValidator( new QIntValidator(0, 10000, this) );
    getCategoriesAndMarques();
    ui->comboBox_marque->setModel(marques);
    ui->comboBox_categorie->setModel(categories);

}

formVoiture::~formVoiture()
{
    delete categories;
    delete marques;
    delete ui;
}

Ui::formVoiture * formVoiture::getUi()
{
    return ui;
}

void formVoiture::on_pushButton_ajouter_clicked()
{
    QString matri = ui->input_matricule->text();
    QString mod = ui->input_modele->text();
    QString coul = ui->input_couleur->text();
    QString pri = ui->input_prix->text();
    QString mar = ui->comboBox_marque->currentText();
    QString cat = ui->comboBox_categorie->currentText();
    // reccuperer les ids de categorie et de marque

    QSqlQuery queryCat;
    queryCat.exec("select id from categories where nom ='"+cat+"';");
    queryCat.first();
    QString idCat = queryCat.value(0).toString();
    while (queryCat.next()) {
         idCat = queryCat.value(0).toString();
    }
    qDebug() << "we get category id : " << idCat;

    QSqlQuery queryMar ;
    queryMar.exec("select id from marques where nom ='"+mar+"';");
    QString idMar;
    while (queryMar.next()) {
         idMar = queryMar.value(0).toString();
    }

    qDebug() << "we get marque id : " << idMar;

    qDebug() << matri << mod << coul << pri << idCat << idMar ;

    QSqlQuery query;
   // QString statement=");";
    if(query.exec("INSERT INTO voitures ( matricule,modele,couleur,prix,categorie_id,marque_id) VALUES ('"+matri+"','"+mod+"','"+coul+"','"+pri+"','"+idCat+"','"+idMar+"');"))
        qDebug() << " well inserted" ;
    else
        qDebug() << " Error d'insertion :"<< query.lastError().text();

    this->close();
}

/*
void formVoiture::refreshDBSlot()
{
    emit refreshDBSignal("refresh the db");
}
*/

void formVoiture::getCategoriesAndMarques(){
    categories = new QSqlQueryModel();
    marques = new QSqlQueryModel();
    categories->setQuery("select nom from categories");
    marques->setQuery("select nom from marques");
}



