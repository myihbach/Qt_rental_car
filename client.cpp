#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowTitle("Clients");
    model = new QSqlQueryModel();
    model->setQuery("select * from clients");
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Client::~Client()
{
    delete ui;
}
