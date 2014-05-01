#-------------------------------------------------
#
# Project created by QtCreator 2014-05-01T14:09:21
#
#-------------------------------------------------
include(settings.pri)
QT       += core

QT       -= gui

TARGET = luaIntfTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix {
    macx {
	include(lua.pri)
    } else {
	CONFIG+=link_pkgconfig
	PKGCONFIG+=lua5.2
    }
}


SOURCES += main.cpp

OTHER_FILES += \
    simple.lua \
    readme.md
