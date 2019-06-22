#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T13:00:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ED2016_Dracula
TEMPLATE = app


SOURCES += main.cpp\
        ventanaprincipal.cpp \
    vcortarmazo.cpp \
    vdireccion.cpp \
    vmesa.cpp \
    carta.cpp \
    deck.cpp \
    tablero.cpp \
    vganador.cpp

HEADERS  += ventanaprincipal.h \
    vcortarmazo.h \
    vdireccion.h \
    vmesa.h \
    carta.h \
    deck.h \
    tablero.h \
    linkedstack.h \
    nodo.h \
    vganador.h

FORMS    += ventanaprincipal.ui \
    vcortarmazo.ui \
    vdireccion.ui \
    vmesa.ui \
    vganador.ui

RESOURCES += \
    resources.qrc
