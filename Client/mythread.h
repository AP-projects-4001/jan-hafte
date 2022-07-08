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
    explicit MyThread(QString user_unique_id);

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
};

#endif // MYTHREAD_H
