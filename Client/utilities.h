#ifndef UTILITIES_H
#define UTILITIES_H

#include <QMessageBox>
#include "changepropertydialog.h"

class Utilities
{
public:
    Utilities();
    static void setUpPopUpMessage(QMessageBox *message);
    static void setUpTextEditDialog (ChangePropertyDialog *main, QLabel* label, QLineEdit *lineEdit, QString lineEditPlaceholder, QPushButton *button);
};

#endif // UTILITIES_H
