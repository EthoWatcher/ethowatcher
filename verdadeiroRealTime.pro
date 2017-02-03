#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T14:48:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = verdadeiroRealTime
TEMPLATE = app

INCLUDEPATH += C:\opencv\RELEASE\install\include
LIBS += C:\opencv\RELEASE\bin\libopencv_calib3d320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_core320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_features2d320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_flann320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_highgui320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_imgproc320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_ml320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_objdetect320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_photo320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_shape320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_stitching320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_superres320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_video320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_videoio320.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_videostab320.dll
LIBS += C:\opencv\RELEASE\bin\opencv_ffmpeg320.dll

SOURCES += ProjetoTempoReal/main.cpp\
        ProjetoTempoReal/mainwindow.cpp\
        modulocaptador.cpp \
    telatemporeal.cpp\
    moduloprocessamento.cpp


HEADERS  += ProjetoTempoReal/mainwindow.h\
            modulocaptador.h \
        telatemporeal.h\
        moduloprocessamento.h


FORMS    += mainwindow.ui \
    telatemporeal.ui

