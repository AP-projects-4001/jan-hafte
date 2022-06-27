/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QWidget *layoutWidget;
    QVBoxLayout *SideGraphics;
    QSpacerItem *verticalSpacer;
    QLabel *Logo;
    QVBoxLayout *Texts;
    QLabel *Lable_JohnHafteh;
    QVBoxLayout *Subtext;
    QLabel *label_FirstLine;
    QLabel *label_secondLine;
    QSpacerItem *verticalSpacer_2;
    QStackedWidget *Pages;
    QWidget *LoginPage;
    QFrame *LoginFrame;
    QWidget *layoutWidget_2;
    QVBoxLayout *LoginArea;
    QLabel *Lable_Username;
    QLineEdit *lineEdit_Username;
    QLabel *Lable_Password;
    QLineEdit *lineEdit_Password;
    QPushButton *SignUpInsteadButton;
    QSpacerItem *verticalSpacer_4;
    QPushButton *LoginButton;
    QLabel *Header;
    QWidget *SignUpPage;
    QFrame *SignUpFrame;
    QWidget *layoutWidget_5;
    QVBoxLayout *SignUpArea;
    QLabel *Lable_Username_New;
    QLineEdit *lineEdit_UsernameNew;
    QLabel *Lable_Password_New;
    QLineEdit *lineEdit_PasswordNew;
    QLineEdit *lineEdit_PasswordReenter;
    QPushButton *LoginInsteadButton;
    QSpacerItem *verticalSpacer_7;
    QPushButton *SignUpButton;
    QLabel *Header_3;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        LoginWindow->setMinimumSize(QSize(800, 600));
        LoginWindow->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/Graphics/Artboard 1@64x.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginWindow->setWindowIcon(icon);
        LoginWindow->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border-radius: 20px;\n"
"border-style: solid;\n"
"border-width: 2px;\n"
"border-color: #9d9d9d;\n"
"padding-left : 20px;\n"
"}"));
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(LoginWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(true);
        widget->setStyleSheet(QString::fromUtf8("background: white;\n"
"\n"
""));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 90, 184, 401));
        SideGraphics = new QVBoxLayout(layoutWidget);
        SideGraphics->setSpacing(10);
        SideGraphics->setObjectName(QString::fromUtf8("SideGraphics"));
        SideGraphics->setSizeConstraint(QLayout::SetFixedSize);
        SideGraphics->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        SideGraphics->addItem(verticalSpacer);

        Logo = new QLabel(layoutWidget);
        Logo->setObjectName(QString::fromUtf8("Logo"));
        Logo->setStyleSheet(QString::fromUtf8(""));
        Logo->setPixmap(QPixmap(QString::fromUtf8(":/Graphics/Graphics/AP_Icon.svg")));
        Logo->setScaledContents(false);
        Logo->setAlignment(Qt::AlignCenter);
        Logo->setWordWrap(false);
        Logo->setMargin(0);
        Logo->setIndent(-1);
        Logo->setOpenExternalLinks(false);

        SideGraphics->addWidget(Logo);

        Texts = new QVBoxLayout();
        Texts->setSpacing(8);
        Texts->setObjectName(QString::fromUtf8("Texts"));
        Texts->setContentsMargins(-1, -1, -1, 0);
        Lable_JohnHafteh = new QLabel(layoutWidget);
        Lable_JohnHafteh->setObjectName(QString::fromUtf8("Lable_JohnHafteh"));
        Lable_JohnHafteh->setStyleSheet(QString::fromUtf8("font: 800 25pt \"Helvetica Now Display\";"));
        Lable_JohnHafteh->setAlignment(Qt::AlignCenter);

        Texts->addWidget(Lable_JohnHafteh);

        Subtext = new QVBoxLayout();
        Subtext->setSpacing(0);
        Subtext->setObjectName(QString::fromUtf8("Subtext"));
        Subtext->setContentsMargins(-1, 0, -1, 0);
        label_FirstLine = new QLabel(layoutWidget);
        label_FirstLine->setObjectName(QString::fromUtf8("label_FirstLine"));
        label_FirstLine->setStyleSheet(QString::fromUtf8("font: 400 13pt \"Helvetica Now Display\";"));
        label_FirstLine->setLineWidth(0);
        label_FirstLine->setMidLineWidth(0);
        label_FirstLine->setTextFormat(Qt::RichText);
        label_FirstLine->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_FirstLine->setWordWrap(false);
        label_FirstLine->setMargin(-1);
        label_FirstLine->setIndent(-1);

        Subtext->addWidget(label_FirstLine);

        label_secondLine = new QLabel(layoutWidget);
        label_secondLine->setObjectName(QString::fromUtf8("label_secondLine"));
        label_secondLine->setStyleSheet(QString::fromUtf8("font: 400 13pt \"Helvetica Now Display\";"));
        label_secondLine->setLineWidth(0);
        label_secondLine->setMidLineWidth(0);
        label_secondLine->setTextFormat(Qt::RichText);
        label_secondLine->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_secondLine->setWordWrap(false);
        label_secondLine->setMargin(-1);
        label_secondLine->setIndent(-1);

        Subtext->addWidget(label_secondLine);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Subtext->addItem(verticalSpacer_2);


        Texts->addLayout(Subtext);


        SideGraphics->addLayout(Texts);

        Pages = new QStackedWidget(widget);
        Pages->setObjectName(QString::fromUtf8("Pages"));
        Pages->setGeometry(QRect(300, 0, 500, 600));
        LoginPage = new QWidget();
        LoginPage->setObjectName(QString::fromUtf8("LoginPage"));
        LoginFrame = new QFrame(LoginPage);
        LoginFrame->setObjectName(QString::fromUtf8("LoginFrame"));
        LoginFrame->setEnabled(true);
        LoginFrame->setGeometry(QRect(10, 90, 331, 401));
        LoginFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"border-radius: 20px;\n"
