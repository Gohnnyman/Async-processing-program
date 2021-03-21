#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Asyncprog.h"

class Asyncprog : public QMainWindow
{
    Q_OBJECT

public:
    Asyncprog(QWidget *parent = Q_NULLPTR);

private slots:
    void on_startButton_clicked();
    void on_debugButton_clicked();
    void on_debugButton2_clicked();
    void on_startButton_pressed();

private:
    Ui::AsyncprogClass ui;
};
