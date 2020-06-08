#include "formclient.h"
#include "ui_formclient.h"


formClient::formClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formClient)
{
    ui->setupUi(this);
    ui->input_date->setDisplayFormat("yyyy-MM-dd");
}

formClient::~formClient()
{
    delete ui;
}

Ui::formClient *formClient::getUi()
{
    return ui;
}

void formClient::setId(QString id)
{
    this->id = id;
}

void formClient::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="Ajouter"){



        QString nom = ui->input_nom->text();
        QString prenom = ui->input_prenom->text();
        QString mail = ui->input_mail->text();
        QString tel = ui->input_tel->text();
        QString addr = ui->input_adress->text();
        QString date = ui->input_date->text();

        qDebug() << nom << prenom << mail << tel << addr << date;

        QSqlQuery query;

        if(query.exec("INSERT INTO clients ( nom,prenom,address,tel,mail,dateNaissance) VALUES ('"+nom+"','"+prenom+"','"+addr+"','"+tel+"','"+mail+"','"+date+"');"))
            qDebug() << " well inserted" ;
        else
            qDebug() << " Error d'insertion :"<< query.lastError().text();

    }
    if(ui->pushButton->text() == "Modifier"){


        qDebug() << "my id :  "<< this->id;
        QString nom = ui->input_nom->text();
        QString prenom = ui->input_prenom->text();
        QString mail = ui->input_mail->text();
        QString tel = ui->input_tel->text();
        QString addr = ui->input_adress->text();
        QString date = ui->input_date->text();

        qDebug() << nom << prenom << mail << tel << addr << date;

        QSqlQuery query;

        if(query.exec("UPDATE clients SET nom = '"+nom+"',prenom = '"+prenom+"',address = '"+addr+"',tel = '"+tel+"',mail = '"+mail+"',dateNaissance = '"+date+"' WHERE id = '"+this->id+"'"))
            qDebug() << " well inserted" ;
        else
            qDebug() << " Error d'insertion :"<< query.lastError().text();
    }


    this->close();

}
