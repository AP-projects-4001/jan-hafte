#ifndef CHATLABLE_H
#define CHATLABLE_H

#include <QFrame>
#include <QLabel>
#include <QLayout>

class ChatLable : public QFrame
{
    Q_OBJECT
public:
    explicit ChatLable(QWidget *parent = nullptr);

signals:

private:
    QLabel *nameField;
    QLabel *lastMessageField;
    QLabel *profilePicSlot;
};

#endif // CHATLABLE_H
