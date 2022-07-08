#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "loginhandleutility.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow *l = new LoginWindow;
    LoginHandleUtility lhu(nullptr, l);
    l->exec();

    //if (!lhu.getLoginStat()) { return 0; }

    MainWindow m(nullptr, lhu.getUsername());
    m.show();

    return a.exec();
}
