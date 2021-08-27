QT       += core gui \
    widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= app_bundle
CONFIG += boost164

LIBS += -ldl

NITA_LIBS += -lreg_12

LIBS += -lboost_system
LIBS += -lboost_filesystem

SOURCES += \
    Circle.cpp \
    Clock.cpp \
    SendHelp.cpp \
    main.cpp

HEADERS += \
    Circle.h \
    Clock.h \
    CoordXml.h \
    SendHelp.h

TARGET = $${TARGET}".bin"
