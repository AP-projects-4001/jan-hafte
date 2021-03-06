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
        if (user["username"].toString() == user_id) {
            return user;
        }
    }
    return QJsonObject();
}

int findUserPlacer(QString id) {
    QFile file(USERS_PATH);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject obj = doc.object();
    QJsonArray users = obj["users"].toArray();
    for (int i = 0; i < users.size(); i++) {
        QJsonObject user = users[i].toObject();
        if (user["username"].toString() == id) {
            return i;
        }
    }
    return -1;
}

QString findChatPlacer(QString id) {
    QFile file(CHAT_PATH);
    file.open(QIODevice::ReadOnly);
    int place = 0;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject obj = doc.object();
    QJsonArray chats = obj["chats"].toArray();
    for (int i = 0; i < chats.size(); i++) {
        QJsonObject chat = chats[i].toObject();
        if (chat["id"].toString() == id) {
            place = i;
        }
    }
    if (place == 0) {
        return "channel_chat";
    }
    else if (place == 1) {
        return "group_chat";
    }
    else if (place == 2) {
        return "private_chat";
    }
    else {
        return "none";
    }
}

QJsonObject chatFinder(QString chat_id) {
    QJsonObject chat;
    QFile file(CHAT_PATH);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return chat;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();
    QJsonArray chats = obj["chats"].toArray();
    file.close();
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
    file.close();
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
// workin fine
QJsonObject get_user_chats(QString username, QString active_chat_id = "None") {
    // get username
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    QJsonArray chatArrayForClient;
    file.close();
    for (int i = 0; i < jsonArr.size(); i++) {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"] == username) {
            QJsonArray chats;
            QJsonArray all_chats = user["all_chats"].toArray();
            for (int j = 0; j < all_chats.size(); j++) {
                QJsonObject chatForClient;
                QJsonObject chat = all_chats[j].toObject();
                QJsonObject founded_chat = chatFinder(chat["id"].toString());
                qDebug() << founded_chat;
                if (founded_chat["chat_type"] == "group_chat" || founded_chat["chat_type"] == "channel_chat") {
                    chatForClient["id"] = chat["id"].toString();
                    chatForClient["last_message"] = chat["last_message"].toString();
                    chatForClient["last_message_time"] = chat["last_message_time"].toString();
                    chatForClient["creator"] = founded_chat["creator"].toString();
                    chatForClient["name"] = founded_chat["name"].toString();
                    chatForClient["profile"] = founded_chat["profile"].toString();
                    chatForClient["chat_type"] = founded_chat["chat_type"];
                }
                else {
                    chatForClient["id"] = chat["id"].toString();
                    chatForClient["last_message"] = chat["last_message"].toString();
                    chatForClient["last_message_time"] = chat["last_message_time"].toString();
                    chatForClient["chat_type"] = founded_chat["chat_type"];
                    chatForClient["creator"] = founded_chat["creator"].toString();
                    chatForClient["reciever"] = founded_chat["reciever"].toString();
                    if (founded_chat["creator"].toString() == username) {
                        chatForClient["phone"] = userFinder(founded_chat["reciever"].toString())["phone"];
                        chatForClient["profile"] = userFinder(founded_chat["reciever"].toString())["profile"];
                        //tof
                        chatForClient["name"] = userFinder(founded_chat["reciever"].toString())["name"];
                    }
                    else {
                        chatForClient["phone"] = userFinder(founded_chat["creator"].toString())["phone"];
                        chatForClient["profile"] = userFinder(founded_chat["creator"].toString())["profile"];
                        //tof
                        chatForClient["name"] = userFinder(founded_chat["creator"].toString())["name"];
                    }

                }
                chatArrayForClient.append(chatForClient);
            }
            // find active caht messages
            QJsonObject finalObject;
            if (active_chat_id != "None") {
                QJsonArray messages;
                QJsonObject active_chat = chatFinder(active_chat_id);
                int theSize = active_chat["messages"].toArray().size();
                for (int j = 0; j < theSize; j++) {
                    QJsonObject message = messageFinder(active_chat["messages"].toArray()[j].toString());
                    messages.append(message);
                }
                finalObject["messages"] = messages;
            }
            finalObject["chats"] = chatArrayForClient;
            finalObject["header"] = "get_continuous_data";
            qDebug() << finalObject;
            QJsonDocument newDoc(finalObject);
            return newDoc.object();
        }
    }
}

