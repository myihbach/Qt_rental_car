#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;
    QSqlQueryModel * model;
};

#endif // CLIENT_H
