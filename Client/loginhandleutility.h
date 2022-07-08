#ifndef LOGINHANDLEUTILITY_H
#define LOGINHANDLEUTILITY_H

#include <QObject>

class LoginHandleUtility : public QObject
{
    Q_OBJECT
public:
    LoginHandleUtility(QObject * parent = nullptr, QObject *loginWindow = nullptr);
    bool getLoginStat() const;
    QString getUsername() const;
private slots:
    void OnLoginSuccessful(QString username);
private:
    bool LoginSuccessful = false;
    QString username;
};

#endif // LOGINHANDLEUTILITY_H
