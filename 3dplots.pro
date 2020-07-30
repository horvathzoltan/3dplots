QT       += core gui datavisualization network

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

CONFIG(debug, debug|release){
BUILD = debug
} else {
BUILD = release
}

equals(BUILD,debug) {
    #message( "build is _ debug" )
    COMMON_LIBS = $$COMMON_LIBS"_debug"
}
#equals(BUILD,release) {
#    #message( "build is _ release" )
#}

!contains(QMAKE_TARGET.arch, x86_64) {
    COMMON_LIBS = $$COMMON_LIBS"_32"
}

# INSTALLDIR = $$COMMON_LIBS
COMMON_LIBS_FULLPATH = $$shell_path($$HOME/$$COMMON_LIBS)

message("COMMON_LIBS_FULLPATH="$$COMMON_LIBS_FULLPATH)

#unix:!macx: LIBS += -L/home/zoli/build-common-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper/ -lstringhelper
unix:!macx:
{
LIBS += -L$$COMMON_LIBS_FULLPATH/ -llogger
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lsignalhelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lCommandLineParserHelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lcoreappworker
#LIBS += -L$COMMON_LIBS_FULLPATH/ -lstringhelper
#LIBS += -L$COMMON_LIBS_FULLPATH/ -lfilehelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lmacrofactory
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lshortguid
#LIBS += -L$COMMON_LIBS_FULLPATH/ -linihelper
#LIBS += -L$COMMON_LIBS_FULLPATH/ -lsettingshelper
#LIBS += -L$COMMON_LIBS_FULLPATH/ -lxmlhelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -ltextfilehelper
}

INCLUDEPATH += $$HOME/common
DEPENDPATH += $$HOME/common

message(includepath = $$INCLUDEPATH)

SOURCES += \
    action.cpp \
    actionhelper.cpp \
    actiontask.cpp \
    dowork.cpp \
    httpthreadedserver.cpp \
    main.cpp \
    mainwindow.cpp \
    request.cpp \
    response.cpp \
    scatterhelper.cpp \
    threadedsockethandler.cpp \
    work1.cpp

HEADERS += \
    action.h \
    actionhelper.h \
    actiontask.h \
    dowork.h \
    httpthreadedserver.h \
    mainwindow.h \
    request.h \
    response.h \
    scatterhelper.h \
    threadedsockethandler.h \
    work1.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target