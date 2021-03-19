#include "Asyncprog.h"
#include <QMessageBox>
#include <Qdir>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QList>    
#include <thread>
#include <future>
#include <QTextStream>
#include <fstream>


Asyncprog::Asyncprog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}



int sizeOfCurve(QFileInfo& fileInfo, QMessageBox& debug)
{
    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 1;
    }

    QTextStream in(&file);
    QString line;
    size_t rowCount = 0;

    while (!in.atEnd()) {
        in >> line;
        if (line == "<td>") rowCount++;
    }

    return rowCount;

}


void Asyncprog::on_startButton_clicked()
{
    
}
