#include "myk_car.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MYK_CAR w;
    w.show();
    return a.exec();
}
