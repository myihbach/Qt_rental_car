#ifndef FORMMAINTENANCE_H
#define FORMMAINTENANCE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class formMaintenance;
}

class formMaintenance : public QDialog
{
    Q_OBJECT

public:
    explicit formMaintenance(QWidget *parent = nullptr);
    ~formMaintenance();
    Ui::formMaintenance * getUi();
    void setId(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::formMaintenance *ui;
    QString id;
};

#endif // FORMMAINTENANCE_H
