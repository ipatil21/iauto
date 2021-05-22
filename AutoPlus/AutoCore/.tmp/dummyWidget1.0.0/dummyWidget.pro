#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T12:34:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dummyWidget
TEMPLATE = app


SOURCES += \
    main.cpp \
    MainScreen.cpp \
    AutoComment.cpp \
    AutoCommentHelper.cpp \
    FileHandler.cpp

HEADERS  += \
    MainScreen.h \
    AutoComment.h \
    AutoCommentHelper.h \
    FileHandler.h

FORMS    += mainscreen.ui
