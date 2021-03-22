#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Asyncprog.h"
#include <QMessageBox>
#include <Qdir>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QList>    
#include <future>
#include <QTextStream>
#include <QDebug>
#include <QPair>
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
};

size_t htmlFilesCount(const QFileInfoList&);
size_t sizeOfCurve(const QFileInfo&);