#include "createchatdialog.h"
#include "ui_createchatdialog.h"

CreateChatDialog::CreateChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateChatDialog)
{
    ui->setupUi(this);
}

CreateChatDialog::~CreateChatDialog()
{
    delete ui;
}

void CreateChatDialog::on_newChannelButton_clicked()
{
    ui->newChannelButton->setChecked(true);
    ui->newContactButton->setChecked(false);
    ui->newGroupButton->setChecked(false);
    ui->pages->setCurrentIndex(0);
}


void CreateChatDialog::on_newGroupButton_clicked()
{
    ui->newChannelButton->setChecked(false);
    ui->newContactButton->setChecked(false);
    ui->newGroupButton->setChecked(true);
    ui->pages->setCurrentIndex(1);
}


void CreateChatDialog::on_newContactButton_clicked()
{
    ui->newChannelButton->setChecked(false);
    ui->newContactButton->setChecked(true);
    ui->newGroupButton->setChecked(false);
    ui->pages->setCurrentIndex(2);
}


void CreateChatDialog::on_createChannelButton_clicked()
{

}


void CreateChatDialog::on_createGroupButton_clicked()
{

}


void CreateChatDialog::on_MessageContactButton_clicked()
{

}

void CreateChatDialog::on_channelProfilePicButton_clicked()
{
    QFileDialog *dialog = new QFileDialog(this);
    dialog->setWindowFlags(Qt::Popup);
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setNameFilter(tr("Images (*.png *.jpeg *.jpg *.gif)"));

    if(dialog->exec()) {
        QString path = dialog->selectedFiles()[0];
        QImage loadedImage(path);
        ui->channelProfilePicButton->setIcon(QIcon(Utilities::maskImage(loadedImage)));
    }
}


void CreateChatDialog::on_contactInfoInput_textChanged(const QString &arg1)
{

}

