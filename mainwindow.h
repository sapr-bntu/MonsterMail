#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settingsform.h>
#include <formnewmessage.h>
#include <QSettings>
#include <QNetworkProxy>
 #include <QTcpSocket>
#include <QModelIndex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SettingsForm settingForm;
    FormNewMessage newMessageForm;
    QSettings *settingObject;
    QTcpSocket *socket;
    
private slots:
    void on_actionSettings_activated();

    void on_actionReceive_Messages_activated();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_actionNew_Message_activated();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
