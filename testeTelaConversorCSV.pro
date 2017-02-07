#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T15:44:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaConversorCSV
TEMPLATE = app


SOURCES += ProjetoConversorCSV/main.cpp\
        #ProjetoConversorCSV/mainwindow.cpp \
    telaconversorxmlcsv.cpp \
    parserxmltocsv.cpp\
    emuladorconversor.cpp

HEADERS  += telaconversorxmlcsv.h \
    parserxmltocsv.h\
    emuladorconversor.h
#ProjetoConversorCSV/mainwindow.h \
FORMS    += telaconversorxmlcsv.ui\
    emuladorconversor.ui
# ProjetoConversorCSV/mainwindow.ui \
