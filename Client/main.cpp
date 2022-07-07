#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "loginhandleutility.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow l;
    LoginHandleUtility lhu;
    QObject::connect(&l, SIGNAL(loginDone()) , &lhu, SLOT(OnLoginSuccessful()));
    l.exec();

    if (!lhu.getLoginStat()) return 0;

    MainWindow m;
    m.show();

    return a.exec();
}
