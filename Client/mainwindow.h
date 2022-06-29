#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "messagebox.h"
#include <QList>
#include "myclient.h"
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void getdata();
    void gettingchat();
    void createpv();
    void creategroup();
    void createchannel();
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;
    QString chat_type;
    QString user_unique_id;
    QString chat_unique_id;
    QJsonArray participants_username;
    myClient e;
    QString user_id;
    QJsonObject all;
    QList <MessageBox*> listOfMessages;
};

#endif // MAINWINDOW_H
