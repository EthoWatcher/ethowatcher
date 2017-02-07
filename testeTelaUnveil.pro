#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T19:05:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaUnveil
TEMPLATE = app


SOURCES += ProjetoCegoUnveil/main.cpp\
#        ProjetoCegoUnveil/mainwindow.cpp \
    telaunveil.cpp\
    modulorsa.cpp \
    emuladorunveil.cpp

HEADERS  += telaunveil.h\
    modulorsa.h \
    emuladorunveil.h
#ProjetoCegoUnveil/mainwindow.h \


FORMS    += telaunveil.ui \
    emuladorunveil.ui
# ProjetoCegoUnveil/mainwindow.ui \

