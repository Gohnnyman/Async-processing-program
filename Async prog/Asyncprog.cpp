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


Asyncprog::Asyncprog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
}



size_t sizeOfCurve(QFileInfo& fileInfo, QMessageBox& debug)
{
    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 1;
    }

    QTextStream in(&file);
    QString line;
    size_t rowCount = 0;

    size_t n = 0;
    while (!in.atEnd()) {
        in >> line;
        if (line == "</td>") rowCount++;
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

    QMessageBox m;
    QDir dir("./files");
    QFileInfoList fileInfoList = dir.entryInfoList();
    size_t filesCount = htmlFilesCount(fileInfoList);

    std::future<size_t>* listOfSizes = new std::future<size_t>[filesCount];
    
    

    size_t j = 0;
    for (auto fileInfo : fileInfoList)
    {
        if (fileInfo.suffix() == "html")
        {
            listOfSizes[j] = std::async(std::launch::async, sizeOfCurve, std::ref(fileInfoList[j]), std::ref(m));
            j++;
        }
    }

    QString tmp;

    for (size_t i = 0; i < filesCount; ++i)
    {
        tmp += QString::number(listOfSizes[i].get());
        tmp += '\n';
    }


    
    m.setText(tmp);
    m.exec();
}
