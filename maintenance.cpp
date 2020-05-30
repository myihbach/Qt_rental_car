#include "maintenance.h"
#include "ui_maintenance.h"

Maintenance::Maintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Maintenance)
{
    ui->setupUi(this);
    this->setWindowTitle("Maintenances");

}

Maintenance::~Maintenance()
{
    delete ui;
}
