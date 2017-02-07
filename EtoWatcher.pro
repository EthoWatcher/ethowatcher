#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T18:37:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EtoWatcher
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

SOURCES += ProjetoEthowatcher/main.cpp\
    ethowatcher.cpp \
    telacadastropessoa.cpp \
    telacadastrofilme.cpp\
    areatraingulo.cpp\
    itemareainte.cpp\
    telacadastrolistafilme.cpp \
    modulocaptador.cpp\
    telacego.cpp\
    telaetografia.cpp\
    etografia.cpp\
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
    parserxmltocsv.cpp



HEADERS  += ethowatcher.h \
    telacadastropessoa.h \
    telacadastrofilme.h \
    areatraingulo.h \
    itemareainte.h \
    telacadastrolistafilme.h\
    modulocaptador.h\
    telacego.h\
    telaetografia.h\
    etografia.h\
    modulorsa.h\
    moduloprocessamento.h\
    #telaconversorxmlcsv.h\
    telacadastrocatalago.h\
    moduloeditavideo.h\
    telasegementacao.h\
    telamatriztransicao.h \
    teaconcordancia.h\
    figuramatriz.h\
    itemnovaseta.h\
    itemcirculo.h\
    itemcompostaseta.h\
    telaetografiaproce.h\
    telaunveil.h\
    telatemporeal.h\
    telafluxocomportamental.h\
    parserxmltocsv.h



FORMS    += ethowatcher.ui \
    telacadastropessoa.ui \
    telacadastrofilme.ui \
    telacadastrolistafilme.ui \
    telacego.ui\
    telaetografia.ui\
    etografia.ui\
    #telaconversorxmlcsv.ui\
    telasegementacao.ui \
    telamatriztransicao.ui \
    teaconcordancia.ui\
    figuramatriz.ui\
    telacadastrocatalago.ui\
    telaetografiaproce.ui\
    telaunveil.ui\
    telatemporeal.ui\
    telafluxocomportamental.ui


RESOURCES += \
    resourcefile.qrc

