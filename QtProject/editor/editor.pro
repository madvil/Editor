#-------------------------------------------------
#
# Project created by QtCreator 2011-03-29T15:42:26
#
#-------------------------------------------------

QT       += core gui opengl

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
    qtpropertybrowser/qtbuttonpropertybrowser.cpp \
    entity.cpp \
    baseobject.cpp \
    propertymanagers.cpp \
    texturelistitemwidget.cpp \
    glwidget.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    test.h \
    qtpropertybrowser/qtvariantproperty.h \
    qtpropertybrowser/qttreepropertybrowser.h \
    qtpropertybrowser/qtpropertymanager.h \
    qtpropertybrowser/qtpropertybrowserutils_p.h \
    qtpropertybrowser/qtpropertybrowser.h \
    qtpropertybrowser/qtgroupboxpropertybrowser.h \
    qtpropertybrowser/qteditorfactory.h \
    qtpropertybrowser/qtbuttonpropertybrowser.h \
    entity.h \
    baseobject.h \
    propertymanagers.h \
    constants.h \
    texturelistitemwidget.h \
    glwidget.h \
    scene.h

FORMS    += mainwindow.ui \
    texturelistitemwidget.ui

RESOURCES += \
    ui_media.qrc \
    qtpropertybrowser/qtpropertybrowser.qrc

OTHER_FILES += \
    qtpropertybrowser/qtpropertybrowser.pri
