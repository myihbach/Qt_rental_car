#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

private:
    Ui::Client *ui;
    QSqlQueryModel * model;
    void getModels();
};

#endif // CLIENT_H
