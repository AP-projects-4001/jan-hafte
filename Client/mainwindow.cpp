#include "mainwindow.h"
#include "ui_createchatdialog.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent, QString username) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    selectedChat = new chatData;
    MyThread *thread = new MyThread(username, selectedChat);
    thread->start();
    e = new myClient();
    e->connectingToServer();
    connect(e, SIGNAL(recievemessage(QJsonObject)), this, SLOT(getdata(QJsonObject)));
    connect(thread, SIGNAL(recievemessage(QJsonObject)), this, SLOT(getdata(QJsonObject)));
    //connect(e, SIGNAL(connected(QString)) , this, SLOT(connectedToServer(QString)));


    createChatDialog = new CreateChatDialog(this);
    createChatDialog->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    connect(createChatDialog->ui->contactInfoInput, SIGNAL(textChanged(QString)), this, SLOT(on_contactInfoInput_textChanged(const QString&)));
    connect(createChatDialog->ui->MessageContactButton, SIGNAL(clicked()), this, SLOT(on_MessageContactButton_clicked()));


    settingsDialog = new SettingsDialog(this);
    settingsDialog->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);

    /*
    for(int i = 0; i < 5; i++) {
        ChatLable *label = new ChatLable(ui->chatListAreaContentSlot, true, true);
        connect(label, SIGNAL(click(ChatLable*)), this, SLOT(onChatLableClick(ChatLable*)));
    }*/

    GraphView *graphView = new GraphView(ui->graphViewArea);
    ui->graphViewArea->layout()->addWidget(graphView);


    ui->chatLineEdit->clear();
    ui->topInfoBarArea->hide();
    ui->chatViewTypeArea->hide();

    getThisUserInfo(username);
}

void MainWindow::getdata(QJsonObject data)
{
    //qDebug() << "ASdDoneDone";

    if (data["header"]=="get_continuous_data"){

        qDeleteAll(listOfChats.begin(), listOfChats.end());
        listOfChats.clear();
        QJsonArray chats =  data["chats"].toArray();
        chatData tempData;
        for (int i = 0; i < chats.size(); i++) {

            tempData.id = chats[i].toObject()["id"].toString();
            tempData.creator = chats[i].toObject()["creator"].toString();
            tempData.reciever = chats[i].toObject()["reciever"].toString();
            tempData.name = chats[i].toObject()["name"].toString();
            tempData.type = chats[i].toObject()["chat_type"].toString();
            tempData.profile = Utilities::stringToImage(chats[i].toObject()["profile"].toString());
            tempData.phoneNumber = chats[i].toObject()["phone"].toString();
            tempData.lastMessage = chats[i].toObject()["last_message"].toString();
            tempData.lastMessageTime = QDateTime::fromString(chats[i].toObject()["last_message_time"].toString());

            qDebug() << tempData.profile;

            ChatLable *chat = new ChatLable (ui->chatListAreaContentSlot, true, true, tempData);
            connect(chat, SIGNAL(click(ChatLable*)), this, SLOT(onChatLableClick(ChatLable*)));
            if(tempData.id == selectedChat->id && anyChatIsActive) chat->setChecked(true);
            listOfChats.append(chat);
        }

        qDeleteAll(listOfMessages.begin(), listOfMessages.end());
        listOfMessages.clear();
        QJsonArray messages = data["messages"].toArray();
        for (int i =0; i < messages.size(); i++) {
            QString text = messages[i].toObject()["message_text"].toString();
            QString sender = messages[i].toObject()["sender"].toString();
            bool isSender = (sender == thisUser.username);
            QDateTime time = QDateTime::fromString(messages[i].toObject()["time"].toString());
            MessageBox *message = new MessageBox(ui->chatViewScrollAreaContent, isSender, text);
            listOfMessages.append(message);
        }

    }

    else if (data["header"] == "get_this_user") {
        QString status = data["status"].toString();
        if (status == "valid") {
            qDebug() << "DoneDone";
            thisUser.username = data["username"].toString();
            thisUser.phoneNumber = data["phone"].toString();
            thisUser.emailAddress = data["email"].toString();
            thisUser.profile = Utilities::stringToImage(data["profile"].toString());
            thisUser.name = data["name"].toString();
        }
        else if (status == "not valid"){

        }
        else{

        }
    }
    else if (data["header"]=="get_messages"){

    }

    else if (data["header"]=="create_chat"){

        QString status = data["status"].toString();
        if (status == "valid") {

        }
        else if (status == "not valid"){

        }
        else{

        }
    }

    else if(data["header"]=="search_chat"){

    }

    else if (data["header"]=="search_user") {

        if (data["status"].toString() == "valid") {
            chatData recievedUser;
            recievedUser.username = data["username"].toString();
            recievedUser.phoneNumber = data["phone"].toString();
            recievedUser.name = data["name"].toString();
            recievedUser.profile = Utilities::stringToImage(data["profile"].toString());

            foundUserLable = new ChatLable(createChatDialog->ui->contactPage, false, false, recievedUser);
            createChatDialog->ui->contactPageUserSlot->addWidget(foundUserLable);

        } else if (data["status"].toString() == "not valid"){
            qDebug() << "PaAaaa";
        } else {
            qDebug() << "Naaaaaa";
        }
    }

    else if(data["header"]=="change_data"){

    }

    else if(data["header"]=="save_message"){
        QString status = data["status"].toString();
        if (status == "valid") {
            qDebug()<<"saved";
            ui->chatViewScrollArea->verticalScrollBar()->setValue(ui->chatViewScrollArea->verticalScrollBar()->maximum());
        }
        else if (status == "not valid"){

        }
        else{

        }
    }
}

