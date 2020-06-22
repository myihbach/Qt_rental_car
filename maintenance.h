#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>

namespace Ui {
class Maintenance;
}

class Maintenance : public QDialog
{
    Q_OBJECT

public:
    explicit Maintenance(QWidget *parent = nullptr);
    ~Maintenance();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

private:
    Ui::Maintenance *ui;
    QSqlQueryModel * model;
    void getModel();
};

#endif // MAINTENANCE_H
