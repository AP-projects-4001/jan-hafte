#include "chatlable.h"

ChatLable::ChatLable(QWidget *parent)
    : QFrame{parent}
{
    profilePicSlot = new QLabel(this);
    nameField = new QLabel(this);
    lastMessageField = new QLabel(this);

    setMinimumHeight(64);
    setStyleSheet(QString("background: red; pressed{background:black;}"));
    profilePicSlot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    profilePicSlot->setFixedSize(64,64);
    nameField->move(70, 15);
    lastMessageField->move(70,30);

    nameField->setText("Profile Name");
    lastMessageField->setText("Hi! This is just a test...");

    parent->layout()->addWidget(this);
}
