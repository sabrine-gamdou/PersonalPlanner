#-------------------------------------------------
#
# Project created by QtCreator 2020-05-04T13:10:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PersonalPlanner
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    databasesingleton.cpp \
    task.cpp \
    taskdaoimp.cpp \
    user.cpp \
    userdaoimp.cpp \
    registrationform.cpp \
    tasklistmodel.cpp \
    statusform.cpp \
    calendarmanager.cpp \
    helpform.cpp \
    aboutform.cpp

HEADERS += \
        mainwindow.h \
    login.h \
    databasesingleton.h \
    task.h \
    taskdaoimp.h \
    user.h \
    userdaoimp.h \
    registrationform.h \
    tasklistmodel.h \
    statusform.h \
    calendarmanager.h \
    helpform.h \
    aboutform.h

FORMS += \
        mainwindow.ui \
    login.ui \
    registrationform.ui \
    statusform.ui \
    helpform.ui \
    aboutform.ui

STATECHARTS +=

DISTFILES += \
    uml.qmodel
