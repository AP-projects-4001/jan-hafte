#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyThread *thread = new MyThread(user_unique_id);
    e = new myClient();
    e->connectingToServer();
    connect(e, SIGNAL(recievemessage(QJsonObject)), this, SLOT(getdata(QJsonObject data)));
    connect(thread, SIGNAL(recievemessage(QJsonObject)), this, SLOT(getdata(QJsonObject data)));


    for(int i = 0; i < 5; i++) {
        ChatLable *label = new ChatLable(ui->chatListAreaContentSlot, true, true);
        connect(label, SIGNAL(click(ChatLable*)), this, SLOT(onChatLableClick(ChatLable*)));
    }


    GraphView *graphView = new GraphView(ui->graphViewArea);
    ui->graphViewArea->layout()->addWidget(graphView);


    ui->topInfoBarArea->hide();
    ui->chatLineEdit->clear();
    //ui->chatViewTypeArea->hide();
}

void MainWindow::getdata(QJsonObject data)
{
    if (data["header"]=="get_user_message"){

    }

    else if (data["header"]=="get_messages"){

    }

    else if (data["header"]=="create_chat"){
        QString status = data["status"].toString();


        if (status == "valid") {

        }
        else if (status == "not valid"){
//            message->setText("Log In Failed");  // delete this
//            std::messages->show();
        }
        else{
//            message->setText("Error");  // delete this
//            message->show();
        }
    }

    else if(data["header"]=="search_user"){

    }

    else if(data["header"]=="change_data"){

    }

    else if(data["header"]=="save_message"){

    }

}

void MainWindow::onChatLableClick(ChatLable *label)
{
    if(selectedChatLabel != nullptr) {
        selectedChatLabel->setChecked(false);
    }

    selectedChatLabel = label;
    selectedChat = label->getData();
    label->setChecked(true);
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

void MainWindow::gettingchat(QString chat_unique_id, QString chat_type)
{
    QJsonObject o;
    o["header"]="get_messages";
    o["chat_type"] = chat_type;
    o["username"]=user_unique_id;
    o["chat_id"]=chat_unique_id;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::createpv(QJsonArray participants_username)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "private_chat";
    o["creator"]=user_unique_id;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::creategroup(QJsonArray participants_username)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "group";
    o["creator"]=user_unique_id;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::createchannel(QJsonArray participants_username)
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "channel";
    o["creator"]=user_unique_id;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::searchuser(QString chat_unique_id,QString time)
{
    QJsonObject o;
    o["header"]="search_user";
    o["chat_id"] = chat_unique_id;
    o["sender"] = user_unique_id;
    o["time"] = time;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::changeusername(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=user_unique_id;
    o["key"]="username";
    o["value"]=newdata;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::changeemail(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=user_unique_id;
    o["key"]="email";
    o["value"]=newdata;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}

void MainWindow::changephone(QString newdata)
{
    QJsonObject o;
    o["header"]="change_data";
    o["username"]=user_unique_id;
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
    o["sender"] = user_unique_id;
    o["message_text"] = message;
    o["time"] = time;
    o["chat_type"]=chat_type;
    QJsonDocument d(o);
    e->writedata(d.toJson());
}



void MainWindow::on_createNewChatButton_clicked()
{
    CreateChatDialog *createChatDialog = new CreateChatDialog(this);
    createChatDialog->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    createChatDialog->exec();
}


void MainWindow::on_settingsButton_clicked()
{
    SettingsDialog *settingsDialog = new SettingsDialog(this);
    settingsDialog->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    settingsDialog->setAttribute(Qt::WA_DeleteOnClose);
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

