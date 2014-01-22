#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T20:46:24
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = srcds_rcon
CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rconconnection.cpp \
    rconpackage.cpp \
    inputreader.cpp

HEADERS += \
    rconconnection.h \
    rconpackage.h \
    inputreader.h
