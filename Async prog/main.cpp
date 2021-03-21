#include "Asyncprog.h"
#include <QtWidgets/QApplication>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.h"



TEST_CASE("Test Block 1") {
    REQUIRE(1 == 1);
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Asyncprog w;
    w.show();
    return a.exec();
}


