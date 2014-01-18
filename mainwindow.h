#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QtGui>
#include <QDeclarativeContext>
#include "logic.h"

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Logic *logic;
    Q_INVOKABLE void FunctionC();
    Q_INVOKABLE void receiveMessages();
    Q_INVOKABLE void showMessage(int index, int lal);
    Q_INVOKABLE void showNewMessageForm();
    Q_INVOKABLE void showDirectory(int index);
    Q_INVOKABLE void sendMessages();

private:
    QDeclarativeView *ui;
    QObject *Root;
    QUrl newMessageFormUrl;

    QDeclarativeView *uiNewMessage;
       QObject *RootNewMessage;

};

#endif // MAINWINDOW_H
