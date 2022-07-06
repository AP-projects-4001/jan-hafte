#include "loginhandleutility.h"

LoginHandleUtility::LoginHandleUtility(QObject *parent): QObject(parent)
{

}

bool LoginHandleUtility::getLoginStat() const
{
    return LoginSuccessful;
}

void LoginHandleUtility::OnLoginSuccessful()
{
    LoginSuccessful = true;
}
