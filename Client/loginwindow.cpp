#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QRegularExpression>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->LoginButton->setFocus();
    message = new QMessageBox(this);
    Utilities::setUpPopUpMessage(message);

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

}


void LoginWindow::on_SignUpInsteadButton_clicked()
{
    clearLoginPage();
    ui->Pages->setCurrentIndex(1);
    ui->SignUpButton->setFocus();
}


void LoginWindow::on_LoginInsteadButton_clicked()
{
    clearSignUpPage();
    ui->Pages->setCurrentIndex(0);
    ui->LoginButton->setFocus();
}


void LoginWindow::on_SignUpButton_clicked()
{
    QString inpUsername = ui->lineEdit_UsernameNew->text();
    QString inpPassword = ui->lineEdit_PasswordNew->text();
    QString inpPasswordReenter = ui->lineEdit_PasswordReenter->text();
    QString inpEmail = ui->lineEdit_EmailNew->text();
    QString inpPhone = ui->lineEdit_PhoneNew->text();

    int eval = checkSignUpInputForError(inpUsername, inpPassword, inpPasswordReenter, inpEmail, inpPhone);
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
    e.getSocket()->waitForReadyRead(-1);
    QJsonObject data = e.getMsg();
    QString status = data["status"].toString();

    if (status == "valid"){
        QJsonArray content = data["content"].toArray();

        for (auto i = content.begin(); i != content.end(); i++){

            //show on chat screen

        }
        message->setText("Successfully Signed In");
        message->show();
        emit(loginDone());
    }
    else if (status == "not valid"){
        message->setText("Sign Up Failed");
        message->show();
    }
    else{
        message->setText("Error");
        message->show();
    }

}

int LoginWindow::checkSignUpInputForError(const QString &userN, const QString &pass, const QString &passR, const QString& email, const QString& phone)
{
    if(userN.isEmpty() || pass.isEmpty() || email.isEmpty() || phone.isEmpty()) {
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
    ui->lineEdit_EmailNew->clear();
    ui->lineEdit_PhoneNew->clear();
}
