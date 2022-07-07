#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "loginhandleutility.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow l;
    LoginHandleUtility lhu(nullptr, &l);
    l.exec();

    //if (!lhu.getLoginStat()) { delete lhu; return 0; }

    MainWindow m;
    m.show();

    return a.exec();
}
