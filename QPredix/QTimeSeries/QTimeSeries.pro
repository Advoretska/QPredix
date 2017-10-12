#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T15:12:15
#
#-------------------------------------------------

QT       += network websockets

QT       -= gui

TARGET = QTimeSeries
TEMPLATE = lib

DEFINES += QTIMESERIES_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += qtimeseries.cpp \
    qtimeseriesrequests.cpp \
    qtimeseriestag.cpp \
    qtimeseriesparser.cpp \
    qtimeseriesdatapoint.cpp

HEADERS += qtimeseries.h\
        qtimeseries_global.h \
    qtimeseriesrequests.h \
    qtimeseriestag.h \
    qtimeseriesparser.h \
    qtimeseriescommands.h \
    qtimeseriesdatapoint.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}