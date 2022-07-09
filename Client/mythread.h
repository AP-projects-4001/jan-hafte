#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include "chatData.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QString user_unique_id, chatData* selectedChat);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void recievemessage(QJsonObject);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    QString user_unique_id;
    chatData *activeChat;
};

#endif // MYTHREAD_H
