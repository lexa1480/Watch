QT       += core gui \
    widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= app_bundle

LIBS += -ldl

SOURCES += \
    Circle.cpp \
    Clock.cpp \
    SendHelp.cpp \
    main.cpp

HEADERS += \
    Circle.h \
    Clock.h \
    SendHelp.h

TARGET = $${TARGET}".bin"
