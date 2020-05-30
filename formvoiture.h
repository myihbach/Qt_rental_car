#ifndef FORMVOITURE_H
#define FORMVOITURE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class formVoiture;
}

class formVoiture : public QDialog
{
    Q_OBJECT

public:
    explicit formVoiture(QWidget *parent = nullptr);
    ~formVoiture();
    Ui::formVoiture * getUi();

private slots:
    void on_pushButton_ajouter_clicked();

//signals :
//    void refreshDBSignal(QString msg);

private:
    Ui::formVoiture *ui;
    QSqlQueryModel *categories;
    QSqlQueryModel *marques;
    void getCategoriesAndMarques();
};

#endif // FORMVOITURE_H