"border-style: solid;\n"
"border-width: 2px;\n"
"border-color: #9d9d9d;\n"
"}"));
        LoginFrame->setFrameShape(QFrame::StyledPanel);
        LoginFrame->setFrameShadow(QFrame::Raised);
        layoutWidget_2 = new QWidget(LoginFrame);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 80, 291, 301));
        LoginArea = new QVBoxLayout(layoutWidget_2);
        LoginArea->setObjectName(QString::fromUtf8("LoginArea"));
        LoginArea->setContentsMargins(0, 0, 0, 0);
        Lable_Username = new QLabel(layoutWidget_2);
        Lable_Username->setObjectName(QString::fromUtf8("Lable_Username"));
        Lable_Username->setEnabled(true);
        Lable_Username->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"border-width: 0px;\n"
"font: 500 12pt \"Helvetica Now Display\";\n"
"padding-left: 5px;"));
        Lable_Username->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        LoginArea->addWidget(Lable_Username);

        lineEdit_Username = new QLineEdit(layoutWidget_2);
        lineEdit_Username->setObjectName(QString::fromUtf8("lineEdit_Username"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_Username->sizePolicy().hasHeightForWidth());
        lineEdit_Username->setSizePolicy(sizePolicy1);
        lineEdit_Username->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Helvetica Now Display")});
        font.setPointSize(11);
        lineEdit_Username->setFont(font);
        lineEdit_Username->setStyleSheet(QString::fromUtf8(""));
        lineEdit_Username->setFrame(true);
        lineEdit_Username->setCursorPosition(0);

        LoginArea->addWidget(lineEdit_Username);

        Lable_Password = new QLabel(layoutWidget_2);
        Lable_Password->setObjectName(QString::fromUtf8("Lable_Password"));
        Lable_Password->setEnabled(true);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Helvetica Now Display")});
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        Lable_Password->setFont(font1);
        Lable_Password->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"border-width: 0px;\n"
"font: 500 12pt \"Helvetica Now Display\";\n"
"padding-left: 5px;"));
        Lable_Password->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        LoginArea->addWidget(Lable_Password);

        lineEdit_Password = new QLineEdit(layoutWidget_2);
        lineEdit_Password->setObjectName(QString::fromUtf8("lineEdit_Password"));
        sizePolicy1.setHeightForWidth(lineEdit_Password->sizePolicy().hasHeightForWidth());
        lineEdit_Password->setSizePolicy(sizePolicy1);
        lineEdit_Password->setMinimumSize(QSize(0, 40));
        lineEdit_Password->setFont(font);
        lineEdit_Password->setStyleSheet(QString::fromUtf8(""));
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        LoginArea->addWidget(lineEdit_Password);

        SignUpInsteadButton = new QPushButton(layoutWidget_2);
        SignUpInsteadButton->setObjectName(QString::fromUtf8("SignUpInsteadButton"));
        SignUpInsteadButton->setMinimumSize(QSize(0, 30));
        SignUpInsteadButton->setCursor(QCursor(Qt::PointingHandCursor));
        SignUpInsteadButton->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"opacity: 1;\n"
