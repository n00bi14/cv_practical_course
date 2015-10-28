#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T14:14:05
#
#-------------------------------------------------

QT       += core gui
QT += widgets

TARGET = Bildverarbeitung
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv2\
                /usr/local/include/opencv

LIBS += -L/usr/local/lib/
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    challangeone.cpp \
    imageelement.cpp \
    challangetwo.cpp \
    imageprocessing.cpp \
    challangethree.cpp \
    challangefour.cpp \
    challangefive.cpp

HEADERS  += mainwindow.h \
    challangeone.h \
    imageelement.h \
    challangetwo.h \
    imageprocessing.h \
    challangethree.h \
    challangefour.h \
    challangefive.h

FORMS    += mainwindow.ui \
    challangeone.ui \
    challangetwo.ui \
    challangethree.ui \
    challangefour.ui \
    challangefive.ui
