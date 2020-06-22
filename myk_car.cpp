#include "myk_car.h"
#include "ui_myk_car.h"

MYK_CAR::MYK_CAR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MYK_CAR)
{
    ui->setupUi(this);
    QDesktopWidget dw; // pour reccuperer une widget dont les dimension sont ceux de l'écran
    int x=dw.width()*0.7; // recupperer les dimensions de l'app en 70% de l'écran
    int y=dw.height()*0.7;// idem
    this->setFixedSize(x,y);// rendre la taille de la fenetre inchangable
    connectionToDB(); // connexion a la base de données
    setBackgroundImage();// pour éviter des problemes de dimension de css

}

MYK_CAR::~MYK_CAR()
{
    db.close();// fermeture de la base de données
    delete ui;
}

void MYK_CAR::connectionToDB(){
   /* QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // 127.0.0.1
    db.setDatabaseName("myk");
    db.setUserName("root");
    db.setPassword("");*/

    // connexion a la base de données
    QString dbname="C:\\Users\\m.y.ihbach\\Desktop\\MYK_\\myk.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(db.open())
        qDebug() << "Well opened";

}

void MYK_CAR::setBackgroundImage(){
        QPixmap background(":/image/cars_image/jaguar_home.jpg");
        background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, background);
        this->setPalette(palette);
}



void MYK_CAR::on_pushButton_voitures_clicked()
{
    Voiture voiture;
    voiture.setModal(true);
    voiture.exec();
}

void MYK_CAR::on_pushButton_clients_clicked()
{
    Client client;
    client.setModal(true);
    client.exec();
}

void MYK_CAR::on_pushButton_maintenance_clicked()
{
    Maintenance maintenance;
    maintenance.setModal(true);
    maintenance.exec();
}

void MYK_CAR::on_pushButton_locations_clicked()
{
    Location location;
    location.setModal(true);
    location.exec();
}

void MYK_CAR::on_pushButton_clicked()
{
    Resultat resultat;
    resultat.setModal(true);
    resultat.exec();
}
