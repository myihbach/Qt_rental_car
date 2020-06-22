#ifndef RESULTAT_H
#define RESULTAT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QItemSelectionModel>

namespace Ui {
class Resultat;
}

class Resultat : public QDialog
{
    Q_OBJECT

public:
    explicit Resultat(QWidget *parent = nullptr);
    ~Resultat();

private:
    Ui::Resultat *ui;
    QSqlQueryModel * model;
};

#endif // RESULTAT_H
