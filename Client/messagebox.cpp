#include "messagebox.h"

MessageBox::MessageBox(QWidget *parent)
    : QWidget{parent}
{
    messageFrame = new QFrame (this);
    messageFrame->setObjectName("frame");
    messageFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    messageFrame->setMaximumWidth(300);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout ->setContentsMargins(0,0,0,0);
    horizontalSpacer = new QSpacerItem(40,20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addSpacerItem(horizontalSpacer);
    horizontalLayout->addWidget(messageFrame);

    this->setLayout(horizontalLayout);

    messageText = new QLabel (messageFrame);

    verticalLayout = new QVBoxLayout();
    verticalLayout ->setContentsMargins(0,0,0,0);
    verticalLayout->addWidget(messageText);
    verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);

    messageFrame->setLayout(verticalLayout);

    QString style = "QFrame#frame{ border: 15px solid; border-image: url(:/Graphics/Graphics/Message Bubble.svg) 15 round; padding-right:30px;}";
    messageFrame->setStyleSheet(style);

    messageText->setWordWrap(true);
    messageText->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    messageText->setText("This Is a Test\n PAOdnakldmal;dsjap;dmA:SJd\n oajsdnadjhalsdha;sld");
}
