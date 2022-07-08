#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class myClient; }
QT_END_NAMESPACE

class myClient : public QMainWindow
{
    Q_OBJECT

public:
    myClient(QWidget *parent = nullptr);
    void writedata(QByteArray d);
    QTcpSocket* getSocket();
    QJsonObject getMsg();
    ~myClient();

signals:
    void recievemessage(QJsonObject);
    void connected();

public slots:
    void connectingToServer();
    void readingData();
    void writingData();
    void connectedToServer();
    void disconnectedFromServer();

private:
    Ui::myClient *ui;
    QTcpSocket *clientSocket;
    QJsonObject msg;
};
#endif // MYCLIENT_H
