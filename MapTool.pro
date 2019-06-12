#-------------------------------------------------
#
# Project created by QtCreator 2019-06-11T22:57:14
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawablewidget.cpp \
    camera/camera.cpp \
    camera/marker.cpp

HEADERS  += mainwindow.h \
    drawablewidget.h \
    camera/camera.h \
    camera/marker.h

FORMS    += mainwindow.ui \
    drawablewidget.ui

RESOURCES += \
    resources.qrc
