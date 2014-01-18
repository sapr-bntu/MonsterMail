#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_SettingsForm.h"
#include <QNetworkProxy>
 #include <QTcpSocket>
#include <QFile>
//#include <QTextStream>
#include "POP3.h"
#include <QMessageBox>
#include <stdio.h>

void ParsingFile(int NumberMessage,QString filter,QString& Output)
{
    int i = NumberMessage;
         QFile textFile("Message"+QString::number(i,10)+".txt");
         textFile.open(QIODevice::ReadOnly | QIODevice::Text);
         bool exit = false;
         while(!exit)
         {
            QString textLine = textFile.readLine();
                    if(textLine.startsWith(filter))
                    {
                        Output = textLine;
                        exit = true;
                    }
         }
         textFile.close();
}
void ParsingFile(int NumberMessage,QString filterStart,QString filterFinish,QString& Output)
{
    int i = NumberMessage;
         QFile textFile("Message"+QString::number(i,10)+".txt");
         textFile.open(QIODevice::ReadOnly | QIODevice::Text);
         bool exit = false;
         bool base64 = false;
         while(!exit)
         {
            QString textLine = textFile.readLine();
            if(textLine.startsWith("Content-Transfer-Encoding: base64"))
                base64 = true;
                    if(textLine.startsWith(filterStart))
                    {
                        if(textLine.startsWith("Content-Transfer-Encoding: base64"))
                            base64 = true;
                        while(!exit)
                        {
                        Output += textLine;
                        textLine = textFile.readLine();
                        if(textLine.startsWith("Content-Transfer-Encoding: base64"))
                            base64 = true;

                        if(textFile.atEnd())exit = true;
                         }
                    }
         }
         if(base64)
         {
         QByteArray xcode("");;
          xcode.append(Output);
          QByteArray precode(QByteArray::fromBase64(xcode));
          Output = precode.data();
         }
         textFile.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(20,20,560,350);
    socket = new QTcpSocket();
    settingObject = new QSettings("setting.ini",QSettings::IniFormat,0);
    settingObject->beginGroup("Proxy");
    if(settingObject->value("UseProxy","0").toString() == "1")
    {
        ui->textEditFromDisplaydCurrentMessage_2->setText("Use Proxy");
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
                 proxy.setHostName(settingObject->value("ProxyServer","0").toString());
                 proxy.setPort(settingObject->value("ProxyPort","0").toInt());
                 proxy.setUser(settingObject->value("ProxyUserName","0").toString());
                 proxy.setPassword(settingObject->value("ProxyPassword","0").toString());
       QNetworkProxy::setApplicationProxy(proxy);
    }
    else
    {
         ui->textEditFromDisplaydCurrentMessage_2->setText("Not Use Proxy");
        QNetworkProxy proxy;
        QNetworkProxy::setApplicationProxy(proxy);
    }
    settingObject->endGroup();

    settingObject->beginGroup("Message");
    int countMessage = settingObject->value("CountMessage","0").toInt(0);
    settingObject->endGroup();

    QString from,subject;
    for(int i=1;i<=countMessage;i++)
    {
        ParsingFile(i,"From",from);
        ParsingFile(i,"Subject",subject);
    ui->listWidget->addItem(from + " " + subject);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSettings_activated()
{
   settingForm.show();
}
int GetCountMessage(QString strInput)
{

    QString output;
    for(int i = 0;i<strInput.length();i++)
    {
        if(strInput[i].isDigit())
        {
            for(int j=i;j<strInput.length();j++)
            {
            output.append(strInput[j]);
            if(!strInput[j+1].isDigit())
                j = strInput.length();
            }
            i = strInput.length();
        }
    }
    QString m = output;
    return output.toInt(0,10);
}


void MainWindow::on_actionReceive_Messages_activated()
{
    settingObject->beginGroup("MailServerSettings");

    QString hostStr = settingObject->value("MailServer","0").toString();
    int  port = settingObject->value("Port","0").toInt();
    QString Login = settingObject->value("Login","0").toString();
    QString Pass = settingObject->value("Password","0").toString();
    settingObject->endGroup();
    POP3 *pop = new POP3();
        pop->Connect(hostStr,port);
     ui->textEditFromDisplaydCurrentMessage_2->setText(pop->debugStr);
        pop->Login(Login, Pass);

        QString CountMessageString = pop->doCommand("stat\r\n",false);
        int CountMessage = GetCountMessage(CountMessageString);

        settingObject->beginGroup("Message");
        settingObject->setValue("CountMessage",QString::number(CountMessage,10));
        settingObject->endGroup();

        QMessageBox MB;
        MB.setText("Count message = "+ QString::number(CountMessage,10) );
        MB.exec();
        for(int i = 1;i<=CountMessage;i++)
        {
              QString message;
       // pop->
             pop->GetMessage(QString::number(i,10), message);
             QFile textFile("Message"+QString::number(i,10)+".txt");
             textFile.open(QIODevice::WriteOnly | QIODevice::Text);
             textFile.write((const char *)message.toAscii());
             textFile.close();
        }
         pop->Quit();
         ui->listWidget->clear();
        QString from,subject;
        for(int i=1;i<=CountMessage;i++)
        {
            ParsingFile(i,"From",from);
            ParsingFile(i,"Subject",subject);
        ui->listWidget->addItem(from + " " + subject);
        }
}


void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    int NumberMessage = index.row()+1;
    QString Message;
    ParsingFile(NumberMessage,"\r\n","\r\n",Message);
    ui->textEditFromDisplaydCurrentMessage_2->setText(Message);
}

void MainWindow::on_actionNew_Message_activated()
{
    newMessageForm.show();
}
