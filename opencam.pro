#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T08:48:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencam
TEMPLATE = app


SOURCES += main.cpp\
        opencam.cpp \
    img_filter.cpp

HEADERS  += opencam.h \
    img_filter.h

FORMS    += opencam.ui

INCLUDEPATH += d:\opencv\build\include\
INCLUDEPATH += d:\opencv\build\include\opencv\
INCLUDEPATH += d:\opencv\build\include\opencv2\

LIBS += -Ld:\opencv\build\x64\vc14\lib \
    -lopencv_world330d\
    -lopencv_world330
