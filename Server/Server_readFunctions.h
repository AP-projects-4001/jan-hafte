#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QFile>
#include <QList>
#include <vector>
#include <QUuid>

using namespace std;

QString USERS_PATH = "./users.json";
QString CHAT_PATH = "./chats.json";
QString MESSAGES_PATH = "./messages.json";

QJsonObject userFinder(QString user_id) {
    QFile file(USERS_PATH);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject obj = doc.object();
    QJsonArray users = obj["users"].toArray();
    for (int i = 0; i < users.size(); i++) {
        QJsonObject user = users[i].toObject();
        if (user["id"].toString() == user_id) {
            return user;
        }
    }
    return QJsonObject();
}

QJsonObject chatFinder(QString chat_id) {
    QJsonObject chat;
    QFile file(CHAT_PATH);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return chat;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();
    QJsonArray chats = obj["chats"].toArray();
    QJsonArray channel = chats[0].toObject()["channel_chat"].toArray();
    QJsonArray group = chats[1].toObject()["group_chat"].toArray();
    QJsonArray private_chat = chats[2].toObject()["private_chat"].toArray();

    for (int i = 0; i < channel.size(); i++) {
        QJsonObject chat = channel[i].toObject();
        if (chat["id"].toString() == chat_id) {
            return chat;
        }
    }
    for (int i = 0; i < group.size(); i++) {
        QJsonObject chat = group[i].toObject();
        if (chat["id"].toString() == chat_id) {
            return chat;
        }
    }
    for (int i = 0; i < private_chat.size(); i++) {
        QJsonObject chat = private_chat[i].toObject();
        if (chat["id"].toString() == chat_id) {
            return chat;
        }
    }
    /*
    return "";*/
    return chat;
}

QJsonObject messageFinder(QString msg_id) {
    QJsonObject message;
    QFile file(MESSAGES_PATH);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return message;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();
    QJsonArray messages = obj["messages"].toArray();
    for (int i = 0; i < messages.size(); i++) {
        QJsonObject msg = messages[i].toObject();
        if (msg["id"].toString() == msg_id) {
            return msg;
        }
    }
    return message;
}

QJsonObject get_user_chats(QString username) {
    // get username
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    QJsonObject chatForClient;
    QJsonArray chatArrayForClient;
    for (int i = 0; i < jsonArr.size(); i++) {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"] == username) {
            QJsonArray chats;
            QJsonArray all_chats = user["all_chats"].toArray();
            for (int i = 0; i < all_chats.size(); i++) {
                QJsonObject chat = all_chats[i].toObject();
                QJsonObject founded_chat = chatFinder(chat["id"].toString());
                QJsonArray participants = founded_chat["participants"].toArray();
                chatForClient["id"] = chat["id"].toString();
                chatForClient["last_message"] = chat["last_message"].toString();
                chatForClient["last_message_time"] = chat["last_message_time"].toString();
                chatForClient["creator"] = founded_chat["creator"].toString();
                chatForClient["name"] = userFinder(participants[0].toString())["username"].toString();
                chatArrayForClient.append(chatForClient);
            }
            QJsonObject finalObject;
            finalObject["chats"] = chatArrayForClient;
            QJsonDocument newDoc(finalObject);
            return newDoc.object();
        }
    }
}

// obj can be messages, chats, users / work only for users and messages
// id type because id for users are username and chats are id
// workin fine
void updateGlobalFile(QString filePath, QString obj, QString obj_id, QString id_type,  QString key, QString value) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj[obj].toArray();
    for (int i = 0; i < jsonArr.size(); i++) {
        QJsonObject obj = jsonArr[i].toObject();
        if (obj[id_type].toString() == obj_id) {
            obj[key] = value;
            jsonArr[i] = obj;
            break;
        }
    }
    // save new user object
    QJsonObject finalObject;
    finalObject[obj] = jsonArr;
    QJsonDocument newDoc(finalObject);
    // write into file
    QFile file2(filePath);
    file2.open(QIODevice::WriteOnly);
    file2.resize(0);
    file2.write(newDoc.toJson());
    file2.close();

}
// workin fine
int foundPlacer(QString chatType)
{
    int placer = -1;
    if (chatType == "channel_chat")
    {
        placer = 0;
    }
    else if (chatType == "group_chat")
    {
        placer = 1;
    }
    else if (chatType == "private_chat")
    {
        placer = 2;
    }
    return placer;
}
// workin fine
int checkValidUsername(QString username, QByteArray jsonDb)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"].toString() == username)
        {
            return 0;
        }
    }
    return 1;
}
// workin fine
int checkValidEmail(QString email, QByteArray jsonDb)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (user["email"].toString() == email)
        {
            return 0;
        }
    }
    return 1;
}
// workin fine
int checkValidPhoneNumber(QString phoneNumber, QByteArray jsonDb)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (!QString::compare(user["phone_number"].toString(), phoneNumber))
        {
            return 0;
        }
    }
    return 1;
}
// workin fine
void update_chats(QString username, QString chatType, QString value)
{
    QFile file(USERS_PATH);
    file.open(QIODevice::ReadWrite);
    QByteArray jsonDb = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"].toString() == username)
        {
            if (chatType != "all_chats")
            {
                QJsonArray chat = user[chatType].toArray();
                chat.append(value);
                user[chatType] = chat;
                jsonArr[i] = user;
                jsonObj["users"] = jsonArr;
                jsonDoc.setObject(jsonObj);
                file.resize(0);
                file.write(jsonDoc.toJson());
                file.close();
                return;
            }
            else
            {
                QJsonArray chat = user["all_chats"].toArray();
                QJsonObject chatObj;
                chatObj["id"] = value;
                chatObj["last_message"] = "";
                chatObj["last_message_time"] = "";
                chat.append(chatObj);
                user["all_chats"] = chat;
                jsonArr[i] = user;
                jsonObj["users"] = jsonArr;
                jsonDoc.setObject(jsonObj);
                file.resize(0);
                file.write(jsonDoc.toJson());
                file.close();
                /*chat.append(value);
                user["all_chats"] = chat;
                jsonArr[i] = user;
                jsonObj["users"] = jsonArr;
                jsonDoc.setObject(jsonObj);
                file.resize(0);
                file.write(jsonDoc.toJson());
                file.close();
                return;*/
            }
        }
    }
}

