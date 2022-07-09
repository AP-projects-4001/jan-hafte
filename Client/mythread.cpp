#include "mythread.h"
#include <QTimer>
#include <QFile>
#include <QDebug>

MyThread::MyThread(QString user_unique_id)
{
    this->user_unique_id = user_unique_id;
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 1234);

    if(socket->waitForConnected(-1)){
        while(true){

            QJsonObject d;
            d["header"]="get_continuous_data";
            d["username"]=user_unique_id;
            QJsonDocument all(d);
            socket->write(all.toJson());
            socket->waitForReadyRead(-1);
            QByteArray res = socket->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(res);
            QJsonObject obj = doc.object();
            emit recievemessage(obj);
            sleep(1);
        }
    }
    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    //connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    //connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    //qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void MyThread::readyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument d = QJsonDocument::fromJson(data);
    QJsonObject all = d.object();
    emit recievemessage(all);

}

void MyThread::disconnected()
{
    //qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
