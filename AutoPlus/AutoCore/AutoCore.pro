#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T12:34:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ./AutoCore
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainScreen.cpp \
    AutoComment.cpp \
    AutoCommentHelper.cpp \
    FunctionInfo.cpp \
    ParamInfo.cpp

HEADERS  += \
    MainScreen.h \
    AutoComment.h \
    AutoCommentHelper.h \
    AutoDefinations.h \
    FunctionInfo.h \
    ParamInfo.h

FORMS    += mainscreen.ui

#DEFINES+=QT_NO_DEBUG_OUTPUT \
#         QT_NO_WARNING_OUTPUT \
#         QT_NO_INFO_OUTPUT \

DISTFILES += \
    qDoc_temp.txt
