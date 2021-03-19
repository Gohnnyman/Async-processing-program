/********************************************************************************
** Form generated from reading UI file 'Asyncprog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASYNCPROG_H
#define UI_ASYNCPROG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsyncprogClass
{
public:
    QWidget *centralWidget;
    QPushButton *startButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AsyncprogClass)
    {
        if (AsyncprogClass->objectName().isEmpty())
            AsyncprogClass->setObjectName(QString::fromUtf8("AsyncprogClass"));
        AsyncprogClass->resize(582, 400);
        centralWidget = new QWidget(AsyncprogClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(210, 60, 131, 51));
        AsyncprogClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AsyncprogClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 582, 25));
        AsyncprogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AsyncprogClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AsyncprogClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AsyncprogClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AsyncprogClass->setStatusBar(statusBar);

        retranslateUi(AsyncprogClass);

        QMetaObject::connectSlotsByName(AsyncprogClass);
    } // setupUi

    void retranslateUi(QMainWindow *AsyncprogClass)
    {
        AsyncprogClass->setWindowTitle(QCoreApplication::translate("AsyncprogClass", "Asyncprog", nullptr));
        startButton->setText(QCoreApplication::translate("AsyncprogClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AsyncprogClass: public Ui_AsyncprogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASYNCPROG_H
