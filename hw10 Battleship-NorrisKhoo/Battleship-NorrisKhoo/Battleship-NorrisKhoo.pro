#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T21:53:09
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Battleship-NorrisKhoo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboardsingleplayer.cpp

HEADERS  += mainwindow.h \
    gameboardsingleplayer.h \
    pointcompare.h

FORMS    += mainwindow.ui \
    gameboardsingleplayer.ui

RESOURCES += \
    resources.qrc