// obj can be messages, chats, users / work only for users and messages
// id type because id for users are username and chats are id
// workin fine
void updateGlobalFile(QString filePath, QString obj, QString obj_id, QString id_type, QString key, QString value) {
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
int existInArray(QString value, QJsonArray mydb) {
    for (int i = 0; i < mydb.size(); i++) {
        if (mydb[i].toString() == value) {
            return 1;
        }
    }
    return 0;
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
// workin fine
void update_last_message(QString chat_id, QString chatType, QString last_message, QString last_message_time)
{
    int placer = foundPlacer(chatType);
    QFile file2(CHAT_PATH);
    file2.open(QIODevice::ReadWrite);
    QByteArray jsonDb = file2.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["chats"].toArray();
    QJsonObject theChat = jsonArr[placer].toObject();
    QJsonArray chatArr = theChat[chatType].toArray();
    QJsonArray mypart;
    file2.close();
    for (int i = 0; i < chatArr.size(); i++)
    {
        QJsonObject chat = chatArr[i].toObject();
        if (chat["id"].toString() == chat_id)
        {
            mypart = chat["participants"].toArray();
            mypart.append(chat["creator"]);
        }
    }
    QFile file(USERS_PATH);
    file.open(QIODevice::ReadWrite);
    QByteArray jsonDb2 = file.readAll();
    QJsonDocument jsonDoc2 = QJsonDocument::fromJson(jsonDb2);
    QJsonObject jsonObj2 = jsonDoc2.object();
    QJsonArray jsonArr2 = jsonObj2["users"].toArray();
    qDebug() << mypart;
    for (int i = 0; i < mypart.size(); i++) {
        qDebug() << mypart[i].toString();
        QJsonObject theUser = userFinder(mypart[i].toString());
        qDebug() << theUser;
        QJsonArray chat = theUser["all_chats"].toArray();
        qDebug() << chat;
        int userPlace = findUserPlacer(theUser["username"].toString());
        qDebug() << userPlace;
        for (int j = 0; j < chat.size(); j++) {
            QJsonObject chatObj = chat[j].toObject();
            if (chatObj["id"].toString() == chat_id) {
                chatObj["last_message"] = last_message;
                chatObj["last_message_time"] = last_message_time;
                qDebug() << chatObj;
                chat[j] = chatObj;
                qDebug() << chat;
                theUser["all_chats"] = chat;
                qDebug() << theUser;
                jsonArr2[userPlace] = theUser;
                qDebug() << jsonArr2;
            }
        }
    }
    qDebug() << jsonArr2;
    QJsonObject finalTEMP;
    finalTEMP["users"] = jsonArr2;
    QJsonDocument mynewDoc(finalTEMP);
    file.resize(0);
    file.write(mynewDoc.toJson());
    file.close();
}
// workin fine
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
    newUser["name"] = readData["username"].toString();
    newUser["password"] = readData["password"].toString();
    newUser["phone"] = readData["phone"].toString();
    newUser["email"] = readData["email"].toString();
    newUser["all_chats"] = all_chat;
    newUser["private_chat"] = private_chat;
    newUser["group_chat"] = group_chat;
    newUser["channel_chat"] = channel_chat;
    newUser["profile"] = readData["profile"].toString();
    jsonArr.append(newUser);
    jsonObj["users"] = jsonArr;
    QJsonDocument newDoc(jsonObj);
    file.resize(0);
    file.write(newDoc.toJson());
    file.close();
    response["status"] = "valid";
    response["header"] = "register";
    response["username"] = readData["username"].toString();
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
    newChat["chat_type"] = chatType;
    newChat["participants"] = readData["participants"].toArray();
    newChat["messages"] = QJsonArray();
    if (chatType == "channel_chat" || chatType == "group_chat") {
        newChat["name"] = readData["name"].toString();
        newChat["profile"] = readData["profile"].toString();
    }
    if (chatType == "private_chat") {
        QString myUserId = readData["participants"].toArray()[0].toString();
        newChat["reciever"] = myUserId;
        for (int k = 0; k < tmp_array.size(); k++) {
            QJsonObject checkChat;
            checkChat = tmp_array[k].toObject();
            if ((checkChat["reciever"] == newChat["reciever"] || checkChat["reciever"] == newChat["creator"]) && (checkChat["creator"] == newChat["reciever"] || checkChat["creator"] == newChat["creator"])) {
                QJsonObject finalTemp;
                finalTemp["status"] = "not valid";
                chatFile.close();
                userFile.close();
                return QJsonDocument(finalTemp).toJson();
            }
        }

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
    for (int i = 0; i < readData["participants"].toArray().size(); i++) {
        if (readData["participants"].toArray()[i].toString() != readData["creator"].toString()) {
            update_chats(readData["participants"].toArray()[i].toString(), "all_chats", newChat["id"].toString());
            update_chats(readData["participants"].toArray()[i].toString(), chatType, newChat["id"].toString());
        }
    }
    QJsonObject finalTemp;
    finalTemp["header"] = "create_chat";
    finalTemp["status"] = "valid";
    return QJsonDocument(finalTemp).toJson();
    // save new chat to user file // CODE HERE //
}
// workin fine
inline QByteArray search_user(QJsonObject readData)
{
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    QJsonObject found_user;
    for (int i = 0; i < jsonArr.size(); i++)
    {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"] == readData["searched_field"] || user["phone"] == readData["searched_field"])
        {
            found_user["username"] = user["username"].toString();
            found_user["phone"] = user["phone"].toString();
            found_user["profile"] = user["profile"].toString();
            found_user["name"] = user["name"].toString();
            found_user["header"] = "search_user";
            found_user["status"] = "valid";
            QJsonDocument newDoc(found_user);
            return newDoc.toJson();
        }
    }
    found_user["status"] = "not valid";
    QJsonDocument newDoc(found_user);
    return newDoc.toJson();
}
// workin fine
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
    update_last_message(readData["chat_id"].toString(), readData["chat_type"].toString(), readData["message_text"].toString(), readData["time"].toString());
    file.write(newDoc.toJson());
    file.close();
    QJsonObject server_response;
    server_response["header"] = "save_message";
    server_response["status"] = "valid";
    return QJsonDocument(server_response).toJson();
}
// workin fine
inline QByteArray get_messages(QJsonObject readData)
{
    QFile file(MESSAGES_PATH);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    file.close();
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
    QJsonObject server_response;
    if (readData["chat_type"] == "group_chat" || readData["chat_type"] == "channel_chat") {
        QJsonObject founded_chat = chatFinder(readData["chat_id"].toString());
        server_response["creator"] = founded_chat["creator"].toString();
    }
    server_response["header"] = "get_messages";
    server_response["status"] = "valid";
    server_response["messages"] = messages;
    //qDebug() << server_response;
    return QJsonDocument(server_response).toJson();
}
// workin fine
inline QByteArray change_data(QJsonObject readData) {
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonObject response;
    if (readData["key"] == "name") {
        updateGlobalFile(USERS_PATH, "users", readData["username"].toString(), "username", "name", readData["value"].toString());
        response["status"] = "valid";
        response["name"] = readData["value"].toString();
    }
    else if (readData["key"] == "email") {
        if (checkValidEmail(readData["value"].toString(), data)) {
            updateGlobalFile(USERS_PATH, "users", readData["username"].toString(), "username", "email", readData["value"].toString());
            response["status"] = "valid";
            response["email"] = readData["value"].toString();
        }
        else {
            response["status"] = "not valid";
            response["error"] = "Invalid email";
        }
    }
    else if (readData["key"] == "phone") {
        if (checkValidPhoneNumber(readData["value"].toString(), data)) {
            updateGlobalFile(USERS_PATH, "users", readData["username"].toString(), "username", "phone", readData["value"].toString());
            response["status"] = "valid";
            response["phone"] = readData["value"].toString();
        }
        else {
            response["status"] = "not valid";
            response["error"] = "Invalid phone number";
        }
    }
    else if (readData["key"] == "profile") {
        updateGlobalFile(USERS_PATH, "users", readData["username"].toString(), "username", "profile", readData["value"].toString());
        response["status"] = "valid";
        response["profile"] = readData["value"].toString();
    }
    else {
        response["status"] = "not valid";
    }
    response["header"] = "change_data";
    qDebug() << response;
    return QJsonDocument(response).toJson();
}
// workin fine
inline QByteArray get_this_user(QJsonObject readData) {
    QJsonObject response;
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument mydoc = QJsonDocument::fromJson(data);
    QJsonObject myobj = mydoc.object();
    QJsonArray myarr = myobj["users"].toArray();
    for (int i = 0; i < myarr.size(); i++)
    {
        QJsonObject user = myarr[i].toObject();
        if (user["username"].toString() == readData["username"].toString())
        {
            response["status"] = "valid";
            response["header"] = "get_this_user";
            response["username"] = user["username"].toString();
            response["name"] = user["name"].toString();
            response["email"] = user["email"].toString();
            response["phone"] = user["phone"].toString();
            response["profile"] = user["profile"].toString();
        }
    }
    return QJsonDocument(response).toJson();
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
    file.close();
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
        response["username"] = readData["username"].toString(); // TYPE HERE
    }
    else
    {
        response["status"] = "not valid";
        response["header"] = "login";
    }
    return QJsonDocument(response).toJson();
}


// TODO:


