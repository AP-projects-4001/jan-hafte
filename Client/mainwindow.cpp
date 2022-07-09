#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_createchatdialog.h"

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
    connect(createChatDialog->ui->createGroupButton, SIGNAL(clicked()), this, SLOT(on_createGroupButton_clicked()));


    settingsDialog = new SettingsDialog(this);
    settingsDialog->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    connect (settingsDialog, SIGNAL(userNameChangeRequest(QString)),this, SLOT(onUsernameChangeRequest(QString)));
    connect (settingsDialog, SIGNAL(emailChangeRequest(QString)),this, SLOT(onEmailChangeRequest(QString)));
    connect (settingsDialog, SIGNAL(phoneChangeRequest(QString)),this, SLOT(onPhoneChangeRequest(QString)));
    connect (settingsDialog, SIGNAL(profileChangeRequest(QString)),this, SLOT(onProfileChangeRequest(QString)));


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
    if (data["header"]=="get_all_users"){

    }

    else if (data["header"]=="get_continuous_data"){

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
            ChatLable *chat = new ChatLable (ui->chatListAreaContentSlot, true, true, tempData);
            connect(chat, SIGNAL(click(ChatLable*)), this, SLOT(onChatLableClick(ChatLable*)));
            if(tempData.id == selectedChat->id && anyChatIsActive) chat->setChecked(true);
            listOfChats.append(chat);
        }

        qDeleteAll(listOfMessages.begin(), listOfMessages.end());
        listOfMessages.clear();
        QJsonArray messages = data["messages"].toArray();
        for (int i = 0; i < messages.size(); i++) {
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
            qDebug() << "Getting User";
            thisUser.username = data["username"].toString();
            thisUser.phoneNumber = data["phone"].toString();
            thisUser.emailAddress = data["email"].toString();
            thisUser.profile = Utilities::stringToImage(data["profile"].toString());
            thisUser.name = data["name"].toString();
            settingsDialog->setUpData(thisUser.name, thisUser.emailAddress, thisUser.phoneNumber, thisUser.profile);
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
        QString status = data["status"].toString();
        if(status == "valid") {
            getThisUserInfo(thisUser.username);
        } else if (status == "not valid") {

        } else {

        }
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
        ui->activeChatProfile->setPixmap(Utilities::maskImage(label->getData().profile));
        ui->activeChatName->setText(label->getData().name);
        ui->activeChatDetail->setText(label->getData().phoneNumber);
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

void MainWindow::on_createGroupButton_clicked()
{
    QJsonArray participants;
    for(int i =0; i < groupUsersSelection.size(); i++) {
        if(groupUsersSelection[i]->getChecked()) {
            QString username;
            if(groupUsersSelection[i]->getData().creator == thisUser.username) {
                if(groupUsersSelection[i]->getData().reciever != thisUser.username) {
                    username = groupUsersSelection[i]->getData().reciever;
                    participants.append(QJsonValue(username));
                }
            } else if (groupUsersSelection[i]->getData().reciever == thisUser.username) {
                username = groupUsersSelection[i]->getData().creator;
                participants.append(QJsonValue(username));
            } else {

            }
        }
    }

    QString name = createChatDialog->ui->groupNameInput->text();
    creategroup(participants, name, Utilities::imageToString(Utilities::createPixBasedOnName(name)));
}

void MainWindow::on_createChannelButton_clicked()
{
    QJsonArray participants;
    for(int i =0; i < channelUsersSelection.size(); i++) {
        if(channelUsersSelection[i]->getChecked()) {
            QString username;
            if(channelUsersSelection[i]->getData().creator == thisUser.username) {
                if(channelUsersSelection[i]->getData().reciever != thisUser.username) {
                    username = channelUsersSelection[i]->getData().reciever;
                    participants.append(QJsonValue(username));
                }
            } else if (channelUsersSelection[i]->getData().reciever == thisUser.username) {
                username = channelUsersSelection[i]->getData().creator;
                participants.append(QJsonValue(username));
            } else {

            }
        }
    }
    QString name = createChatDialog->ui->channelNameInput->text();
    creategroup(participants, name, Utilities::imageToString(Utilities::createPixBasedOnName(name)));
}

void MainWindow::connectedToServer(QString temp_id)
{

}

void MainWindow::onUsernameChangeRequest(QString newUsername)
{
    changeusername(newUsername);
}

void MainWindow::onEmailChangeRequest(QString newEmail)
{
    changeemail(newEmail);
}

void MainWindow::onPhoneChangeRequest(QString newPhone)
{
    changephone(newPhone);
}

void MainWindow::onProfileChangeRequest(QString newProfile)
{
    changeprofile(newProfile);
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

void MainWindow::creategroup(QJsonArray participants_username, const QString& name, const QString& profile)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "group_chat";
    o["creator"] = thisUser.username;
    o["name"] = name;
    o["profile"] = profile;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::createchannel(QJsonArray participants_username, const QString& name, const QString& profile)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "channel_chat";
    o["creator"]=thisUser.username;
    o["name"] = name;
    o["profile"] = profile;
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
    o["key"]="name";
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

void MainWindow::changeprofile(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=thisUser.username;
    o["key"]="profile";
    o["value"]=newdata;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::getallusers()
{
    QJsonObject o;
    o["header"]="get_all_users";
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

void MainWindow::clearCreateChatWindow()
{
    qDeleteAll(groupUsersSelection);
    qDeleteAll(channelUsersSelection);
    groupUsersSelection.clear();
    channelUsersSelection.clear();
    if(foundUserLable != nullptr) {
        delete foundUserLable;
        foundUserLable = nullptr;
    }
    createChatDialog->ui->channelNameInput->clear();
    createChatDialog->ui->groupNameInput->clear();
    createChatDialog->ui->contactInfoInput->clear();
}

void MainWindow::on_createNewChatButton_clicked()
{
    clearCreateChatWindow();
    for (int i = 0; i < listOfChats.size(); i++) {
        if(listOfChats[i]->getData().type == "private_chat") {
            ChatLable *channelUser = new ChatLable(createChatDialog->ui->channelMembers, false, true, listOfChats[i]->getData());
            ChatLable *groupUser = new ChatLable(createChatDialog->ui->groupMembers, false, true, listOfChats[i]->getData());
            groupUsersSelection.append(groupUser);
            channelUsersSelection.append(channelUser);
        }
    }
    createChatDialog->exec();
}

void MainWindow::on_settingsButton_clicked()
{
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
    searchPattern = arg1;
}

