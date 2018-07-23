#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T21:59:19
#
#-------------------------------------------------

QT       += core gui\
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = playerTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    musicPlayer.cpp

HEADERS  += mainwindow.h \
    musicPlayer.h

FORMS    += mainwindow.ui



LIBS += -L$$PWD/lib/ -lavcodec\
        -L$$PWD/lib/ -lavdevice \
        -L$$PWD/lib/ -lavfilter \
        -L$$PWD/lib/ -lavutil \
        -L$$PWD/lib/ -lavformat \
        -L$$PWD/lib/ -lpostproc \
        -L$$PWD/lib/ -lswresample \
        -L$$PWD/lib/ -lSDL2main  \
        -L$$PWD/lib/ -lswscale \
        -L$$PWD/lib/ -swresample \
        -L$$PWD/lib/ -lSDL2

INCLUDEPATH +=$$PWD/include/

