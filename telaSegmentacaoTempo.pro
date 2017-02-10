#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T16:02:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = telaSegmentacaoTempo
TEMPLATE = app


SOURCES += ProjetoSegmentacaoTempo/main.cpp\
        #ProjetoSegmentacaoTempo/mainwindow.cpp\
        telasegementacao.cpp\
        emuladorsegmentacaotempo.cpp\
        parserxmltocsv.cpp

HEADERS  += telasegementacao.h\
            emuladorsegmentacaotempo.h\
            parserxmltocsv.h
        #ProjetoSegmentacaoTempo/mainwindow.h\

FORMS    += telasegementacao.ui\
            emuladorsegmentacaotempo.ui
    #ProjetoSegmentacaoTempo/mainwindow.ui\
