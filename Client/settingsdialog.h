#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>

#include "changepropertydialog.h"
#include "utilities.h"

namespace Ui {
class SettingsDialog;
}

class MainWindow;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    void setUpData(QString name, QString email, QString phone, QImage profile);
    ~SettingsDialog();

private slots:
    void on_editUsernameButton_clicked();

    void on_editEmailButton_clicked();

    void on_editPhoneButton_clicked();

    void on_addProfileBlacklistButton_clicked();

    void on_addPhoneBlacklistButton_clicked();

public slots:
    void changeUsername(QString newUsername);
    void changePhone(QString newPhone);
    void changeEmail(QString newEmail);
    void changeProfile(QString newProfile);

signals:
    void userNameChangeRequest(QString val);
    void emailChangeRequest(QString val);
    void phoneChangeRequest (QString val);
    void profileChangeRequest (QString val);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
