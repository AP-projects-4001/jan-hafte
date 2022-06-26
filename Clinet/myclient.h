#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

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
    ~myClient();

public slots:
    void connectingToServer();
    QByteArray readingData();
    void writingData();
    void connectedToServer();
    void disconnectedFromServer();

private:
    Ui::myClient *ui;
    QTcpSocket *clientSocket;
};
#endif // MYCLIENT_H
