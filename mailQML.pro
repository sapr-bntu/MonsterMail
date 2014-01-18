#-------------------------------------------------
#
# Project created by QtCreator 2013-05-07T14:47:39
#
#-------------------------------------------------

QT       += core gui declarative network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab3_QML
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    smtp.cpp \
    pop3.cpp \
    logic.cpp

HEADERS  += mainwindow.h \
    smtp.h \
    pop3.h \
    logic.h

OTHER_FILES += \
    mainform.qml \
    Button.qml \
    FormNewMessage.qml \
    MessagesList.qml \
    Directory.qml \
    MessageView.qml \
    Settings.qml \
    MainWindow.qml \
    CircleButton.qml \
    TextInputDesu.qml \
    InputDescription.qml \
    Input.qml

RESOURCES += \
    res.qrc
