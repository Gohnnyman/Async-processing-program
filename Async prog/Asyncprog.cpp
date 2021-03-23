#include "Asyncprog.h"



Asyncprog::Asyncprog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
}

size_t sizeOfCurve(const QString& filePath)
{
    
    QFile file(filePath);
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

void Asyncprog::on_startButton_clicked()
{   
    QString defaultDirectory = QString::fromStdString(toml::find<std::string>(data, "filePath"));
    QStringList pathsList = QFileDialog::getOpenFileNames(this, "Select HTML files",
        defaultDirectory, "HTML files (*.html)");
    std::thread th(startButtonProcessing, ui, pathsList);
    th.detach();
}

void Asyncprog::on_startButton_pressed()
{
    ui.statusBar->showMessage("Loading . . .");
    ui.ansLabel->clear();
}

void startButtonProcessing(Ui::AsyncprogClass& ui, const QStringList& pathsList)
{
    time_t time = clock();
    QString labelOfSizes;
    size_t filesCount = pathsList.size();
    std::unique_ptr<QPair <QString, std::future<size_t>>[]> 
        sizesList(new QPair<QString, std::future<size_t>>[filesCount]);

    size_t j = 0;
    for (const auto& path : pathsList)
    {
        sizesList[j].first = path.right(path.size() - path.lastIndexOf("/") - 1);
        sizesList[j].second = std::async(std::launch::async, sizeOfCurve, std::ref(path));
        j++;
    }

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

    labelOfSizes = "Time (milliseconds): " + QString::number(clock() - time) + '\n' 
        + labelOfSizes;
    ui.statusBar->clearMessage();
    ui.ansLabel->setText(labelOfSizes);
}




