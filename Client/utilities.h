#ifndef UTILITIES_H
#define UTILITIES_H

#include <QMessageBox>
#include "changepropertydialog.h"
#include <QPixmap>
#include <QImage>
#include <QBrush>
#include <QPainter>
#include <QWindow>

class Utilities
{
public:
    Utilities();
    static void setUpPopUpMessage(QMessageBox *message);
    static void setUpTextEditDialog (ChangePropertyDialog *main, QLabel* label, QLineEdit *lineEdit, QString lineEditPlaceholder, QPushButton *button);
    static QPixmap maskImage (QImage &image, int size = 64);
};

#endif // UTILITIES_H
