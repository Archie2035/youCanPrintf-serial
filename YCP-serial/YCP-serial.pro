#-------------------------------------------------
#
# Project created by QtCreator 2015-09-14T11:10:56
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YCP-serial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/serialsetting.cpp

HEADERS  += mainwindow.h \
    src/serialsetting.h \
    src/typedf.h

FORMS    += mainwindow.ui \
    src/serialsetting.ui

RESOURCES += \
    ycp-serial.qrc
