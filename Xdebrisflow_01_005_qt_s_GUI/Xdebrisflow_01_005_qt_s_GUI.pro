#-------------------------------------------------
#
# Project created by QtCreator 2019-08-07T12:14:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Xdebrisflow_01_005_qt_s_GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    data.cpp \
    dialog_channel.cpp \
    dialog_channel_view.cpp \
    dialog_dam.cpp \
    dialog_dam_view.cpp \
    dialog_initiation.cpp \
    dialog_initiation_view.cpp \
    dialog_movement.cpp \
    dialog_movement_view.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowview.cpp \
    process_bar_widget.cpp \
    swe_view.cpp \
    Swe_mnt/phase.cpp \
    Swe_mnt/process_main.cpp \
    Swe_mnt/process_post.cpp \
    Swe_mnt/process_pre.cpp \
    Swe_mnt/process_pre_makeshape.cpp \
    Swe_mnt/swe_movemnt.cpp \
    Swe_mnt/term.cpp \
    swe.cpp \
    dialog_logging_view.cpp \
    dialog_logging.cpp \
    Swe_mnt/function.cpp \
    frmroundplot.cpp \
    roundplot.cpp

HEADERS += \
    data.h \
    dialog_channel.h \
    dialog_channel_view.h \
    dialog_dam.h \
    dialog_dam_view.h \
    dialog_initiation.h \
    dialog_initiation_view.h \
    dialog_movement.h \
    dialog_movement_view.h \
    mainwindow.h \
    mainwindowview.h \
    process_bar_widget.h \
    swe_view.h \
    Swe_mnt/phase.h \
    Swe_mnt/process_main.h \
    Swe_mnt/process_post.h \
    Swe_mnt/process_pre.h \
    Swe_mnt/process_pre_makeshape.h \
    Swe_mnt/swe_movemnt.h \
    Swe_mnt/term.h \
    swe.h \
    dialog_logging_view.h \
    dialog_logging.h \
    Swe_mnt/function.h \
    frmroundplot.h \
    roundplot.h


FORMS += \
    mainwindow.ui \
    process_bar_widget.ui \
    dialog_movement.ui \
    dialog_channel.ui \
    dialog_initiation.ui \
    dialog_dam.ui \
    dialog.ui \
    frmroundplot2.ui

RESOURCES += \
    resource.qrc
