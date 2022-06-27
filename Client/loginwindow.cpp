#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QRegularExpression>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    message = new QMessageBox(this);
    message->setStyleSheet("");
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
        message->setText("Login Failed, Wrong Credentials");  // delete this
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

    int eval = checkSignUpInputForError(inpUsername, inpPassword, inpPasswordReenter);
    if (eval != 0) {
        clearSignUpPage();
        return;
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
        message->setText("Successfully Signed Up");  // delete this
        message->show();
    }
    else if (f == "not valid"){
        message->setText("Sign Up Failed");  // delete this
        message->show();
    }
    else{
        message->setText("Error");  // delete this
        message->show();
    }

}

int LoginWindow::checkSignUpInputForError(const QString &userN, const QString &pass, const QString &passR)
{
    if(userN.isEmpty() || pass.isEmpty()) {
        message->setText("Please Fill Every Field");
        message->show();
        return - 1;
    }

    if(userN.contains(QRegularExpression("\\W"))) {
        message->setText("Username Invalid.\nOnly letters, numbers and underscore");
        message->show();
        return -1;
    }

    if(QString::compare(pass, passR, Qt::CaseSensitive) != 0) {
        message->setText("Passwords don't match!");
        message->show();
        return -1;
    }

    switch (evaluatePasswordStrength(pass)) {
    case -1:
        message->setText("Password is too Short");
        message->show();
        return -1;
    case -2:
        message->setText("Password must contain lowercase & uppercase characters");
        message->show();
        return -1;
    case -3:
        message->setText("Password must contain numbers");
        message->show();
        return -1;
    case -4:
        message->setText("Password must contain special characters");
        message->show();
        return -1;
    default:
        break;
    }

    return 0;
}

int LoginWindow::evaluatePasswordStrength(const QString &pass)
{
    static QRegularExpression regEx;
    if (pass.length() < 8) {
        return - 1;
    }
    if (QString::compare(pass, pass.toLower(), Qt::CaseSensitive) == 0) {
        return - 2;
    }
    regEx.setPattern(R"([0-9])");
    if (!pass.contains(regEx)) {
        return - 3;
    }
    regEx.setPattern(R"([ !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~0-9])");
    if (!pass.contains(regEx)) {
        return - 4;
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

