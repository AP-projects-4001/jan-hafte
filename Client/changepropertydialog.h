#ifndef CHANGEPROPERTYDIALOG_H
#define CHANGEPROPERTYDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>

class ChangePropertyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChangePropertyDialog(QWidget *parent = nullptr);
    void setHeader(QLabel *label);
    void setLineEdit(QLineEdit *lineEdit);
    void setSubmitButton (QPushButton *button);
signals:
    void submit();
    void submit(QString value);

public slots:
    void submitButtonClicked();

private:
    QLabel *header;
    QLineEdit *propertyLineEdit;
    QPushButton *submitButton;
};

#endif // CHANGEPROPERTYDIALOG_H
