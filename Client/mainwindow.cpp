#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyThread *thread = new MyThread();
    connect(thread,SIGNAL(recievemassage(QJsonObject)),this,SLOT(getdata()));


    // just testing;
    for (int i = 0; i < 10; i++)
        ChatLable *chatLable = new ChatLable(ui->chatListAreaContentSlot, false, true);

    ui->topInfoBarArea->hide();
    ui->chatLineEdit->clear();
    //ui->chatViewTypeArea->hide();

}

void MainWindow::getdata()
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

void MainWindow::gettingchat()
{
    QJsonObject o;
    o["header"]="gettingchat";
    o["chat_type"] = chat_type;
    o["username"]=user_unique_id;
    o["chat_id"]=chat_unique_id;
    QJsonDocument d(o);
    e.writedata(d.toJson());

    //show them on chat
}

void MainWindow::createpv()
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "private_chat";
    o["creator"]=user_unique_id;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e.writedata(d.toJson());
}

void MainWindow::creategroup()
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "group";
    o["creator"]=user_unique_id;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e.writedata(d.toJson());
}

void MainWindow::createchannel()
{
    QJsonObject o;
    o["header"]="create_chat";
    o["chatType"] = "channel";
    o["creator"]=user_unique_id;
    o["participants"] = participants_username;
    QJsonDocument d(o);
    e.writedata(d.toJson());
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

