#-------------------------------------------------
#
# Project created by QtCreator 2017-01-30T12:26:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaMatrisTransicao
TEMPLATE = app


SOURCES += ProjetoMatrizTransicao/main.cpp\
        ProjetoMatrizTransicao/mainwindow.cpp\
        figuramatriz.cpp\
        itemcirculo.cpp\
        itemcompostaseta.cpp\
        itemnovaseta.cpp\
        telamatriztransicao.cpp\
        parserxmltocsv.cpp

HEADERS  += ProjetoMatrizTransicao/mainwindow.h\
            figuramatriz.h\
            itemcirculo.h\
            itemcompostaseta.h\
            itemnovaseta.h\
            telamatriztransicao.h\
            parserxmltocsv.h


FORMS    += ProjetoMatrizTransicao/mainwindow.ui\
            figuramatriz.ui\
            telamatriztransicao.ui

RESOURCES += \
    resourcefile.qrc




