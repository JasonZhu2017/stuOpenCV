QT += core
QT -= gui

CONFIG += c++11

TARGET = testOpenCV
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

unix{
#    CONFIG += link_pkgconfig
#    PKGCONFIG += opencv
    INCLUDEPATH += /usr/local/include \
                    /usr/local/include/opencv \
                    /usr/local/include/opencv2

    LIBS += /usr/local/lib/libopencv_highgui.so \
            /usr/local/lib/libopencv_core.so \
            /usr/local/lib/libopencv_imgproc.so
}

win32{

}

