#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMessageBox>
#include "messagebox.h"
#include "myclient.h"
#include "mythread.h"
#include "chatlable.h"
#include "createchatdialog.h"

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

    void on_createNewChatButton_clicked();

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
    QList <ChatLable> listOfChats;
};

#endif // MAINWINDOW_H
