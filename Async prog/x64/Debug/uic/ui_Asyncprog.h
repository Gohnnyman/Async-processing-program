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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsyncprogClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AsyncprogClass)
    {
        if (AsyncprogClass->objectName().isEmpty())
            AsyncprogClass->setObjectName(QString::fromUtf8("AsyncprogClass"));
        AsyncprogClass->resize(600, 400);
        menuBar = new QMenuBar(AsyncprogClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AsyncprogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AsyncprogClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AsyncprogClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AsyncprogClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AsyncprogClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AsyncprogClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AsyncprogClass->setStatusBar(statusBar);

        retranslateUi(AsyncprogClass);

        QMetaObject::connectSlotsByName(AsyncprogClass);
    } // setupUi

    void retranslateUi(QMainWindow *AsyncprogClass)
    {
        AsyncprogClass->setWindowTitle(QCoreApplication::translate("AsyncprogClass", "Asyncprog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AsyncprogClass: public Ui_AsyncprogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASYNCPROG_H
