#include "client_interface.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    //cream o aplicatie in Qt cu argumentele date
    QApplication a(argc, argv);
    //cream interfata necesara
    //client_interface este o clasa
    //pe care o putem edita
    Client_interface w;
    //afisam pe ecran interfata
    w.show();
    //asteptam ca aplicatia sa se inchida
    return a.exec();
}
