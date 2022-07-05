#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow l;
    int res = l.exec();

    MainWindow m;
    m.show();

    return a.exec();
}
