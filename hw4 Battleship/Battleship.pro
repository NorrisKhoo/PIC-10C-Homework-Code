#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T20:05:45
#
#-------------------------------------------------

QT       += core gui

QT       += core gui multimedia

QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Battleship
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    gameboard.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
