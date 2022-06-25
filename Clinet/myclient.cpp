#include "myclient.h"
#include "ui_myclient.h"

myClient::myClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myClient)
{
    ui->setupUi(this);
    connect(ui->pbnConnect,SIGNAL(clicked()),this,SLOT(connectingToServer()));
}

myClient::~myClient()
{
    delete ui;
}



void myClient::connectingToServer()
{
    ui->ted->setText("Start\n");
    clientSocket = new QTcpSocket;
    clientSocket->connectToHost("127.0.0.1",1234);
    ui->ted->setText("connecting...\n");

    connect(clientSocket,SIGNAL(connected()),this,SLOT(connectedToServer()));
    connect(clientSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(writingData()));
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(readingData()));
    connect(clientSocket,SIGNAL(disconnect()),this,SLOT(disconnectedFromServer()));

}


void myClient::readingData()
{
    QByteArray data = clientSocket->readAll();
    ui->ted->append(data);

}

void myClient::writingData()
{
    ui->ted->append("writing successfully!\n");
}

void myClient::connectedToServer()
{
    ui->ted->append("connected Successfully!\n");
    clientSocket->write("Hello\n");
}

void myClient::disconnectedFromServer()
{
    ui->ted->append("connection lost\n");
}
