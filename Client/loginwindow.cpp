#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QRegularExpression>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    message = new QMessageBox(this);
    e.connectingToServer();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_LoginButton_clicked()
{
    QString inpUsername = ui->lineEdit_Username->text();
    QString inpPassword = ui->lineEdit_Password->text();

    if(inpUsername.isEmpty() || inpPassword.isEmpty()) {
        message->setText("Enter Your Credentials Fully");
        message->show();
        clearLoginPage();
        return;
    }

    QJsonObject login;

    login["header"]="login";
    login["username"]=inpUsername;
    login["password"]=inpPassword;

    QJsonDocument d(login);
    e.writedata(d.toJson());
    e.getSocket()->waitForReadyRead(1);
    QByteArray f = e.getMsg();

    if (f == "valid"){
        message->setText("Successfully Logged In");  // delete this
        message->show();
    }
    else if (f == "not valid"){
        message->setText("UnSuccessfully Logged In");  // delete this
        message->show();
    }
    else{
        message->setText("error");  // delete this
        message->show();
    }
}


void LoginWindow::on_SignUpInsteadButton_clicked()
{
   clearLoginPage();
    ui->Pages->setCurrentIndex(1);
}


void LoginWindow::on_LoginInsteadButton_clicked()
{
    clearSignUpPage();
    ui->Pages->setCurrentIndex(0);
}


void LoginWindow::on_SignUpButton_clicked()
{
    QString inpUsername = ui->lineEdit_UsernameNew->text();
    QString inpPassword = ui->lineEdit_PasswordNew->text();
    QString inpPasswordReenter = ui->lineEdit_PasswordReenter->text();

    if(inpUsername.isEmpty() || inpPassword.isEmpty()) {
        message->setText("Please Fill Every Field");
        message->show();
        clearSignUpPage();
        return;
    }

    if(QString::compare(inpPassword, inpPasswordReenter, Qt::CaseSensitive) != 0) {
        message->setText("Passwords don't match!");
        message->show();
        clearSignUpPage();
        return;
    }

    switch (evaluatePasswordStrength(inpPassword)) {
    case -1:
        message->setText("Password is too Short");
        message->show();
        clearSignUpPage();
        return;
    case -2:
        message->setText("Password doesn't contain both lower and uppercase");
        message->show();
        clearSignUpPage();
        return;
//    case -3:
//        message->setText("Password doesn't contain special characters");
//        message->show();
//        clearSignUpPage();
//        return;
    default:
        break;
    }   

    QJsonObject regist;

    regist["header"]="register";
    regist["username"]=inpUsername;
    regist["password"]=inpPassword;

    QJsonDocument d(regist);
    e.writedata(d.toJson());
    e.getSocket()->waitForReadyRead(1);
    QByteArray f = e.getMsg();

    if (f == "valid"){
        message->setText("Successfully Logged In");  // delete this
        message->show();
    }
    else if (f == "not valid"){
        message->setText("UnSuccessfully Logged In");  // delete this
        message->show();
    }
    else{
        message->setText("error");  // delete this
        message->show();
    }

}

int LoginWindow::evaluatePasswordStrength(const QString &pass)
{
    if (pass.length() <= 8) {
        return - 1;
    }
    if (QString::compare(pass, pass.toLower(), Qt::CaseSensitive) == 0) {
        return - 2;
    }
    QRegularExpression RegEx("[!@#$%^&()_+]0123456789");
    if (!pass.contains(RegEx)) {
        return - 3;
    }
    return 0;
}

void LoginWindow::clearLoginPage()
{
    ui->lineEdit_Username->clear();
    ui->lineEdit_Password->clear();
}

void LoginWindow::clearSignUpPage()
{
    ui->lineEdit_UsernameNew->clear();
    ui->lineEdit_PasswordNew->clear();
    ui->lineEdit_PasswordReenter->clear();
}

