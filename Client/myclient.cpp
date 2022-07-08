#include "myclient.h"
#include "ui_myclient.h"
#include <QDebug>

myClient::myClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myClient)
{
    ui->setupUi(this);
    //connect(ui->pbnConnect,SIGNAL(clicked()),this,SLOT(connectingToServer()));
}

void myClient::writedata(QByteArray d)
{
    clientSocket->write(d);
}

QTcpSocket* myClient::getSocket()
{
    return clientSocket;
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
    QJsonDocument d = QJsonDocument::fromJson(data);
    QJsonObject all = d.object();
    emit recievemessage(all);
}

void myClient::writingData()
{
    qDebug()<<"writing successfully!\n";
}

void myClient::connectedToServer()
{
    qDebug()<<"connected Successfully!\n";
    emit connected();
    //clientSocket->write("Hello\n");
}

void myClient::disconnectedFromServer()
{
    qDebug()<<"connection lost\n";
}

QJsonObject myClient::getMsg()
{
    return msg;
}
