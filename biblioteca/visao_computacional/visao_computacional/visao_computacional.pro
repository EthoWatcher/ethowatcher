#-------------------------------------------------
#
# Project created by QtCreator 2020-09-12T16:49:21
#
#-------------------------------------------------

QT       -= gui

TARGET = visao_computacional
TEMPLATE = lib

DEFINES += VISAO_COMPUTACIONAL_LIBRARY

SOURCES += visao_computacional.cpp

HEADERS += visao_computacional.h\
        visao_computacional_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
