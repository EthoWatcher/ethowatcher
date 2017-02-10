#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T23:49:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaConcordancia
TEMPLATE = app


SOURCES += ProjetoConcordancia/main.cpp\
       # ProjetoConcordancia/mainwindow.cpp\
        teaconcordancia.cpp \
    emuladortelaconcordancia.cpp\
    parserxmltocsv.cpp


HEADERS  += teaconcordancia.h \
    emuladortelaconcordancia.h\
    parserxmltocsv.h

    #ProjetoConcordancia/mainwindow.h\

FORMS    += teaconcordancia.ui \
    emuladortelaconcordancia.ui

#ProjetoConcordancia/mainwindow.ui\
