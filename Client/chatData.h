#ifndef CHATDATA_H
#define CHATDATA_H


#include <QObject>
#include <QImage>
#include <QDateTime>

class chatData {
public:
    enum Type {channel, group, contact};
    QString name;
    QString username;
    Type type;
    QString phoneNumber;
    QString emailAddress;
    QImage profile;
    QString lastMessage;
    QDateTime lastMessageTime;

    chatData& operator=(const chatData& rhs);
    int Compare(const chatData& rhs);
};

inline chatData &chatData::operator=(const chatData &rhs)
{
    name = rhs.name;
    username = rhs.username;
    type = rhs.type;
    phoneNumber = rhs.phoneNumber;
    emailAddress = rhs.emailAddress;
    profile = rhs.profile;
    lastMessage = rhs.lastMessage;
    lastMessageTime = rhs.lastMessageTime;
    return *this;
}

inline int chatData::Compare(const chatData &rhs)
{
    if(lastMessageTime > rhs.lastMessageTime) {
        return 1;
    } else if (lastMessageTime < rhs.lastMessageTime) {
        return -1;
    } else {
        return 0;
    }
}


#endif // CHATDATA_H
