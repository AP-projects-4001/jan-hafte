#ifndef UTILITIES_H
#define UTILITIES_H

#include <QMessageBox>
#include "changepropertydialog.h"
#include <QPixmap>
#include <QImage>
#include <QBrush>
#include <QPainter>
#include <QWindow>
#include <QBuffer>

class Utilities
{
public:
    Utilities();
    static void setUpPopUpMessage(QMessageBox *message);
    static void setUpTextEditDialog (ChangePropertyDialog *main, QLabel* label, QLineEdit *lineEdit, QString lineEditPlaceholder, QPushButton *button);
    static QPixmap maskImage (QImage image, int size = 64);
    static QImage createPixBasedOnName(QString name);
    static QString imageToString(const QImage &image);
    static QImage stringToImage(const QString& str);
};

#endif // UTILITIES_H
