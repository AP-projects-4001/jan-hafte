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

    //MyThread *thread = new MyThread();
    e = new myClient();
    e->connectingToServer();
    connect(e, SIGNAL(recievemessage(QJsonObject)), this, SLOT(getdata(QJsonObject)));

}

void LoginWindow::getdata(QJsonObject data)
{
    if (data["header"]=="login") {
        QString status = data["status"].toString();

        if (status == "valid") {
            emit loginDone(data["username"].toString());
            close();
        }
        else if (status == "not valid"){
            message->setText("Log In Failed");  // delete this
            message->show();
        }
        else{
            message->setText("Error");  // delete this
            message->show();
        }
    }

    else if (data["header"] == "register"){
        QString status = data["status"].toString();

        if (status == "valid"){
            message->setText("Successfully Signed In");  // delete this
            message->exec();
            emit loginDone(data["username"].toString());
            close();
        }
        else if (status == "not valid"){
            message->setText("Sign Up Failed");  // delete this
            message->show();
        }
        else{
            message->setText("Error");  // delete this
            message->show();
        }
    }

    else{
        message->setText("Server Error");  // delete this
        message->show();
    }
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
    e->writedata(d.toJson());

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
    regist["phone"]=inpPhone;
    regist["email"]=inpEmail;
    regist["profile"]= Utilities::imageToString(Utilities::createPixBasedOnName(inpUsername));


    QJsonDocument d(regist);
    e->writedata(d.toJson());
}

int LoginWindow::checkSignUpInputForError(const QString &userN, const QString &pass, const QString &passR, const QString& email, const QString& phone)
{
    if(userN.isEmpty() || pass.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        message->setText("Please Fill Every Field");
        message->show();
        return - 1;
    }

    QString pattern = "\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b";
    QRegularExpression re(pattern, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = re.match(email);

    if(!match.hasMatch()) {
        message->setText("Invalid Email Address");
        message->show();
        return -1;
    }

    if(phone.contains(QRegularExpression("\\D"))) {
        message->setText("Phone number invalid. Only use numbers");
        message->show();
        return -1;
    }

    if(userN.contains(QRegularExpression("\\W"))) {
        message->setText("Username Invalid.Only letters, numbers and underscore");
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
