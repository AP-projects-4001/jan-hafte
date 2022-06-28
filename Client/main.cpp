#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow* l = new LoginWindow();
    l->show();

    int res = l->exec();

    MainWindow m;
    m.show();

    return a.exec();
}
