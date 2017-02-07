#ifndef EMULADORVERDADEIROREALTIME_H
#define EMULADORVERDADEIROREALTIME_H

#include <QWidget>
#include "telatemporeal.h"
namespace Ui {
class EmuladorVerdadeiroRealTime;
}

class EmuladorVerdadeiroRealTime : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorVerdadeiroRealTime(QWidget *parent = 0);
    ~EmuladorVerdadeiroRealTime();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorVerdadeiroRealTime *ui;
    telaTempoReal *tempoReal;
    telaTempoReal *tempoReal1;
    telaTempoReal *tempoReal2;
    std::vector<telaTempoReal *> vetorTempoReal;
    int contTela=0;
};

#endif // EMULADORVERDADEIROREALTIME_H



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
