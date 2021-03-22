#include "Asyncprog.h"


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

