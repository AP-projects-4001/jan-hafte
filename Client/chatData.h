#ifndef CHATDATA_H
#define CHATDATA_H


#include <QObject>
#include <QImage>
#include <QDateTime>

class chatData {
public:
    enum Type {channel, group, contact};
    QString name = "";
    Type type = Type::contact;
    QImage profile;
    QString lastMessage = "";
    QDateTime lastMessageTime;
};


#endif // CHATDATA_H
