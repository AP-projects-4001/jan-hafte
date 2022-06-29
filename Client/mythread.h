#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread();

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void recievemassage(QJsonObject);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // MYTHREAD_H
