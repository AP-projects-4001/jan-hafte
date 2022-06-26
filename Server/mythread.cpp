#include "mythread.h"
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

int checkValidUsername(QString username, QByteArray jsonDb)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"].toString() == username)
        {
            return 0;
        }
    }
    return 1;
}

void MyThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(Data);
    QJsonObject readData = doc.object();
    QString header = readData["header"].toString();
    if (header == "register")
    {
        QFile file("./user.json");
        if (!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "Error opening file";
        }
        QByteArray data = file.readAll();
        if (checkValidUsername(readData["username"].toString(), data) == 0)
        {
            socket->write("failed");
            return;
        }
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray jsonArr = jsonObj["users"].toArray();
        QJsonObject newUser;
        newUser["username"] = readData["username"].toString();
        newUser["password"] = readData["password"].toString();
        jsonArr.append(newUser);
        jsonObj["users"] = jsonArr;
        QJsonDocument newDoc(jsonObj);
        file.resize(0);
        file.write(newDoc.toJson());
        file.close();
        socket->write("success");
    }
    else if (header == "login")
    {
        QFile file("./user.json");
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Error opening file";
        }
        QByteArray data = file.readAll();
        if (checkValidUsername(readData["username"].toString(), data) == 1)
        {
            socket->write("not valid");
            return;
        }
        QJsonDocument mydoc = QJsonDocument::fromJson(data);
        QJsonObject myobj = mydoc.object();
        QJsonArray myarr = myobj["users"].toArray();
        for (int i = 0; i < myarr.size(); i++)
        {
            QJsonObject user = myarr[i].toObject();
            if (user["username"].toString() == readData["username"].toString() && user["password"].toString() == readData["password"].toString())
            {
                socket->write("success");
                return;
            }
        }
        socket->write("failed");
    }

    // will write on server side window
    qDebug() << socketDescriptor << " Data in: " << Data;

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
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
