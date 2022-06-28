#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    messageTest = new MessageBox[20];

    for (int i = 0; i < 20 ; i++) {
        messageTest[i].setParent(ui->chatViewScrollAreaContent);
        ui->chatViewScrollAreaContent->layout()->addWidget(&messageTest[i]);
    }

}

MainWindow::~MainWindow()
{
    delete[] messageTest;
    delete ui;
}