void update_messages_in_chatDB(QString chatType, QString chat_id, QString msg_id)
{
    QFile file(CHAT_PATH);
    file.open(QIODevice::ReadWrite);
    int placer = foundPlacer(chatType);
    QByteArray jsonDb = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["chats"].toArray();
    QJsonObject chat_temp = jsonArr[placer].toObject();
    QJsonArray chat_temp2 = chat_temp[chatType].toArray();
    for (int i = 0; i < chat_temp2.size(); i++)
    {
        QJsonObject arrTemp = chat_temp2[i].toObject();
        if (arrTemp["id"] == chat_id)
        {
            QJsonArray myMessages = arrTemp["messages"].toArray();
            myMessages.append(msg_id);
            arrTemp["messages"] = myMessages;
            chat_temp2[i] = arrTemp;
            chat_temp[chatType] = chat_temp2;
            jsonArr[placer] = chat_temp;
            jsonObj["chats"] = jsonArr;
            jsonDoc.setObject(jsonObj);
            file.resize(0);
            file.write(jsonDoc.toJson());
            file.close();
            return;
        }
    }
    return;
}
// workin fine
inline QByteArray register_user(QJsonObject readData)
{
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error opening file";
    }
    QJsonObject response;
    QByteArray data = file.readAll();
    if (checkValidUsername(readData["username"].toString(), data) == 0 || checkValidEmail(readData["email"].toString(), data) == 0 || checkValidPhoneNumber(readData["phone"].toString(), data) == 0)
    {
        response["status"] = "not valid";
        response["header"] = "register";
        return QJsonDocument(response).toJson();
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    QJsonArray all_chat, private_chat, group_chat, channel_chat;
    QJsonObject newUser;
    newUser["username"] = readData["username"].toString();
    newUser["password"] = readData["password"].toString();
    newUser["phone"] = readData["phone"].toString();
    newUser["email"] = readData["email"].toString();
    newUser["birthday"] = readData["birthday"].toString();
    newUser["all_chats"] = all_chat;
    newUser["private_chat"] = private_chat;
    newUser["group_chat"] = group_chat;
    newUser["channel_chat"] = channel_chat;
    newUser["profile"] = "";
    jsonArr.append(newUser);
    jsonObj["users"] = jsonArr;
    QJsonDocument newDoc(jsonObj);
    file.resize(0);
    file.write(newDoc.toJson());
    file.close();
    response["status"] = "valid";
    response["header"] = "register";
    return QJsonDocument(response).toJson();
}
// workin fine
inline QByteArray create_chat(QJsonObject readData, QString chatType)
{
    // when I write this function, I understand it but now I cant
    int placer = foundPlacer(chatType);
    QFile userFile(USERS_PATH);
    QFile chatFile(CHAT_PATH);
    if (!userFile.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error opening file";
    }
    if (!chatFile.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error opening file";
    }
    QByteArray userData = userFile.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData);
    QJsonObject jsonObj = jsonDoc.object();

    QByteArray chatData = chatFile.readAll();
    QJsonDocument chatDoc = QJsonDocument::fromJson(chatData);
    QJsonObject chatJson = chatDoc.object();
    // qDebug() << chatJson;

    QJsonArray userDatabse = jsonObj["users"].toArray();   // user database is up
    QJsonArray chatDatabase = chatJson["chats"].toArray(); // chatDatabase is up

    // qDebug() << chatDatabase;
    QJsonObject tmp = chatDatabase[placer].toObject();
    QJsonArray tmp_array = tmp[chatType].toArray();
    QJsonObject newChat;
    newChat["id"] = QUuid::createUuid().toString().remove("{").remove("}");
    newChat["creator"] = readData["creator"].toString();
    newChat["participants"] = readData["participants"].toArray();
    newChat["messages"] = QJsonArray();
    if (chatType == "channel_chat" || chatType == "group_chat") {
        newChat["name"] = readData["name"].toString();
        newChat["profile"] = readData["profile"].toString();
    }
    if (chatType == "private_chat") {
        QString myUserId = readData["participants"].toArray()[0].toString();
        newChat["reciever"] = myUserId;
    }
    tmp_array.append(newChat);
    tmp[chatType] = tmp_array;
    chatDatabase[placer] = tmp;
    QJsonArray temp_2 = chatDatabase;
    chatJson["chats"] = temp_2;
    QJsonDocument newDoc(chatJson);
    chatFile.resize(0);
    chatFile.write(newDoc.toJson());
    chatFile.close();
    update_chats(readData["creator"].toString(), chatType, newChat["id"].toString());
    update_chats(readData["creator"].toString(), "all_chats", newChat["id"].toString());
    for (int i=0; i<readData["participants"].toArray().size(); i++) {
        if (readData["participants"].toArray()[i].toString() != readData["creator"].toString()) {
            update_chats(readData["participants"].toArray()[i].toString(), "all_chats", newChat["id"].toString());
            update_chats(readData["participants"].toArray()[i].toString(), chatType, newChat["id"].toString());
        }
    }
    QJsonObject finalTemp;
    finalTemp["status"] = "done";
    return QJsonDocument(finalTemp).toJson();
    // save new chat to user file // CODE HERE //
}

