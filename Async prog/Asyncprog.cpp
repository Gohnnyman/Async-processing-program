#include "Asyncprog.h"
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
        throw std::logic_error("Can't open file");
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
    time_t time = clock();
    QDir dir("./files");
    QFileInfoList fileInfoList = dir.entryInfoList();
    size_t filesCount = htmlFilesCount(fileInfoList);
    std::unique_ptr<QPair <QString, std::future<size_t>> []> sizesList(new QPair<QString, std::future<size_t>>[filesCount]);
    
    size_t j = 0;
    for (const auto& fileInfo : fileInfoList)
    {
        if (fileInfo.suffix() == "html")
        {
            sizesList[j].first = fileInfo.fileName();
            sizesList[j].second = std::async(std::launch::async, sizeOfCurve, std::ref(fileInfo));
            j++;
        }
    }

    
    QString labelOfSizes;
    try
    {
        for (int i = 0; i < filesCount; i++)
        {
            labelOfSizes += sizesList[i].first + " : ";
            labelOfSizes += QString::number(sizesList[i].second.get());
            labelOfSizes += '\n';
        }
    }
    catch (const std::exception& err)
    {
        labelOfSizes = err.what();
    }
    
    labelOfSizes = QString::number(clock() - time) + '\n' + labelOfSizes;
    ui.statusBar->clearMessage();
    ui.ansLabel->setText(labelOfSizes);

}

void Asyncprog::on_startButton_pressed()
{
    ui.statusBar->showMessage("Loading . . .");
    ui.ansLabel->clear();
}

//+------------------------------------------------------------------+

void Asyncprog::on_debugButton_clicked()
{
    time_t time = clock();
    QDir dir("./files");
    QFileInfoList fileInfoList = dir.entryInfoList();
    size_t filesCount = htmlFilesCount(fileInfoList);
    QPair <QString, int>* sizesList = new QPair<QString, int>[filesCount];


    size_t j = 0;

    for (const auto& fileInfo : fileInfoList)
    {
        if (fileInfo.suffix() == "html")
        {
            sizesList[j].first = fileInfo.fileName();
            sizesList[j].second = sizeOfCurve(fileInfo);
            j++;
        }
    }




    QString labelOfSizes;
    for (int i = 0; i < filesCount; i++)
    {
        labelOfSizes += sizesList[i].first + " : ";
        labelOfSizes += QString::number(sizesList[i].second);
        labelOfSizes += '\n';
    }
    labelOfSizes = "DEBUG:\n" + QString::number(clock() - time) + '\n' + labelOfSizes;
    ui.statusBar->clearMessage();


    ui.ansLabel->setText(labelOfSizes);

    delete[] sizesList;
}

void debugsizeOfCurve(const QFileInfo& fileInfo, std::promise<size_t>& promise)
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

    promise.set_value(rowCount);
}

void Asyncprog::on_debugButton2_clicked()
{
    time_t time = clock();
    QDir dir("./files");
    QFileInfoList fileInfoList = dir.entryInfoList();
    size_t filesCount = htmlFilesCount(fileInfoList);

    std::promise<size_t>* p = new std::promise<size_t>[filesCount];
    QPair <QString, std::future<size_t>>* sizesList = new QPair<QString, std::future<size_t>>[filesCount];


    size_t j = 0;

    for (const auto& fileInfo : fileInfoList)
    {
        if (fileInfo.suffix() == "html")
        {
            sizesList[j].first = fileInfo.fileName();
            sizesList[j].second = p[j].get_future();
            j++;
        }
    }

    std::thread t1(debugsizeOfCurve, std::ref(fileInfoList[2]), std::ref(p[0]));
    std::thread t2(debugsizeOfCurve, std::ref(fileInfoList[3]), std::ref(p[1]));
    std::thread t3(debugsizeOfCurve, std::ref(fileInfoList[4]), std::ref(p[2]));
    std::thread t4(debugsizeOfCurve, std::ref(fileInfoList[5]), std::ref(p[3]));


    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();


    QString labelOfSizes;
    for (int i = 0; i < filesCount; i++)
    {
        labelOfSizes += sizesList[i].first + " : ";
        labelOfSizes += QString::number(sizesList[i].second.get());
        labelOfSizes += '\n';
    }
    labelOfSizes = QString::number(clock() - time) + '\n' + labelOfSizes;
    ui.statusBar->clearMessage();


    ui.ansLabel->setText(labelOfSizes);
    delete[] sizesList;
}