"font: 500 12pt \"Helvetica Now Display\";\n"
"text-decoration: underline;\n"
"color:#956cec;\n"
"\n"
"\n"
""));

        LoginArea->addWidget(SignUpInsteadButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        LoginArea->addItem(verticalSpacer_4);

        LoginButton = new QPushButton(layoutWidget_2);
        LoginButton->setObjectName(QString::fromUtf8("LoginButton"));
        LoginButton->setMinimumSize(QSize(0, 60));
        LoginButton->setCursor(QCursor(Qt::PointingHandCursor));
        LoginButton->setStyleSheet(QString::fromUtf8("border-radius: 12px;\n"
"background: #956cec;\n"
"font: 800 18pt \"Helvetica Now Display\";\n"
"color: white;\n"
""));
        LoginButton->setAutoDefault(true);

        LoginArea->addWidget(LoginButton);

        Header = new QLabel(LoginPage);
        Header->setObjectName(QString::fromUtf8("Header"));
        Header->setGeometry(QRect(30, 65, 90, 51));
        Header->setStyleSheet(QString::fromUtf8("font: 800 24pt \"Helvetica Now Display\";"));
        Header->setFrameShape(QFrame::NoFrame);
        Header->setAlignment(Qt::AlignCenter);
        Pages->addWidget(LoginPage);
        SignUpPage = new QWidget();
        SignUpPage->setObjectName(QString::fromUtf8("SignUpPage"));
        SignUpFrame = new QFrame(SignUpPage);
        SignUpFrame->setObjectName(QString::fromUtf8("SignUpFrame"));
        SignUpFrame->setEnabled(true);
        SignUpFrame->setGeometry(QRect(10, 90, 331, 401));
        SignUpFrame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"border-radius: 20px;\n"
"border-style: solid;\n"
"border-width: 2px;\n"
"border-color: #9d9d9d;\n"
"}"));
        SignUpFrame->setFrameShape(QFrame::StyledPanel);
        SignUpFrame->setFrameShadow(QFrame::Raised);
        layoutWidget_5 = new QWidget(SignUpFrame);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 80, 291, 301));
        SignUpArea = new QVBoxLayout(layoutWidget_5);
        SignUpArea->setObjectName(QString::fromUtf8("SignUpArea"));
        SignUpArea->setContentsMargins(0, 0, 0, 0);
        Lable_Username_New = new QLabel(layoutWidget_5);
        Lable_Username_New->setObjectName(QString::fromUtf8("Lable_Username_New"));
        Lable_Username_New->setEnabled(true);
        Lable_Username_New->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"border-width: 0px;\n"
"font: 500 12pt \"Helvetica Now Display\";\n"
"padding-left: 5px;"));
        Lable_Username_New->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        SignUpArea->addWidget(Lable_Username_New);

        lineEdit_UsernameNew = new QLineEdit(layoutWidget_5);
        lineEdit_UsernameNew->setObjectName(QString::fromUtf8("lineEdit_UsernameNew"));
        sizePolicy1.setHeightForWidth(lineEdit_UsernameNew->sizePolicy().hasHeightForWidth());
        lineEdit_UsernameNew->setSizePolicy(sizePolicy1);
        lineEdit_UsernameNew->setMinimumSize(QSize(0, 40));
        lineEdit_UsernameNew->setFont(font);
        lineEdit_UsernameNew->setStyleSheet(QString::fromUtf8(""));
        lineEdit_UsernameNew->setFrame(true);
        lineEdit_UsernameNew->setCursorPosition(0);

        SignUpArea->addWidget(lineEdit_UsernameNew);

        Lable_Password_New = new QLabel(layoutWidget_5);
        Lable_Password_New->setObjectName(QString::fromUtf8("Lable_Password_New"));
        Lable_Password_New->setEnabled(true);
        Lable_Password_New->setFont(font1);
        Lable_Password_New->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"border-width: 0px;\n"
