#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T08:48:26
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent

QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencam
TEMPLATE = app


SOURCES += main.cpp\
        opencam.cpp \
    img_filter.cpp \
    util.cpp \
    picinfo.cpp \
    settingdialog.cpp \
    dataqueue.cpp \
    faceprocess.cpp \
    editwindow.cpp \
    mainwindow.cpp \
    cache.cpp

HEADERS  += opencam.h \
    img_filter.h \
    util.h \
    picinfo.h \
    settingdialog.h \
    dataqueue.h \
    faceprocess.h \
    editwindow.h \
    mainwindow.h \
    cache.h

FORMS    += \
    Opencam.ui \
    settingdialog.ui \
    editwindow.ui \
    mainwindow.ui

INCLUDEPATH += d:\opencv\build\include\
INCLUDEPATH += d:\opencv\build\include\opencv\
INCLUDEPATH += d:\opencv\build\include\opencv2\

INCLUDEPATH +=-I C:\Python27\include
LIBS += -LC:\Python27\libs -lpython27

LIBS += -Ld:\opencv\build\x64\vc14\lib \
    -lopencv_world330d\
    -lopencv_world330

DISTFILES += \
    upload_weibo.py \
    ../build-opencam-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug/debug/upload_weibo.py \
    ../build-opencam-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug/debug/py_geturl.py
