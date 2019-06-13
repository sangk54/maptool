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
    camera/marker.cpp \
    camera/markermanager.cpp

HEADERS  += mainwindow.h \
    drawablewidget.h \
    camera/camera.h \
    camera/marker.h \
    camera/markermanager.h

FORMS    += mainwindow.ui \
    drawablewidget.ui

RESOURCES += \
    resources.qrc

OBJECTS_DIR = obj
MOC_DIR = moc
UI_DIR = ui
