QT       += core
QT       += gui
QT       += widgets

TEMPLATE = lib
DEFINES += AGREEMENT_LIBRARY

CONFIG += resources_big
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agreement.cpp \
    .\src\bootstrap.cpp \
    .\src\ethowatcher.cpp\
    .\src\concordance.cpp \
    .\src\randcustom.cpp \
    .\src\relatorio_paper.cpp

HEADERS += \
    Agreement_global.h \
    agreement.h \
    .\src\bootstrap.h \
    .\src\ethowatcher.h \
    .\src\concordance.h \
    .\src\randcustom.h \
    .\src\relatorio_paper.h
RESOURCES += \
    .\src\script.qrc

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
