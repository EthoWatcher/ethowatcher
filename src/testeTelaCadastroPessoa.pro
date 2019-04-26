#-------------------------------------------------
#
# Project created by QtCreator 2017-01-30T12:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaCadastroPessoa
TEMPLATE = app


SOURCES += ProjetoCadastroPessoa/main.cpp\
       # ProjetoCadastroPessoa/mainwindow.cpp\
        telacadastropessoa.cpp \
        emuladorcadastropessoa.cpp

HEADERS  +=  telacadastropessoa.h \
             emuladorcadastropessoa.h
#ProjetoCadastroPessoa/mainwindow.h\

FORMS    += telacadastropessoa.ui \
    emuladorcadastropessoa.ui
    #ProjetoCadastroPessoa/mainwindow.ui\

RESOURCES += \
    recursos.qrc

