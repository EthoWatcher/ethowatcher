#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T01:20:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaEtografia
TEMPLATE = app

INCLUDEPATH += C:\opencv\RELEASE\install\include
LIBS += C:\opencv\RELEASE\bin\libopencv_calib3d2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_contrib2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_core2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_features2d2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_flann2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_gpu2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_highgui2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_imgproc2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_legacy2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_ml2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_nonfree2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_objdetect2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_ocl2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_photo2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_stitching2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_superres2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_video2411.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_videostab2411.dll



SOURCES += ProjetoEtografia/main.cpp\
        ProjetoEtografia/mainwindow.cpp \
        telaetografia.cpp\
        etografia.cpp\
        modulorsa.cpp\
        moduloprocessamento.cpp \
        telaetografiaproce.cpp\
         modulocaptador.cpp
    #ethowatcheros.cpp \
    #ProjetoEtografia/areatraingulo.cpp
    #../estruturas.cpp



HEADERS  += ProjetoEtografia/mainwindow.h \
        telaetografia.h\
        etografia.h\
        modulorsa.h\
        moduloprocessamento.h \
        telaetografiaproce.h \
        modulocaptador.h
    #ethowatcheros.h \
   # ProjetoEtografia/areatraingulo.h


FORMS    += ProjetoEtografia/mainwindow.ui \
    telaetografia.ui\
        etografia.ui \
    telaetografiaproce.ui

RESOURCES += \
    resourcefile.qrc
