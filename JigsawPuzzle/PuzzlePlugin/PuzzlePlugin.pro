CONFIG      += plugin debug_and_release
TARGET      = puzzleplugin
TEMPLATE    = lib

HEADERS     = puzzleplugin.h
SOURCES     = puzzleplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

Debug:DESTDIR = $$PWD/../bin/debug
Release:DESTDIR = $$PWD/../bin/release

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(puzzle.pri)


