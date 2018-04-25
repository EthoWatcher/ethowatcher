#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T19:15:59
#
#-------------------------------------------------

QT       += core gui
QT +=xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EthoInpi
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


SOURCES += EthoInpi/main.cpp\
        ethoinpi.cpp\
        telacadastrocatalago.cpp \
    botoesinterfaces.cpp \
    interfacedecisao.cpp \
    telacadastrofilme.cpp\
    areatraingulo.cpp\
    itemareainte.cpp\
    modulocaptador.cpp

HEADERS  += ethoinpi.h\
            telacadastrocatalago.h \
    botoesinterfaces.h \
    interfacedecisao.h \
    telacadastrofilme.h\
    areatraingulo.h\
    itemareainte.h\
     modulocaptador.h

FORMS    += ethoinpi.ui\
            telacadastrocatalago.ui\
            telacadastrofilme.ui


