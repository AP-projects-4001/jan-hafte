#include "changepropertydialog.h"

ChangePropertyDialog::ChangePropertyDialog(QWidget *parent)
    : QDialog {parent}
{

}

void ChangePropertyDialog::setHeader(QLabel *label)
{
    header = label;
}

void ChangePropertyDialog::setLineEdit(QLineEdit *lineEdit)
{
    propertyLineEdit = lineEdit;
}

void ChangePropertyDialog::setSubmitButton(QPushButton *button)
{
    submitButton = button;
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitButtonClicked()));
}

void ChangePropertyDialog::submitButtonClicked()
{
    emit(submit(propertyLineEdit->text()));
}
