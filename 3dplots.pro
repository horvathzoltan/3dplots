QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

message(QMAKE_PLATFORM: $$QMAKE_PLATFORM)
message(QMAKE_COMPILER: $$QMAKE_COMPILER)
message(QMAKE_COMPILER_DEFINES: $$QMAKE_COMPILER_DEFINES)
message(MAKEFILE_GENERATOR: $$MAKEFILE_GENERATOR)

mingw: message(MINGW)
msvc: message(MSVC)

CONFIG += c++1z
msvc:QMAKE_CXXFLAGS += /std:c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:HOME = $$system(echo $HOME)
win32:HOME = $$system(echo %userprofile%)

COMMON_LIBS = commonlib

#unix:!macx: LIBS += -L/home/zoli/build-common-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper/ -lstringhelper
unix:!macx:
{
LIBS += -L$$HOME/$$COMMON_LIBS/ -llogger
LIBS += -L$$HOME/$$COMMON_LIBS/ -lsignalhelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lCommandLineParserHelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lcoreappworker
#LIBS += -L$$HOME/$$COMMON_LIBS/ -lstringhelper
#LIBS += -L$$HOME/$$COMMON_LIBS/ -lfilehelper
LIBS += -L$$HOME/$$COMMON_LIBS/ -lmacrofactory
LIBS += -L$$HOME/$$COMMON_LIBS/ -lshortguid
#LIBS += -L$$HOME/$$COMMON_LIBS/ -linihelper
#LIBS += -L$$HOME/$$COMMON_LIBS/ -lsettingshelper
#LIBS += -L$$HOME/$$COMMON_LIBS/ -lxmlhelper
}

INCLUDEPATH += $$HOME/common
DEPENDPATH += $$HOME/common

message(includepath = $$INCLUDEPATH)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    work1.cpp

HEADERS += \
    mainwindow.h \
    work1.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
