#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QImage pic = ui->profilePic->pixmap().toImage();
    ui->profilePic->setPixmap(Utilities::maskImage(pic, 128));
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

}

void SettingsDialog::changePhone(QString newUsername)
{

}

void SettingsDialog::changeEmail(QString newUsername)
{

}