void MainWindow::onChatLableClick(ChatLable *label)
{
    if(!anyChatIsActive) {
        ui->topInfoBarArea->show();
        ui->chatViewTypeArea->show();
        anyChatIsActive = true;
    } else {
        if(selectedChatLabel != nullptr) {
            selectedChatLabel->setChecked(false);
        }
        label->setChecked(true);
    }
        *selectedChat = label->getData();
}

void MainWindow::on_contactInfoInput_textChanged(const QString &arg1)
{
    if(foundUserLable != nullptr) {
        delete foundUserLable;
        foundUserLable = nullptr;
    }
    searchUser(arg1);
}

void MainWindow::on_MessageContactButton_clicked()
{
    QString inputUsername = createChatDialog->ui->contactInfoInput->text();
    QJsonArray participants;
    participants.append(QJsonValue(inputUsername));
    createpv(participants);
}

void MainWindow::connectedToServer(QString temp_id)
{

}

void MainWindow::updateChatList()
{

}

void MainWindow::updateMessageList()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButton_clicked()
{
    QString inpMessage = ui->chatLineEdit->toPlainText().trimmed();
    ui->chatLineEdit->clear();
    if(inpMessage.isEmpty()) return;

    QDateTime time = QDateTime::currentDateTimeUtc();

    MessageBox *message = new MessageBox(ui->chatViewScrollAreaContent, true, inpMessage, time);
    listOfMessages.append(message);

    ui->chatViewScrollArea->verticalScrollBar()->setValue(ui->chatViewScrollArea->verticalScrollBar()->maximum());
    save_message(selectedChat->id, selectedChat->type, inpMessage, time.toString());
}

void MainWindow::getThisUserInfo(QString user_unique_id)
{
    QJsonObject o;
    o["header"]= "get_this_user";
    o["username"] = user_unique_id;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::gettingchat(QString chat_unique_id, QString chat_type)
{
    QJsonObject o;
    o["header"]="get_messages";
    o["chat_type"] = chat_type;
    o["username"]= thisUser.username;
    o["chat_id"]=chat_unique_id;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::createpv(QJsonArray participants_username)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "private_chat";
    o["creator"]=thisUser.username;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::creategroup(QJsonArray participants_username)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "group";
    o["creator"]=thisUser.username;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::createchannel(QJsonArray participants_username)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "channel";
    o["creator"]=thisUser.username;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::searchChat(QString chat_unique_id)
{
    QJsonObject o;
    o["header"]="search_chat";
    o["chat_id"] = chat_unique_id;
    o["sender"] = thisUser.username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::searchUser(QString user_unique_id)
{
    QJsonObject o;
    o["header"]="search_user";
    o["searched_field"] = user_unique_id;
    o["sender"] = thisUser.username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::changeusername(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=thisUser.username;
    o["key"]="username";
    o["value"]=newdata;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::changeemail(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=thisUser.username;
    o["key"]="email";
    o["value"]=newdata;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::changephone(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=thisUser.username;
    o["key"]="phone";
    o["value"]=newdata;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::save_message(QString chat_unique_id, QString chat_type, QString message, QString time)
{
    //qDebug() <<
    QJsonObject o;
    o["header"]="save_message";
    o["chat_id"] = chat_unique_id;
    o["sender"] = thisUser.username;
    o["message_text"] = message;
    o["time"] = time;
    o["chat_type"]=chat_type;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::on_createNewChatButton_clicked()
{
    createChatDialog->exec();
}

void MainWindow::on_settingsButton_clicked()
{
    //getThisUserInfo("Yasin");
    settingsDialog->setUpData(thisUser.name, thisUser.emailAddress, thisUser.phoneNumber, thisUser.profile);
    settingsDialog->show();
}

void MainWindow::on_showChatViewButton_clicked()
{
    ui->showChatViewButton->setChecked(true);
    ui->showGraphViewButton->setChecked(false);
    ui->activeSectionPages->setCurrentIndex(0);
    ui->listViewPages->setCurrentIndex(0);
}

void MainWindow::on_showGraphViewButton_clicked()
{
    ui->showChatViewButton->setChecked(false);
    ui->showGraphViewButton->setChecked(true);
    ui->activeSectionPages->setCurrentIndex(1);
    ui->listViewPages->setCurrentIndex(1);
}

void MainWindow::on_searchBar_textChanged(const QString &arg1)
{

}

