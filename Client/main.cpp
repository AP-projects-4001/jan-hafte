#include "loginwindow.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow m;
    m.show();

    //LoginWindow l;
    //l.show();


    return a.exec();
}
