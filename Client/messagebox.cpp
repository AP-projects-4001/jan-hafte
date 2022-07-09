#include "messagebox.h"

MessageBox::MessageBox(QWidget *parent, bool isSender, QString text, QString name, QDateTime time)
    : QWidget{parent}, message(text), time(time)
{
    messageFrame = new QFrame(this);
    messageFrame->setObjectName("frame");
    messageFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    messageFrame->setMaximumWidth(300);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout ->setContentsMargins(0,0,0,0);
    horizontalSpacer = new QSpacerItem(40,20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    if (isSender) {
        horizontalLayout->addSpacerItem(horizontalSpacer);
        horizontalLayout->addWidget(messageFrame);
    } else {
        horizontalLayout->addWidget(messageFrame);
        horizontalLayout->addSpacerItem(horizontalSpacer);
    }

    this->setLayout(horizontalLayout);

    messageText = new QLabel(messageFrame);

    verticalLayout = new QVBoxLayout();
    verticalLayout ->setContentsMargins(0,0,0,0);
    verticalLayout->addWidget(messageText);
    verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);

    messageFrame->setLayout(verticalLayout);

    QString style;
    if(isSender) {
        style = "QFrame#frame{ border: 15px solid; border-image: url(:/Graphics/Graphics/Message Bubble.svg) 15 round; padding-right:20px;}";
    } else {
        style = "QFrame#frame{ border: 15px solid; border-image: url(:/Graphics/Graphics/Message Bubble Other.svg) 15 round; padding-left:20px;}";
    }
    messageFrame->setStyleSheet(style);

    messageText->setWordWrap(true);
    messageText->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    parent->layout()->addWidget(this);
    QString content = name + ":\n" + text;
    messageText->setText(content);
}

void MessageBox::setText(const QString text)
{
    messageText->setText(text);
}
