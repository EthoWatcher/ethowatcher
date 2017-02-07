#-------------------------------------------------
#
# Project created by QtCreator 2016-07-16T21:44:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testeTelaCadastroVideo
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




SOURCES += ProjetoCadastroVideo/main.cpp\
        ProjetoCadastroVideo/mainwindow.cpp \
    modulocaptador.cpp \
    itemareainte.cpp \
    areatraingulo.cpp \
    telacadastrofilme.cpp \
    emuladrocadastrovideo.cpp

HEADERS  += ProjetoCadastroVideo/mainwindow.h \
    modulocaptador.h \
    itemareainte.h \
    areatraingulo.h \
    telacadastrofilme.h \
    emuladrocadastrovideo.h

FORMS    += ProjetoCadastroVideo/mainwindow.ui \
    telacadastrofilme.ui \
    emuladrocadastrovideo.ui

RESOURCES += \
    resourcefile.qrc
