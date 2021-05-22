#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T21:18:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoUI
TEMPLATE = app

win32:RC_FILE += rsc/AUTO.rc

SOURCES += main.cpp\
        AutoWindow.cpp \
    AutoConfiguration.cpp \
    AutoCore/AutoComment.cpp \
    AutoCore/AutoCommentHelper.cpp \
    AutoCore/FunctionInfo.cpp \
    AutoCore/ParamInfo.cpp

HEADERS  += AutoWindow.h \
    AutoConfiguration.h \
    AutoCore/AutoComment.h \
    AutoCore/AutoCommentHelper.h \
    AutoCore/AutoDefinations.h \
    AutoCore/FunctionInfo.h \
    AutoCore/ParamInfo.h

FORMS    += AutoWindow.ui

RESOURCES += \
    rsc/AutoPlus.qrc
