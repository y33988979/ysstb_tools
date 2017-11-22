#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T20:59:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ysstb_tools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chip_reg.cpp \
    chip.cpp

HEADERS  += mainwindow.h \
    chip_reg.h \
    chip.h \
    common.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc

RC_ICONS = 21.ico

#RC_FILE += ico.rc
