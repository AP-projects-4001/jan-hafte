#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QBuffer>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    //ui->profilePic->setPixmap(QPixmap::fromImage());
}

void SettingsDialog::setUpData(QString name, QString email, QString phone, QImage profile)
{
    ui->usernameLabel->setText(name);
    ui->emailAddressLabel->setText(email);
    ui->phoneLabel->setText(phone);
    ui->profilePic->setPixmap(Utilities::maskImage(profile, 128));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_editUsernameButton_clicked()
{
    ChangePropertyDialog * editDialog = new ChangePropertyDialog(this);
    Utilities::setUpTextEditDialog(editDialog, new QLabel("Change Username", editDialog),
                                   new QLineEdit(editDialog), "Enter new username",
                                   new QPushButton("Submit Changes", editDialog));

    connect (editDialog, SIGNAL(submit(QString)), this, SLOT(changeUsername(QString)));

    editDialog->show();
}


void SettingsDialog::on_editEmailButton_clicked()
{
    ChangePropertyDialog * editDialog = new ChangePropertyDialog(this);
    Utilities::setUpTextEditDialog(editDialog, new QLabel("Change Email Address", editDialog),
                                   new QLineEdit(editDialog), "Enter new email address",
                                   new QPushButton("Submit Changes", editDialog));

    connect (editDialog, SIGNAL(submit(QString)), this, SLOT(changeEmail(QString)));

    editDialog->show();
}


void SettingsDialog::on_editPhoneButton_clicked()
{
    ChangePropertyDialog * editDialog = new ChangePropertyDialog(this);
    Utilities::setUpTextEditDialog(editDialog, new QLabel("Change phone number", editDialog),
                                   new QLineEdit(editDialog), "Enter new phone number",
                                   new QPushButton("Submit Changes", editDialog));

    connect (editDialog, SIGNAL(submit(QString)), this, SLOT(changePhone(QString)));

    editDialog->show();
}


void SettingsDialog::on_addProfileBlacklistButton_clicked()
{

}


void SettingsDialog::on_addPhoneBlacklistButton_clicked()
{

}


void SettingsDialog::changeUsername(QString newUsername)
{
    emit userNameChangeRequest(newUsername);
}

void SettingsDialog::changePhone(QString newPhone)
{
    emit phoneChangeRequest(newPhone);
}

void SettingsDialog::changeEmail(QString newEmail)
{
    emit emailChangeRequest(newEmail);
}

void SettingsDialog::changeProfile(QString newProfile)
{
    emit profileChangeRequest(newProfile);
}

