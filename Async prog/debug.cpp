#include "Asyncprog.h"


void Asyncprog::on_debugButton_clicked()
{
    QStringList pathsList = QFileDialog::getOpenFileNames(this, "Select HTML files (DEBUG)",
        "./files", "HTML files (*.html)");

    time_t time = clock();
    QString labelOfSizes;
    size_t filesCount = pathsList.size();
    std::unique_ptr<QPair <QString, size_t>[]>
        sizesList(new QPair<QString, size_t>[filesCount]);

    size_t j = 0;
    for (const auto& path : pathsList)
    {
        sizesList[j].first = path.right(path.size() - path.lastIndexOf("/") - 1);
        sizesList[j].second = sizeOfCurve(path);
        j++;
    }

    try
    {
        for (int i = 0; i < filesCount; i++)
        {
            labelOfSizes += sizesList[i].first + " : ";
            labelOfSizes += QString::number(sizesList[i].second);
            labelOfSizes += '\n';
        }
    }
    catch (const std::exception& err)
    {
        labelOfSizes = err.what();
    }

    labelOfSizes = "Time (milliseconds): " + QString::number(clock() - time) + '\n'
        + labelOfSizes;
    ui.statusBar->clearMessage();
    ui.ansLabel->setText(labelOfSizes);
}

