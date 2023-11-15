QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#DEPENDPATH +=   ./3par/agreement/bin
#INCLUDEPATH +=  ./3par/agreement/bin
#LIBS += -L      ./3par/agreement/header


SOURCES += \
    Reliability.cpp \
    main.cpp

HEADERS += \
    Reliability.h

FORMS += \
    Reliability.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../src/build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/release/ -lAgreement
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../src/build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/debug/ -lAgreement
#else:unix: LIBS += -L$$PWD/../src/build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/ -lAgreement

#INCLUDEPATH += $$PWD/../src/Agreement
#DEPENDPATH += $$PWD/../src/Agreement

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Release/release/ -lAgreement
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/debug/ -lAgreement
#else:unix: LIBS += -L$$PWD/../build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/ -lAgreement

#INCLUDEPATH += $$PWD/../Agreement
#DEPENDPATH += $$PWD/../Agreement

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../release/ -lAgreement
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../debug/ -lAgreement
#else:unix: LIBS += -L$$PWD/../build-Agreement-Desktop_Qt_6_1_2_MinGW_64_bit-Debug/ -lAgreement

RESOURCES += \
    props/resource.qrc
