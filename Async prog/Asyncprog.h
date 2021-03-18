#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Asyncprog.h"

class Asyncprog : public QMainWindow
{
    Q_OBJECT

public:
    Asyncprog(QWidget *parent = Q_NULLPTR);

private:
    Ui::AsyncprogClass ui;
};
