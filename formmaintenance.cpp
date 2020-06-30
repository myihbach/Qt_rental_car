#include "formmaintenance.h"
#include "ui_formmaintenance.h"

formMaintenance::formMaintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formMaintenance)
{
    ui->setupUi(this);
    this->setWindowTitle("Maintenance");
    ui->input_date_entree->setDisplayFormat("yyyy-MM-dd");
    ui->input_date_sortie->setDisplayFormat("yyyy-MM-dd");
    ui->input_date_entree->setMinimumDate(QDate::currentDate());
    ui->input_date_sortie->setMinimumDate(QDate::currentDate());

}

formMaintenance::~formMaintenance()
{
    delete ui;
}

Ui::formMaintenance *formMaintenance::getUi()
{
    return ui;
}

void formMaintenance::setId(QString id)
{
    this->id = id ;
}



void formMaintenance::on_pushButton_clicked()
{
    if(ui->pushButton->text() == "Ajouter"){



        QString matricule = ui->input_matricule->text();
        QString description = ui->input_description->text();
        QString date_entree = ui->input_date_entree->text();
        QString date_sortie = ui->input_date_sortie->text();
        QString prix = ui->input_prix->text();

        qDebug() << matricule << description << date_entree << date_sortie << prix;

             QSqlQuery query;
             if(query.exec("INSERT INTO maintenances ( description,voiture_id,date_entree,date_sortie,prix) VALUES ('"+description+"','"+matricule+"','"+date_entree+"','"+date_sortie+"','"+prix+"');"))
                 qDebug() << "Well inserted" ;
             else
                 qDebug() << "Error d'insertion : "<< query.lastError().text();


    }

    if(ui->pushButton->text() == "Modifier"){


        qDebug() << "my id :  "<< this->id;
        QString matricule = ui->input_matricule->text();
        QString description = ui->input_description->text();
        QString date_entree = ui->input_date_entree->text();
        QString date_sortie = ui->input_date_sortie->text();
        QString prix = ui->input_prix->text();
        qDebug() << matricule << description << date_entree << date_sortie << prix;


            QSqlQuery query;

            if(query.exec("UPDATE maintenances SET description = '"+description+"' , voiture_id = '"+matricule+"' , date_entree = '"+date_entree+"' ,date_sortie = '"+date_sortie+"' , prix = '"+prix+"'  where id = '"+this->id+"' ;"))

                qDebug() << "Well updated" ;
            else
                qDebug() << "Error de mise a jour :"<< query.lastError().text();

    }

    this->close();
}
