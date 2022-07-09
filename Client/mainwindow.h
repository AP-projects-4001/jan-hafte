#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include "messagebox.h"
#include "myclient.h"
#include "mythread.h"
#include "chatlable.h"
#include "createchatdialog.h"
#include "utilities.h"
#include "settingsdialog.h"
#include "graphview.h"
#include <QScrollBar>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, QString username = "");
    void getThisUserInfo(QString user_unique_id);
    void gettingchat(QString chat_unique_id, QString chat_type);
    void createpv(QJsonArray participants_username);
    void creategroup(QJsonArray participants_username, const QString& name, const QString& profile);
    void createchannel(QJsonArray participants_username);
    void searchChat(QString chat_unique_id);
    void searchUser(QString user_unique_id);
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

    void on_contactInfoInput_textChanged(const QString &arg1);

    void on_MessageContactButton_clicked();

    void on_createGroupButton_clicked();

    void on_createChannelButton_clicked();

    void connectedToServer(QString temp_id);

private:
    Ui::MainWindow *ui;
    //QString user_unique_id;
    myClient *e;
    QJsonObject all;

    CreateChatDialog *createChatDialog;
    SettingsDialog *settingsDialog;

    QList <MessageBox*> listOfMessages;
    QList <ChatLable*> listOfChats, groupUsersSelection, channelUsersSelection;

    chatData thisUser, *selectedChat;
    bool anyChatIsActive = false;
    ChatLable *selectedChatLabel = nullptr;

    ChatLable *foundUserLable = nullptr;

    QString searchPattern;

    void updateChatList();
    void updateMessageList();
};

#endif // MAINWINDOW_H
