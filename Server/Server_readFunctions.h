#ifndef SERVER_READFUNCTIONS_H
#define SERVER_READFUNCTIONS_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QFile>

using namespace std;

int checkValidUsername(QString username, QByteArray jsonDb) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonDb);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    for (int i = 0; i < jsonArr.size(); i++) {
        QJsonObject user = jsonArr[i].toObject();
        if (user["username"].toString() == username) {
            return 0;
        }
    }
    return 1;
}


inline QByteArray register_user(QJsonObject readData) {
    QFile file("./user.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    if (checkValidUsername(readData["username"].toString(), data) == 0) {
        return "not valid";
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArr = jsonObj["users"].toArray();
    QJsonObject newUser;
    newUser["username"] = readData["username"].toString();
    newUser["password"] = readData["password"].toString();
    jsonArr.append(newUser);
    jsonObj["users"] = jsonArr;
    QJsonDocument newDoc(jsonObj);
    file.resize(0);
    file.write(newDoc.toJson());
    file.close();
    return "valid";
}


inline QByteArray login_user(QJsonObject readData) {
    QFile file("./user.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file";
    }
    QByteArray data = file.readAll();
    if (checkValidUsername(readData["username"].toString(), data) == 1) {
        return "not valid";
    }
    QJsonDocument mydoc = QJsonDocument::fromJson(data);
    QJsonObject myobj = mydoc.object();
    QJsonArray myarr = myobj["users"].toArray();
    for (int i = 0; i < myarr.size(); i++) {
        QJsonObject user = myarr[i].toObject();
        if (user["username"].toString() == readData["username"].toString() && user["password"].toString() == readData["password"].toString()) {
            return "valid";
        }
    }
}

#endif // SERVER_READFUNCTIONS_H
