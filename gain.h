#ifndef GAIN_H
#define GAIN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class Gain;
}

class Gain : public QDialog
{
    Q_OBJECT

public:
    explicit Gain(QWidget *parent = nullptr);
    ~Gain();

private:
    Ui::Gain *ui;
    QSqlQueryModel * charge;
    QSqlQueryModel * produit;
    void getModels();
    void getTotal();
    int resultats;


};

#endif // GAIN_H
