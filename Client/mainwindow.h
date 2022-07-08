#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "messagebox.h"
#include "myclient.h"
#include "mythread.h"
#include "chatlable.h"
#include "createchatdialog.h"
#include "utilities.h"
#include "settingsdialog.h"
#include "graphview.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void gettingchat(QString chat_unique_id, QString chat_type);
    void createpv(QJsonArray participants_username);
    void creategroup(QJsonArray participants_username);
    void createchannel(QJsonArray participants_username);
    void searchuser(QString chat_unique_id, QString time);
    void changeusername(QString newdata);
    void changeemail(QString newdata);
    void changephone(QString newdata);
    void save_message(QString chat_unique_id, QString chat_type, QString message, QString time);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

    void on_createNewChatButton_clicked();

    void on_settingsButton_clicked();

    void on_showChatViewButton_clicked();

    void on_showGraphViewButton_clicked();

    void on_searchBar_textChanged(const QString &arg1);

    void getdata(QJsonObject data);

    void onChatLableClick(ChatLable *label);

private:
    Ui::MainWindow *ui;
    QString user_unique_id;
    myClient *e;
    QJsonObject all;

    QList <MessageBox*> listOfMessages;
    QList <ChatLable> listOfChats;

    chatData thisUser;
    chatData selectedChat;
    ChatLable *selectedChatLabel = nullptr;


    QString searchPattern;
};

#endif // MAINWINDOW_H
