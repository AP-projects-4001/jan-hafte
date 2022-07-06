QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatlable.cpp \
    createchatdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    messagebox.cpp \
    myclient.cpp \
    loginwindow.cpp \
    mythread.cpp \
    settingsdialog.cpp \
    utilities.cpp

HEADERS += \
    chatlable.h \
    createchatdialog.h \
    mainwindow.h \
    messagebox.h \
    myclient.h \
    loginwindow.h \
    mythread.h \
    settingsdialog.h \
    utilities.h

FORMS += \
    createchatdialog.ui \
    mainwindow.ui \
    myclient.ui \
    loginwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
