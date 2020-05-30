#ifndef VOITURE_H
#define VOITURE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "formvoiture.h"
#include "ui_formvoiture.h"
#include <QItemSelectionModel>
#include "formupdatevoiture.h"


namespace Ui {
class Voiture;
}

class Voiture : public QDialog
{
    Q_OBJECT

public:
    explicit Voiture(QWidget *parent = nullptr);
    ~Voiture();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_ajouter_clicked();

    void on_pushButton_reserver_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();

private:
    Ui::Voiture *ui;
    QSqlQueryModel * voiture_dispo;
    QSqlQueryModel * voiture_reserv;
    void getModels();
    formVoiture *formAjoutVoiture;
    formUpdateVoiture *formUpdateVoi;
    void refreshDB();
};

#endif // VOITURE_H
