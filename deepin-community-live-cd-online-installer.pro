QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 程序版本号
VERSION = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutprogram.cpp \
    diskcontrol.cpp \
    editpartdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    aboutprogram.h \
    diskcontrol.h \
    editpartdialog.h \
    mainwindow.h

FORMS += \
    aboutprogram.ui \
    editpartdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    deepin-community-live-cd-online-installer_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
