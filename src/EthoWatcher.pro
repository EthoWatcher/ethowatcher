#-------------------------------------------------
#
#
# EthoWatcher OS is a software to assist study of animal behavior.
# Copyright (C) 2018  Universidade Federal de Santa Catarina.

# EthoWatcher OS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
# Project created by QtCreator 2016-04-20T18:37:51
#
#-------------------------------------------------
#include(QtXlsx/src/xlsx/qtxlsx.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EthoWatcher
TEMPLATE = app

DEFINES += XLSX_NO_LIB

CONFIG += c++11

INCLUDEPATH += C:\opencv4_7\RELEASE\include
LIBS += C:\opencv4_7\RELEASE\bin\libopencv_core470.dll
LIBS += C:\opencv4_7\RELEASE\bin\libopencv_highgui470.dll
LIBS += C:\opencv4_7\RELEASE\bin\libopencv_imgcodecs470.dll
LIBS += C:\opencv4_7\RELEASE\bin\libopencv_imgproc470.dll
LIBS += C:\opencv4_7\RELEASE\bin\libopencv_videoio470.dll
LIBS += C:\opencv4_7\RELEASE\bin\libopencv_video470.dll

#INCLUDEPATH += C:\opencv\RELEASE\install\include
#LIBS += C:\opencv\RELEASE\bin\libopencv_calib3d2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_contrib2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_core2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_features2d2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_flann2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_gpu2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_highgui2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_imgproc2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_legacy2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_ml2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_nonfree2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_objdetect2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_ocl2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_photo2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_stitching2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_superres2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_video2411.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_videostab2411.dll

# agreement report
#INCLUDEPATH += $$PWD/../Agreement
#DEPENDPATH += $$PWD/../Agreement

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Agreement/release/ -l Agreement
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Agreement/debug/ -l Agreement
#else:unix: LIBS += -L$$PWD/../build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/ -lAgreement



SOURCES += ProjetoEthowatcher/main.cpp\
    ethowatcher.cpp \
    telacadastropessoa.cpp \
    telacadastrofilme.cpp\
    areatraingulo.cpp\
    itemareainte.cpp\
    telacadastrolistafilme.cpp\
    modulocaptador.cpp\
    telacego.cpp\
    telablind.cpp\
    #telaetografia.cpp\
    #etografia.cpp\
    modulorsa.cpp\
    moduloprocessamento.cpp\
    #telaconversorxmlcsv.cpp\
    telacadastrocatalago.cpp\
    moduloeditavideo.cpp\
    figuramatriz.cpp\
    itemcirculo.cpp\
    itemcompostaseta.cpp\
    itemnovaseta.cpp\
    teaconcordancia.cpp\
    telamatriztransicao.cpp\
    telasegementacao.cpp\
    telaetografiaproce.cpp\
    telaunveil.cpp\
    telatemporeal.cpp\
    telafluxocomportamental.cpp\
    parserxmltocsv.cpp\
#    mysplash.cpp\
    parserxml.cpp\
#    ..\Agreement\ui\Reliability.cpp


HEADERS  += ethowatcher.h\
    telacadastropessoa.h\
    telacadastrofilme.h\
    areatraingulo.h\
    itemareainte.h\
    telacadastrolistafilme.h\
    modulocaptador.h\
    telacego.h\
    telablind.h\
    #telaetografia.h\
    #etografia.h\
    modulorsa.h\
    moduloprocessamento.h\
    #telaconversorxmlcsv.h\
    telacadastrocatalago.h\
    moduloeditavideo.h\
    telasegementacao.h\
    telamatriztransicao.h\
    teaconcordancia.h\
    figuramatriz.h\
    itemnovaseta.h\
    itemcirculo.h\
    itemcompostaseta.h\
    telaetografiaproce.h\
    telaunveil.h\
    telatemporeal.h\
    telafluxocomportamental.h\
    parserxmltocsv.h\
#    mysplash.h\
    parserxml.h\
#    ..\Agreement\ui\Reliability.h



FORMS    += ethowatcher.ui\
    telacadastropessoa.ui\
    telacadastrofilme.ui\
    telacadastrolistafilme.ui\
    telacego.ui\
    telablind.ui\
    #telaetografia.ui\
    #etografia.ui\
    #telaconversorxmlcsv.ui\
    telasegementacao.ui\
    telamatriztransicao.ui\
    teaconcordancia.ui\
    figuramatriz.ui\
    telacadastrocatalago.ui\
    telaetografiaproce.ui\
    telaunveil.ui\
    telatemporeal.ui\
    telafluxocomportamental.ui\
#    ..\Agreement\ui\Reliability.ui




RESOURCES += \
    resourcefile.qrc\
    recursos.qrc

