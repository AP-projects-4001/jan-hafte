#include "loginhandleutility.h"

LoginHandleUtility::LoginHandleUtility(QObject *parent, QObject *loginWindow): QObject(parent)
{
    connect(loginWindow, SIGNAL(loginDone()), this, SLOT(OnLoginSuccessful()));
}

bool LoginHandleUtility::getLoginStat() const
{
    return LoginSuccessful;
}

void LoginHandleUtility::OnLoginSuccessful()
{
    LoginSuccessful = true;
}
