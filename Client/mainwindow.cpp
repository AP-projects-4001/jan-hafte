#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString inpMessage = ui->chatLineEdit->toPlainText().trimmed();
    ui->chatLineEdit->clear();
    if(inpMessage.isEmpty()) return;
    MessageBox *message = new MessageBox(ui->chatViewScrollAreaContent);
    message->setText(inpMessage);
    listOfMessages.append(message);

}

