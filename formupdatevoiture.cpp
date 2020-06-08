#include "formupdatevoiture.h"
#include "ui_formupdatevoiture.h"

formUpdateVoiture::formUpdateVoiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formUpdateVoiture)
{
    ui->setupUi(this);
    QObject::connect(this,SIGNAL(rejected()),this,SLOT(refreshDBSlot()));
    this->setWindowTitle("Modification de voiture");
    ui->input_prix->setValidator( new QIntValidator(0, 10000, this) );
    getCategoriesAndMarques();
    ui->comboBox_marque->setModel(marques);
    ui->comboBox_categorie->setModel(categories);
}

formUpdateVoiture::~formUpdateVoiture()
{
    delete categories;
    delete marques;
    delete ui;
}

Ui::formUpdateVoiture *formUpdateVoiture::getUi()
{
    return ui;
}



void formUpdateVoiture::refreshDBSlot()
{
    emit refreshDBSignal("refresh the db");
}

void formUpdateVoiture::getCategoriesAndMarques(){
    categories = new QSqlQueryModel();
    marques = new QSqlQueryModel();
    categories->setQuery("select nom from categories");
    marques->setQuery("select nom from marques");
}

void formUpdateVoiture::on_pushButton_modifier_clicked()
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
    if(query.exec("UPDATE voitures SET modele = '"+mod+"', couleur = '"+coul+"' , categorie_id = '"+idCat+"', marque_id = '"+idMar+"', prix = '"+pri+"' WHERE matricule = '"+matri+"';"))
        qDebug() << " well updated" ;
    else
        qDebug() << " Error de modification :"<< query.lastError().text();

    this->close();
}
