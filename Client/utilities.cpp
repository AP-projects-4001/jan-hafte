#include "utilities.h"

Utilities::Utilities()
{

}

void Utilities::setUpPopUpMessage(QMessageBox *message)
{
    message->setWindowFlags (Qt::Popup | Qt::CustomizeWindowHint);
    message->setStyleSheet("QAbstractButton{border-radius: 15px; font: 800 14pt \"Helvetica Now Display\"; background: #956cec; color:white; min-width:75px; min-height:30px; transition: border-width 2s;}"
                           "QAbstractButton:hover {background: #7152b3;}"
                           "QAbstractButton:pressed {background: white; border: 2px solid #956cec; color: #956cec;}"
                           "QLabel {font: 500 13pt \"Helvetica Now Display\"; margin-top:1ex; padding-right:25px; min-height:25px;}"
                           "QDialog {border: 2px solid #9d9d9d; background: white;}");
}

void Utilities::setUpTextEditDialog(ChangePropertyDialog *main, QLabel *label, QLineEdit *lineEdit, QString lineEditPlaceholder, QPushButton *button)
{
    main->setWindowFlags(Qt::Popup | Qt::CustomizeWindowHint);
    main->setAttribute(Qt::WA_DeleteOnClose);
    main->setMinimumSize(300, 160);

    label->setGeometry(0,0,300,50);
    label->setAlignment(Qt::AlignCenter);
    main->setHeader(label);

    lineEdit->setGeometry(25,50,250,40);
    lineEdit->setPlaceholderText(lineEditPlaceholder);
    main->setLineEdit(lineEdit);

    button->setGeometry(25,100,250,40);
    main->setSubmitButton(button);
}

QPixmap Utilities::maskImage(QImage &image, int size)
{
    image.convertToFormat(QImage::Format_ARGB32);

    int imgsize =  std::min(image.width(), image.height());
    QRect rec((image.width() - imgsize) / 2,(image.height() - imgsize) / 2,imgsize,imgsize);

    image = image.copy(rec);
    QImage out_img = QImage(imgsize, imgsize, QImage::Format_ARGB32);
    out_img.fill(Qt::transparent);

    QBrush brush(image);
    QPainter painter(&out_img);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawEllipse(0, 0, imgsize, imgsize);
    painter.end();

    qreal pr = QWindow().devicePixelRatio();
    QPixmap pm = QPixmap::fromImage(out_img);
    size *= pr;
    pm = pm.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    return pm;
}
