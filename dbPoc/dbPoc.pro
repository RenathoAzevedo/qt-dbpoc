#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T08:06:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dbPoc
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    modelproxy.cpp \
    produto.cpp

HEADERS  += \
    modelproxy.h \
    produto.h

FORMS    += \
    produto.ui
