#include "chatlable.h"

ChatLable::ChatLable(QWidget *parent, bool lastMessage, bool isCheckable, chatData data)
    : QFrame{parent} , showsLastMessage(lastMessage) , isCheckable(isCheckable), data(data)
{
    connect(this, SIGNAL(click(ChatLable*)), this, SLOT(OnLableClick()));
    connect(this, SIGNAL(release()), this, SLOT(OnLableRelease()));

    profilePicSlot = new QLabel(this);
    nameField = new QLabel(this);
    lastMessageField = new QLabel(this);

    setMinimumHeight(72);
    profilePicSlot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    profilePicSlot->setFixedSize(64,64);
    profilePicSlot->move(5,4);
    nameField->move(70, 15);
    lastMessageField->move(70,30);
    this->setProperty("clicked", false);

    setStyleSheet("QFrame[clicked=\"true\"] { background-color: #956cec; } "
                  "QFrame[clicked=\"false\"] { background-color: white; }"
                  "QFrame:hover[clicked=\"false\"]{background: #e9e9e9;}"
                  "");

    nameField->setText(data.name);
    profilePicSlot->setPixmap(Utilities::maskImage(data.profile, 64));

    if(lastMessage) lastMessageField->setText(data.lastMessage);
    else lastMessageField->setText(data.phoneNumber);

    parent->layout()->addWidget(this);
}

void ChatLable::mousePressEvent(QMouseEvent *me)
{
    if (me->button() == Qt::LeftButton) {
        emit click(this);
        me->accept();
        return;
    }

    QFrame::mousePressEvent(me);
}

void ChatLable::mouseReleaseEvent(QMouseEvent *me)
{
    emit release();
}

void ChatLable::setChecked(bool val)
{
    isChecked = val;
    this->setProperty("clicked", val);
    style()->unpolish(this);
    style()->polish(this);
}

void ChatLable::setCheckable(bool val)
{
    isCheckable = val;
}

chatData ChatLable::getData()
{
    return data;
}


void ChatLable::OnLableClick()
{
    if(!isCheckable) {
        this->setProperty("clicked", true);
    } else {
        isChecked = !isChecked;
        this->setProperty("clicked", isChecked);
    }

    style()->unpolish(this);
    style()->polish(this);
}

void ChatLable::OnLableRelease()
{
    if(!isCheckable) {
        this->setProperty("clicked", false);
    } else {

    }
    style()->unpolish(this);
    style()->polish(this);
}
