#ifndef CHATLABLE_H
#define CHATLABLE_H

#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QMouseEvent>
#include <QStyle>

class ChatLable : public QFrame
{
    Q_OBJECT
public:
    explicit ChatLable(QWidget *parent = nullptr, bool lastMessage = true, bool isCheckable = false);
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);
    void setChecked(bool val);
    void setCheckable (bool val);

signals:
    void click();
    void release();

private slots:

    void OnLableClick();
    void OnLableRelease();

private:
    QLabel *nameField;
    QLabel *lastMessageField;
    QLabel *profilePicSlot;

    bool showsLastMessage = true;
    bool isCheckable = false;
    bool isChecked = false;
};

#endif // CHATLABLE_H
