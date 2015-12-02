#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T03:23:11
#
#-------------------------------------------------

QT       += core gui
QT      += phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = caiji
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Dis_thread.cpp \
    play.cpp \
    ssthread.cpp

HEADERS  += mainwindow.h \
    x264.h \
    Dis_thread.h \
    play.h \
    ssthread.h


FORMS    += mainwindow.ui \
    play.ui

LIBS += -L. -lx264 -lpthread

RESOURCES += \
    res.qrc

LIBS += -L/usr/lib \
          -lopencv_core \
          -lopencv_highgui \
          -lopencv_imgproc \

LIBS += -L/usr/local/lib -lwiringPi
INCLUDEPATH += /usr/include \
                /usr/include/opencv \
                /usr/include/opencv2\

RC_FILE =  myapp.rc

