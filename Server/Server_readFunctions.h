#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QFile>
#include <QList>
#include <vector>

using namespace std;

QString USERS_PATH = "./users.json";
QString CHAT_PATH = "./chats.json";

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
    }
}

inline QByteArray register_user(QJsonObject readData)
{
    QFile file(USERS_PATH);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error opening file";
    }
    QJsonObject response;
    QByteArray data = file.readAll();
    if (checkValidUsername(readData["username"].toString(), data) == 0)
    {
        response["status"] = "not valid";
        return QJsonDocument(response).toJson();
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    QJsonArray all_chat, private_chat, group_chat, channel_chat;
    QJsonObject newUser;
    newUser["username"] = readData["username"].toString();
    newUser["password"] = readData["password"].toString();
    newUser["all_chats"] = all_chat;
    newUser["private_chat"] = private_chat;
    newUser["group_chat"] = group_chat;
    newUser["channel_chat"] = channel_chat;
    jsonArr.append(newUser);
    jsonObj["users"] = jsonArr;
    QJsonDocument newDoc(jsonObj);
    file.resize(0);
    file.write(newDoc.toJson());
    file.close();
    response["status"] = "valid";
    return QJsonDocument(response).toJson();
}

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
            foreach (QJsonValue x, user["all_chats"].toArray())
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
        response["content"] = content_array; // TYPE HERE
    }
    else
    {
        response["status"] = "not valid";
    }
    return QJsonDocument(response).toJson();
}

inline QByteArray create_chat(QJsonObject readData, QString chatType)
{
    // when I write this function, I understand it but now I cant
    QJsonObject response;
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
    QJsonDocument jsonDoc = QJsonDocument::fromJson(chatData);
    QJsonObject chatJson = jsonDoc.object();

    QJsonArray userDatabse = jsonObj["users"].toArray();   // user database is up
    QJsonArray chatDatabase = chatJson["chats"].toArray(); // chatDatabase is up

    QJsonObject newChat;
    newChat["id"] = chatJson[chatType].toArray().size() + 1;
    newChat["creator"] = readData["creator"].toString();
    newChat["participants"] = readData["participants"].toArray();
    newChat["messages"] = QJsonArray();
    chatDatabase.append(newChat);
    chatJson[chatType] = chatDatabase;
    QJsonDocument newDoc(chatJson);
    chatFile.resize(0);
    chatFile.write(newDoc.toJson());
    chatFile.close();
    update_chats(readData["creator"].toString(), chatType, readData["id"].toString());
    update_chats(readData["creator"].toString(), "all_chats", readData["id"].toString());
    return "DONE!";
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
