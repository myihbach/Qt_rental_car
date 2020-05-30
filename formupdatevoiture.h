#ifndef FORMUPDATEVOITURE_H
#define FORMUPDATEVOITURE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class formUpdateVoiture;
}

class formUpdateVoiture : public QDialog
{
    Q_OBJECT

public:
    explicit formUpdateVoiture(QWidget *parent = nullptr);
    ~formUpdateVoiture();
    Ui::formUpdateVoiture * getUi();

signals :
    void refreshDBSignal(QString msg);

private slots:
    void on_pushButton_modifier_clicked();
    void refreshDBSlot();

private:
    Ui::formUpdateVoiture *ui;
    QSqlQueryModel *categories;
    QSqlQueryModel *marques;
    void getCategoriesAndMarques();
};

#endif // FORMUPDATEVOITURE_H
