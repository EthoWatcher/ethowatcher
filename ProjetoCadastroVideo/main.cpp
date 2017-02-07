//#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "emuladrocadastrovideo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<"tela cadastro video";
   // MainWindow w;
    //w.show();
    EmuladroCadastroVideo w;
    w.show();

    return a.exec();
}


//INCLUDEPATH += C:\opencv\RELEASE\install\include
//LIBS += C:\opencv\RELEASE\bin\libopencv_calib3d320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_core320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_features2d320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_flann320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_highgui320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_imgproc320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_ml320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_objdetect320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_photo320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_shape320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_stitching320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_superres320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_video320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_videoio320.dll
//LIBS += C:\opencv\RELEASE\bin\libopencv_videostab320.dll
//LIBS += C:\opencv\RELEASE\bin\opencv_ffmpeg320.dll
