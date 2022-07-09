#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QFrame>
#include <QSpacerItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>

class MessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = nullptr, bool isSender = true, QString text = "", QString name = "" , QDateTime time = QDateTime());

    void setText(const QString text);

signals:

private:
    QFrame *messageFrame;
    QSpacerItem *horizontalSpacer;
    QLabel *messageText;

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    QString message;
    QDateTime time;
};

#endif // MESSAGEBOX_H
