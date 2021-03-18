#include "Asyncprog.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Asyncprog w;
    w.show();
    return a.exec();
}
