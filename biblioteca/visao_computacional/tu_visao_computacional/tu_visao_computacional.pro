#-------------------------------------------------
#
# Project created by QtCreator 2020-09-12T17:32:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_tu_visao_computacionaltest
CONFIG   += console
CONFIG   -= app_bundle

LIBS += C:\ethowatcher\biblioteca\visao_computacional\build-visao_computacional-Desktop_Qt_5_3_MinGW_32bit-Debug\debug\visao_computacional.dll

INCLUDEPATH += C:\opencv\RELEASE\install\include
LIBS += C:\opencv\RELEASE\bin\libopencv_calib3d2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_contrib2411.dll

TEMPLATE = app


SOURCES += tst_tu_visao_computacionaltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    visao_computacional.h \
    visao_computacional_global.h

