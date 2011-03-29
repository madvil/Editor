#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T15:42:26
#
#-------------------------------------------------

QT       += core gui

TARGET = editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtpropertybrowser/qtvariantproperty.cpp \
    qtpropertybrowser/qttreepropertybrowser.cpp \
    qtpropertybrowser/qtpropertymanager.cpp \
    qtpropertybrowser/qtpropertybrowserutils.cpp \
    qtpropertybrowser/qtpropertybrowser.cpp \
    qtpropertybrowser/qtgroupboxpropertybrowser.cpp \
    qtpropertybrowser/qteditorfactory.cpp \
    qtpropertybrowser/qtbuttonpropertybrowser.cpp

HEADERS  += mainwindow.h \
    test.h \
    qtpropertybrowser/qtvariantproperty.h \
    qtpropertybrowser/qttreepropertybrowser.h \
    qtpropertybrowser/qtpropertymanager.h \
    qtpropertybrowser/qtpropertybrowserutils_p.h \
    qtpropertybrowser/qtpropertybrowser.h \
    qtpropertybrowser/qtgroupboxpropertybrowser.h \
    qtpropertybrowser/qteditorfactory.h \
    qtpropertybrowser/qtbuttonpropertybrowser.h

FORMS    += mainwindow.ui

RESOURCES += \
    ui_media.qrc \
    qtpropertybrowser/qtpropertybrowser.qrc

OTHER_FILES += \
    qtpropertybrowser/qtpropertybrowser.pri
