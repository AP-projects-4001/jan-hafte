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

MyThread::MyThread(qintptr ID, QObject* parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }


    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " Client connected";

    exec();
}

void MyThread::readyRead()
{

    QFile msgFile("./messages.json");
    QFile usrFile("./users.json");
    QFile chtFile("./chats.json");
    if (msgFile.size() < 7)
    {
        QJsonObject obj;
        msgFile.open(QIODevice::WriteOnly);
        obj["messages"] = QJsonArray();
        QJsonDocument doc(obj);
        msgFile.write(doc.toJson());
        msgFile.close();
    }
    if (usrFile.size() < 7)
    {
        QJsonObject obj;
        usrFile.open(QIODevice::WriteOnly);
        obj["users"] = QJsonArray();
        QJsonDocument doc(obj);
        usrFile.write(doc.toJson());
        usrFile.close();
    }
    if (chtFile.size() < 7)
    {
        QJsonObject obj, channel, group, private_chat;
        channel["channel_chat"] = QJsonArray();
        group["group_chat"] = QJsonArray();
        private_chat["private_chat"] = QJsonArray();
        QJsonArray chatArray;
        chatArray.append(channel);
        chatArray.append(group);
        chatArray.append(private_chat);
        chtFile.open(QIODevice::WriteOnly);
        obj["chats"] = chatArray;
        QJsonDocument doc(obj);
        chtFile.write(doc.toJson());
        chtFile.close();
    }

    // get the information
    QByteArray Data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(Data);
    QJsonObject readData = doc.object();
    QString header = readData["header"].toString();
    if (header == "register") // {header:register, \
                                  username: <username>, \
                                  password: <password>} \
                                  phone: <phone> \
                                  birthday: <birthday> \
                                  email: <email> \
                                  }
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
                                         chatType: <group_chat/channel_chat/private_chat>, \
                                         creator: <creator_username>, \
                                         participants: QJsonArray(QStrings)}
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
    else if (header == "save_message")
    { // {header: save_message, \
                                             chat_id: <chat_id>, \
                                             sender: <sender_username>, \
                                             message_text: <message>  \
                                             time: <time> \
                                             chat_type: <chat_type>}
        QByteArray response = save_message(readData);
        socket->write(response);
    }
    else if (header == "get_messages")
    { // {header: get_message, \\
                                            chat_id: <chat_id>, \
                                            chat_type: <chat_type>}
        QByteArray response = get_messages(readData);
        socket->write(response);
    }
    else if (header == "get_continuous_data") { // {header:get_user_chat, \
                                          username: <username>}, \
    }
        QJsonObject response = get_user_chats(readData["username"].toString());
        QJsonDocument doc(response);
        QByteArray response_bytes = doc.toJson();
        socket->write(response_bytes);
    }
    else if (header == "change_data") { // {header:"change_data" \
                                            old_username: <oldUsername> \
                                            key: username/email/phone \
                                            value: <new_value> }
        QByteArray response = change_data(readData);
        socket->write(response);
    }
    else if (header == "get_this_user") {
        QByteArray response = get_this_user(readData);
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
