#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "myclient.h"
#include "mythread.h"
#include "utilities.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:

    void on_LoginButton_clicked();

    void on_SignUpInsteadButton_clicked();

    void on_LoginInsteadButton_clicked();

    void on_SignUpButton_clicked();

    void getdata(QJsonObject data);

signals:
    void loginDone(QString username);

private:
    Ui::LoginWindow *ui;
    QMessageBox *message;

    int evaluatePasswordStrength(const QString& pass);
    int checkSignUpInputForError (const QString& userN, const QString& pass, const QString& passR, const QString& email, const QString& phone);
    void clearLoginPage();
    void clearSignUpPage();
    myClient *e;
};

#endif // LOGINWINDOW_H
