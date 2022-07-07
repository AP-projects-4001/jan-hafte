#ifndef LOGINHANDLEUTILITY_H
#define LOGINHANDLEUTILITY_H

#include <QObject>

class LoginHandleUtility : public QObject
{
    Q_OBJECT
public:
    LoginHandleUtility(QObject * parent = nullptr);
    bool getLoginStat() const;
public slots:
    void OnLoginSuccessful();
private:
    bool LoginSuccessful = false;
};

#endif // LOGINHANDLEUTILITY_H
