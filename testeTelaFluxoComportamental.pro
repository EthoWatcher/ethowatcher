#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T23:25:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaFluxoComportamental
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

SOURCES += ProjetoFluxoComportamental/main.cpp\
        ProjetoFluxoComportamental/mainwindow.cpp \
    telafluxocomportamental.cpp\
    modulorsa.cpp\
    moduloeditavideo.cpp


HEADERS  += ProjetoFluxoComportamental/mainwindow.h \
    ProjetoFluxoComportamental/telafluxocomportamental.h\
    modulorsa.h\
    moduloeditavideo.h


FORMS    += ProjetoFluxoComportamental/mainwindow.ui \
    telafluxocomportamental.ui
