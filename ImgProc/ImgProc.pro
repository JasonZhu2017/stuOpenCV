#-------------------------------------------------
#
# Project created by QtCreator 2017-07-03T11:51:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgProc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    view/imageview.cpp \
    view/colorreducepanel.cpp \
    view/basicpanel.cpp \
    controller/corecontroller.cpp \
    model/colordetector.cpp \
    model/colorreduce.cpp \
    view/viewpanel.cpp \
    view/viewpanelc3.cpp \
    view/viewpanelc2r2.cpp

HEADERS  += mainwindow.h \
    view/imageview.h \
    view/colorreducepanel.h \
    view/basicpanel.h \
    controller/corecontroller.h \
    model/colordetector.h \
    model/colorreduce.h \
    view/viewpanel.h \
    view/viewpanelc3.h \
    view/viewpanelc2r2.h \
    controller/ringbuffer.h

INCLUDEPATH += C:\opencv\mingw\include\
               C:\opencv\mingw\include\opencv\
               C:\opencv\mingw\include\opencv2\

LIBS += C:\opencv\mingw\lib\libopencv_calib3d2413.dll.a\
    C:\opencv\mingw\lib\libopencv_contrib2413.dll.a\
    C:\opencv\mingw\lib\libopencv_core2413.dll.a\
    C:\opencv\mingw\lib\libopencv_features2d2413.dll.a\
    C:\opencv\mingw\lib\libopencv_flann2413.dll.a\
    C:\opencv\mingw\lib\libopencv_gpu2413.dll.a\
    C:\opencv\mingw\lib\libopencv_highgui2413.dll.a\
    C:\opencv\mingw\lib\libopencv_imgproc2413.dll.a\
    C:\opencv\mingw\lib\libopencv_legacy2413.dll.a\
    C:\opencv\mingw\lib\libopencv_ml2413.dll.a\
    C:\opencv\mingw\lib\libopencv_nonfree2413.dll.a\
    C:\opencv\mingw\lib\libopencv_objdetect2413.dll.a\
    C:\opencv\mingw\lib\libopencv_ocl2413.dll.a\
    C:\opencv\mingw\lib\libopencv_photo2413.dll.a\
    C:\opencv\mingw\lib\libopencv_stitching2413.dll.a\
    C:\opencv\mingw\lib\libopencv_superres2413.dll.a\
    C:\opencv\mingw\lib\libopencv_ts2413.dll.a\
    C:\opencv\mingw\lib\libopencv_video2413.dll.a\
    C:\opencv\mingw\lib\libopencv_videostab2413.dll.a\

DISTFILES +=

RESOURCES += \
    res.qrc
