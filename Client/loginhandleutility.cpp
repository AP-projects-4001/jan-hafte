#include "loginhandleutility.h"

LoginHandleUtility::LoginHandleUtility(QObject *parent, QObject *loginWindow): QObject(parent)
{
    connect(loginWindow, SIGNAL(loginDone(QString)), this, SLOT(OnLoginSuccessful(QString)));
}

bool LoginHandleUtility::getLoginStat() const
{
    return LoginSuccessful;
}

QString LoginHandleUtility::getUsername() const
{
    return username;
}

void LoginHandleUtility::OnLoginSuccessful(QString username)
{
    LoginSuccessful = true;
    this->username = username;
}
