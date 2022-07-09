#include "mainwindow.h"
#include "ui_createchatdialog.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, QString username) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyThread *thread = new MyThread(username);
    //thread->start();
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
    qDebug() << "ASdDoneDone";

    if (data["header"]=="get_continuous_data"){
        qDebug() << "Ooomad";

        qDeleteAll(listOfChats.begin(), listOfChats.end());
        listOfChats.clear();
        QJsonArray chats =  data["chats"].toArray();
        chatData tempData;
        for (int i = 0; i < chats.size(); i++) {
            tempData.id = chats[i].toObject()["name"].toString();
            tempData.name = chats[i].toObject()["name"].toString();
            tempData.creator = chats[i].toObject()["creator"].toString();
            tempData.lastMessage = chats[i].toObject()["last_message"].toString();
            tempData.lastMessageTime = QDateTime::fromString(chats[i].toObject()["last_message_time"].toString());
            ChatLable *chat = new ChatLable (ui->chatViewScrollAreaContent, true, true, tempData);
            connect(chat, SIGNAL(click(ChatLable*)), this, SLOT(onChatLableClick(ChatLable*)));
            listOfChats.append(chat);
        }

        QJsonArray messages = data["messages"].toArray();
        for (int i =0; i < messages.size(); i++) {

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

            qDebug() << "HSdfaAaaa";

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
        }
        else if (status == "not valid"){

        }
        else{

        }
    }
}

void MainWindow::onChatLableClick(ChatLable *label)
{
    if(selectedChatLabel != nullptr) {
        selectedChatLabel->setChecked(false);
    } else {
        ui->topInfoBarArea->show();
        ui->chatViewTypeArea->show();
    }

    selectedChatLabel = label;
    selectedChat = label->getData();
    label->setChecked(true);
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

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButton_clicked()
{
    QString inpMessage = ui->chatLineEdit->toPlainText().trimmed();
    ui->chatLineEdit->clear();
    if(inpMessage.isEmpty()) return;
    MessageBox *message = new MessageBox(ui->chatViewScrollAreaContent);
    message->setText(inpMessage);
    listOfMessages.append(message);
    MessageBox *answer = new MessageBox (ui->chatViewScrollAreaContent, false);
    answer->setText("This is A random answer");
    listOfMessages.append(answer);

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

