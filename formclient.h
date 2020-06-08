#ifndef FORMCLIENT_H
#define FORMCLIENT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class formClient;
}

class formClient : public QDialog
{
    Q_OBJECT

public:
    explicit formClient(QWidget *parent = nullptr);
    ~formClient();
    Ui::formClient * getUi();
    void setId(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::formClient *ui;
    QString id;
};

#endif // FORMCLIENT_H