inline QByteArray search_user(QJsonObject readData)
{
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"] == readData["searched_field"] || user["phone"] == readData["searched_field"])
        {
            QJsonObject found_user;
            found_user["username"] = user["username"].toString();
            found_user["phone"] = user["phone"].toString();
            QJsonDocument newDoc(found_user);
            return newDoc.toJson();
        }
    }
}

inline QByteArray save_message(QJsonObject readData)
{
    QFile file(MESSAGES_PATH);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["messages"].toArray();
    QJsonObject newMessage;
    newMessage["id"] = QString::number(jsonArr.size() + 1);
    newMessage["sender"] = readData["sender"].toString();
    newMessage["message_text"] = readData["message_text"].toString();
    newMessage["time"] = readData["time"].toString();
    newMessage["chat_id"] = readData["chat_id"].toString();
    newMessage["chat_type"] = readData["chat_type"].toString();
    jsonArr.append(newMessage);
    jsonObj["messages"] = jsonArr;
    QJsonDocument newDoc(jsonObj);
    file.resize(0);
    update_messages_in_chatDB(readData["chat_type"].toString(), readData["chat_id"].toString(), newMessage["id"].toString());
    file.write(newDoc.toJson());
    file.close();
    return "DONE!";
}

inline QByteArray get_messages(QJsonObject readData)
{
    QFile file(MESSAGES_PATH);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["messages"].toArray();
    QJsonArray messages;
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject message = jsonArr[i].toObject();
        if (message["chat_id"] == readData["chat_id"] && message["chat_type"] == readData["chat_type"])
        {
            messages.append(message);
        }
    }
    QJsonDocument newDoc(messages);
    return newDoc.toJson();
}
// workin fine
inline QByteArray login_user(QJsonObject readData)
{
    int flag = 0;
    QJsonObject response;
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    if (checkValidUsername(readData["username"].toString(), data) == 1)
    {
        response["status"] = "not valid";
        response["header"] = "login";
        return QJsonDocument(response).toJson();
    }
    QJsonDocument mydoc = QJsonDocument::fromJson(data);
    QJsonObject myobj = mydoc.object();
    QJsonArray content_array;
    QJsonArray myarr = myobj["users"].toArray();
    vector<QString> all_chats_vector;
    /*QJsonObject readData2;
    QJsonArray test;                           |||||   FOR TESTING CREATE CHAT |||||
    test.append("mmd");
    readData2["chat_type"] = "private_chat";
    readData2["creator"] = "atid";
    readData2["participants"] = test;
    create_chat(readData2, "private_chat");*/
    for (int i = 0; i < myarr.size(); i++)
    {
        QJsonObject user = myarr[i].toObject();
        if (user["username"].toString() == readData["username"].toString() && user["password"].toString() == readData["password"].toString())
        {
            foreach(QJsonValue x, user["all_chats"].toArray())
            {
                all_chats_vector.push_back(x.toString());
            }
            // all_chat_vector contains all chat id that user has

            flag = 1;
        }
    }
    if (flag == 1)
    {
        response["status"] = "valid";
        response["header"] = "login";
        response["content"] = get_user_chats(readData["username"].toString()); // TYPE HERE
    }
    else
    {
        response["status"] = "not valid";
        response["header"] = "login";
    }
    return QJsonDocument(response).toJson();
}



// TODO: change username / email / phoneNumber
