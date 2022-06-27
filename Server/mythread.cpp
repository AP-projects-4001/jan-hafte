#include "mythread.h"
#include "Server_readFunctions.h"
#include <QTimer>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QFile>

MyThread::MyThread(qintptr ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if (!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void MyThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(Data);
    QJsonObject readData = doc.object();
    QString header = readData["header"].toString();
    if (header == "register") // {header:register, \
		                          username: <username>, \
                                  password: <password>}
    {
        QByteArray response = register_user(readData);
        socket->write(response);
    }
    else if (header == "login") // {header:login, \
                                    username: <username> \
                                    password: <password>}
    {
        QByteArray response = login_user(readData);
        socket->write(response);
    }
    else if (header == "create_chat") // {header:create_chat, \
                                         chatType: <group/channel/private_chat>, \
                                         creator: <creator_username>, \
                                         participants: [participants_username]}
    {
        // read chatType from readData
        QString chatType = readData["chatType"].toString();
        QByteArray response = create_chat(readData, chatType);
    }
    else if (header == "search_user")
    { // {header:search_user,\
                                            searched_field: <input_field>}
        QByteArray response = search_user(readData);
        socket->write(response);
    }
}

// will write on server side window
// qDebug() << socketDescriptor << " Data in: " << Data;

// write to socket
// read file data from local
/*QFile file("C:/test.txt");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
QTextStream in(&file);
QString line = in.readLine();
while (!line.isNull()) {
    socket->write(line.toUtf8());
    line = in.readLine();
}*/

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
