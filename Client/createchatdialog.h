#ifndef CREATECHATDIALOG_H
#define CREATECHATDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "utilities.h"

namespace Ui {
class CreateChatDialog;
}

class MainWindow;

class CreateChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChatDialog(QWidget *parent = nullptr);
    ~CreateChatDialog();

private slots:
    void on_newChannelButton_clicked();

    void on_newGroupButton_clicked();

    void on_newContactButton_clicked();

    void on_createChannelButton_clicked();

    void on_createGroupButton_clicked();

    void on_MessageContactButton_clicked();

    void on_channelProfilePicButton_clicked();

    void on_contactInfoInput_textChanged(const QString &arg1);

private:
    Ui::CreateChatDialog *ui;
    friend MainWindow;
};

#endif // CREATECHATDIALOG_H
