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
