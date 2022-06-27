/********************************************************************************
** Form generated from reading UI file 'myclient.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLIENT_H
#define UI_MYCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myClient
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pbnConnect;
    QTextEdit *ted;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *myClient)
    {
        if (myClient->objectName().isEmpty())
            myClient->setObjectName(QString::fromUtf8("myClient"));
        myClient->resize(366, 348);
        centralwidget = new QWidget(myClient);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pbnConnect = new QPushButton(centralwidget);
        pbnConnect->setObjectName(QString::fromUtf8("pbnConnect"));

        verticalLayout->addWidget(pbnConnect);

        ted = new QTextEdit(centralwidget);
        ted->setObjectName(QString::fromUtf8("ted"));

        verticalLayout->addWidget(ted);

        myClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(myClient);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 366, 25));
        myClient->setMenuBar(menubar);
        statusbar = new QStatusBar(myClient);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        myClient->setStatusBar(statusbar);

        retranslateUi(myClient);

        QMetaObject::connectSlotsByName(myClient);
    } // setupUi

    void retranslateUi(QMainWindow *myClient)
    {
        myClient->setWindowTitle(QCoreApplication::translate("myClient", "myClient", nullptr));
        pbnConnect->setText(QCoreApplication::translate("myClient", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myClient: public Ui_myClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
