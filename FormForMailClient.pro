#-------------------------------------------------
#
# Project created by QtCreator 2012-11-06T13:46:25
#
#-------------------------------------------------

QT       += core gui network

TARGET = FormForMailClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsform.cpp \
    pop3.cpp \
    formnewmessage.cpp \
    smtp.cpp

HEADERS  += mainwindow.h \
    settingsform.h \
    pop3.h \
    formnewmessage.h \
    smtp.h

FORMS    += mainwindow.ui \
    settingsform.ui \
    formnewmessage.ui
