#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QFrame>
#include <QSpacerItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = nullptr);

    void setText(const QString text);

signals:

private:
    QFrame *messageFrame;
    QSpacerItem *horizontalSpacer;
    QLabel *messageText;

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
};

#endif // MESSAGEBOX_H
