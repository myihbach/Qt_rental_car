#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>

namespace Ui {
class Maintenance;
}

class Maintenance : public QDialog
{
    Q_OBJECT

public:
    explicit Maintenance(QWidget *parent = nullptr);
    ~Maintenance();

private:
    Ui::Maintenance *ui;
    QSqlQueryModel * model;

};

#endif // MAINTENANCE_H
