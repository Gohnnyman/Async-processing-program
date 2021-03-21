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
#include <QDebug>
#include <stdexcept>


Asyncprog::Asyncprog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
}



size_t sizeOfCurve(const QFileInfo& fileInfo)
{
    
    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw std::logic_error("File didn't open");
    }

    QTextStream in(&file);
    QString line;
    size_t rowCount = 0;


    size_t n = 0;
    while (!in.atEnd()) {
        line = in.readLine();
        if (line.indexOf("<tr>") != -1) rowCount++;
    }

    return rowCount;
}


size_t htmlFilesCount(const QFileInfoList& fileInfoList)
{
    size_t filesCount = 0;
    for (const auto& fileInfo : fileInfoList)
    {
        if (fileInfo.suffix() == "html") filesCount++;
    }

    return filesCount;
}

void Asyncprog::on_startButton_clicked()
{       
    QDir dir("./files");
    QFileInfoList fileInfoList = dir.entryInfoList();
    size_t filesCount = htmlFilesCount(fileInfoList);
    std::future<size_t>* sizesList = new std::future<size_t>[filesCount];
    

    size_t j = 0;

    for (auto& fileInfo : fileInfoList)
    {
        if (fileInfo.suffix() == "html")
        {
            sizesList[j] = std::async(std::launch::async, sizeOfCurve, std::ref(fileInfo));
            j++;
        }
    }


    QMessageBox debug;
    QString labelOfSizes;
    for (int i = 0; i < filesCount; i++)
    {
        labelOfSizes += QString::number(sizesList[i].get());
        labelOfSizes += '\n';
    }

    debug.setText(labelOfSizes);
    debug.exec();
}
