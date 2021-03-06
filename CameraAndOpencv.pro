#-------------------------------------------------
#
# Project created by QtCreator 2018-01-11T14:21:41
#
#-------------------------------------------------

QT       += core gui
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraAndOpencv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    operateimageinterface.cpp

HEADERS += \
        widget.h \
    operateimageinterface.h


#INCLUDEPATH += ./opencv/include
#LIBS += $$PWD/opencv/lib/opencv_world340.lib \
#    $$PWD/opencv/lib/opencv_world340d.lib

unix{
INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS    +=  /usr/local/lib/libopencv_highgui.so \
            /usr/local/lib/libopencv_core.so    \
            /usr/local/lib/libopencv_imgproc.so \
            /usr/local/lib/libopencv_imgcodecs.so   \
            /usr/local/lib/libopencv_video.so   \
            /usr/local/lib/libopencv_videoio.so
}