"font: 500 12pt \"Helvetica Now Display\";\n"
"padding-left: 5px;"));
        Lable_Password_New->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        SignUpArea->addWidget(Lable_Password_New);

        lineEdit_PasswordNew = new QLineEdit(layoutWidget_5);
        lineEdit_PasswordNew->setObjectName(QString::fromUtf8("lineEdit_PasswordNew"));
        sizePolicy1.setHeightForWidth(lineEdit_PasswordNew->sizePolicy().hasHeightForWidth());
        lineEdit_PasswordNew->setSizePolicy(sizePolicy1);
        lineEdit_PasswordNew->setMinimumSize(QSize(0, 40));
        lineEdit_PasswordNew->setFont(font);
        lineEdit_PasswordNew->setStyleSheet(QString::fromUtf8(""));
        lineEdit_PasswordNew->setEchoMode(QLineEdit::Password);

        SignUpArea->addWidget(lineEdit_PasswordNew);

        lineEdit_PasswordReenter = new QLineEdit(layoutWidget_5);
        lineEdit_PasswordReenter->setObjectName(QString::fromUtf8("lineEdit_PasswordReenter"));
        sizePolicy1.setHeightForWidth(lineEdit_PasswordReenter->sizePolicy().hasHeightForWidth());
        lineEdit_PasswordReenter->setSizePolicy(sizePolicy1);
        lineEdit_PasswordReenter->setMinimumSize(QSize(0, 40));
        lineEdit_PasswordReenter->setFont(font);
        lineEdit_PasswordReenter->setStyleSheet(QString::fromUtf8(""));
        lineEdit_PasswordReenter->setEchoMode(QLineEdit::Password);

        SignUpArea->addWidget(lineEdit_PasswordReenter);

        LoginInsteadButton = new QPushButton(layoutWidget_5);
        LoginInsteadButton->setObjectName(QString::fromUtf8("LoginInsteadButton"));
        LoginInsteadButton->setMinimumSize(QSize(0, 30));
        LoginInsteadButton->setCursor(QCursor(Qt::PointingHandCursor));
        LoginInsteadButton->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"opacity: 1;\n"
"font: 500 12pt \"Helvetica Now Display\";\n"
"text-decoration: underline;\n"
"color:#956cec;\n"
"\n"
"\n"
""));

        SignUpArea->addWidget(LoginInsteadButton);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        SignUpArea->addItem(verticalSpacer_7);

        SignUpButton = new QPushButton(layoutWidget_5);
        SignUpButton->setObjectName(QString::fromUtf8("SignUpButton"));
        SignUpButton->setMinimumSize(QSize(0, 60));
        SignUpButton->setCursor(QCursor(Qt::PointingHandCursor));
        SignUpButton->setStyleSheet(QString::fromUtf8("border-radius: 12px;\n"
"background: #956cec;\n"
"font: 800 18pt \"Helvetica Now Display\";\n"
"color: white;\n"
""));
        SignUpButton->setAutoDefault(true);

        SignUpArea->addWidget(SignUpButton);

        Header_3 = new QLabel(SignUpPage);
        Header_3->setObjectName(QString::fromUtf8("Header_3"));
        Header_3->setGeometry(QRect(30, 65, 125, 51));
        Header_3->setStyleSheet(QString::fromUtf8("font: 800 24pt \"Helvetica Now Display\";"));
        Header_3->setAlignment(Qt::AlignCenter);
        Pages->addWidget(SignUpPage);

        verticalLayout->addWidget(widget);


        retranslateUi(LoginWindow);

        Pages->setCurrentIndex(0);
        LoginButton->setDefault(false);
        SignUpButton->setDefault(false);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        Logo->setText(QString());
        Lable_JohnHafteh->setText(QCoreApplication::translate("LoginWindow", "Jan Hafteh", nullptr));
        label_FirstLine->setText(QCoreApplication::translate("LoginWindow", "<html><head/><body><p align=\"center\">The <span style=\" font-weight:700;\">most</span> trusted name</p></body></html>", nullptr));
        label_secondLine->setText(QCoreApplication::translate("LoginWindow", "<html><head/><body><p align=\"center\">among massaging apps</p></body></html>", nullptr));
        Lable_Username->setText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        lineEdit_Username->setText(QString());
        lineEdit_Username->setPlaceholderText(QString());
        Lable_Password->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        SignUpInsteadButton->setText(QCoreApplication::translate("LoginWindow", "Sign Up Instead", nullptr));
        LoginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        LoginButton->setProperty("fd", QVariant(QString()));
        Header->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        Lable_Username_New->setText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        lineEdit_UsernameNew->setText(QString());
        lineEdit_UsernameNew->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Set a username", nullptr));
        Lable_Password_New->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        lineEdit_PasswordNew->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter a secure password", nullptr));
        lineEdit_PasswordReenter->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Reenter the password", nullptr));
        LoginInsteadButton->setText(QCoreApplication::translate("LoginWindow", "LogIn Instead", nullptr));
        SignUpButton->setText(QCoreApplication::translate("LoginWindow", "Sign Up", nullptr));
        Header_3->setText(QCoreApplication::translate("LoginWindow", "Sign Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
