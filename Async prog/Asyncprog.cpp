#include "Asyncprog.h"



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




