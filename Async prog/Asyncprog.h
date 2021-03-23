#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Asyncprog.h"
#include "toml11/toml.hpp"
#include <QMessageBox>
#include <Qdir>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QList>    
#include <future>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <stdexcept>
#include <chrono>
#include <time.h>
#include <memory>

class Asyncprog : public QMainWindow
{
    Q_OBJECT

public:
    Asyncprog(QWidget *parent = Q_NULLPTR);

private slots:
    void on_startButton_clicked();
    void on_debugButton_clicked();
    void on_startButton_pressed();

private:
    
    Ui::AsyncprogClass ui;
    toml::value data = toml::parse("inf.toml");
};
void startButtonProcessing(Ui::AsyncprogClass&, const QStringList&);
size_t sizeOfCurve(const QString&);
