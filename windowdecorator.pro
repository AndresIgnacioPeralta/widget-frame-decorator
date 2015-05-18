#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T22:35:05
#
#-------------------------------------------------

QT += core gui
QT += winextras #Need for windows UI window control access

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = windowdecorator
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           windowdecorator.cpp \
           containerframe.cpp \
           decorationconfigurationwidget.cpp

HEADERS  += mainwindow.h \
            windowdecorator.h \
            containerframe.h \
            decorationconfigurationwidget.h

FORMS    += mainwindow.ui \
            containerframe.ui \
            decorationconfigurationwidget.ui
