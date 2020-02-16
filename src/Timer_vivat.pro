#-------------------------------------------------
#
# Project created by QtCreator 2018-11-07T11:44:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Timer_vivat
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
SOURCES += main.cpp\
        timer_vivat.cpp \
    setting.cpp \
    filereader.cpp

HEADERS  += timer_vivat.h \
    setting.h \
    filereader.h
win32:LIBS += libwinmm
FORMS    += \
    timer_vivat.ui \
    setting.ui
