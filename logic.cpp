#include "logic.h"
#include <QEventLoop>
#include <QDebug>

Logic::Logic(QObject *parent) :
    QObject(parent)
{
}
void Logic::ParsingFile(int NumberMessage,QString filter,QString& Output)
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
void Logic::ParsingFileForInputMessage(int NumberMessage,QString& Output)
{
    if(NumberMessage!=0)
    {
        int i = NumberMessage-1;
        QFile textFile("send_message"+QString::number(i,10)+".txt");
        textFile.open(QIODevice::ReadOnly | QIODevice::Text);
        Output = textFile.readAll();
        textFile.close();
    }
}

void Logic::ParsingFile(int NumberMessage,QString filterStart,QString filterFinish,QString& Output)
{
    int i = NumberMessage;
    QFile textFile("Message"+QString::number(i,10)+".txt");
    textFile.open(QIODevice::ReadOnly | QIODevice::Text);
    bool exit = false;
    bool base64 = false;
    while(!exit)
    {
        bool flag = true;
        QString textLine = textFile.readLine();
        if(textLine.startsWith("Content-Transfer-Encoding: base64"))
            base64 = true;
        if(textLine.startsWith(filterStart))
        {
            while(!exit)
            {
                Output += textLine;
                textLine = textFile.readLine();
                if(textFile.atEnd())exit = true;
            }
        }
        Output.replace(0,4,"\n");
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
int Logic::GetCountMessage(QString strInput)
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
    return output.toInt(0,10);
}
void Logic::SetUp()
{
    qDebug("SetUp begin");
    settingObject = new QSettings("setting.ini",QSettings::IniFormat,0);
    settingObject->beginGroup("Proxy");
    if(settingObject->value("UseProxy","0").toString() == "1")
    {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(settingObject->value("ProxyServer","0").toString());
        proxy.setPort(settingObject->value("ProxyPort","0").toInt());
        proxy.setUser(settingObject->value("ProxyUserName","0").toString());
        proxy.setPassword(settingObject->value("ProxyPassword","0").toString());
        QNetworkProxy::setApplicationProxy(proxy);
    }
//    else
//    {
//        QNetworkProxy proxy;
//        QNetworkProxy::setApplicationProxy(proxy);
//    }
    settingObject->endGroup();

    settingObject->beginGroup("Message");
    CountReceiveMessage = settingObject->value("CountMessage", "0").toInt();
    qDebug("CountReceiveMessage: " + settingObject->value("CountMessage", "0").toString().toLatin1());
    CountSentMessage = settingObject->value("CountSendMessage","0").toInt();
    settingObject->endGroup();
    qDebug("SetUp end");
}

void Logic::UpdateCountSentMessage()
{
    QSettings* setting = new QSettings("setting.ini",QSettings::IniFormat,0);
    setting->beginGroup("Message");
    setting->setValue("CountSendMessage",QString::number(CountSentMessage,10));
    setting->endGroup();
}

void Logic::ReceiveMessages()
{
    settingObject->beginGroup("MailServerSettings");

    QString hostStr = settingObject->value("MailServer","0").toString();
    qDebug(hostStr.toLatin1());
    int  port = settingObject->value("Port","0").toInt();
    QString Login = settingObject->value("Login","0").toString();
    qDebug(Login.toLatin1());
    QString Pass = settingObject->value("Password","0").toString();
    qDebug(Pass.toLatin1());
    settingObject->endGroup();
    pop = new POP3();
    pop->Connect(hostStr,port);
    pop->Login(Login, Pass);

    QString CountMessageString = pop->doCommand("stat\r\n",false);
    CountReceiveMessage = GetCountMessage(CountMessageString);

    settingObject->beginGroup("Message");
    settingObject->setValue("CountMessage",QString::number(CountReceiveMessage,10));
    settingObject->endGroup();

    for(int i = 1;i<=CountReceiveMessage;i++)
    {
        QString message;

        pop->GetMessage(QString::number(i,10), message);
        QFile textFile("Message"+QString::number(i,10)+".txt");
        textFile.open(QIODevice::WriteOnly | QIODevice::Text);
        //***********textFile.write((const char *)message.toAscii());
        textFile.write((const char *)message.toLatin1());
        textFile.close();
    }
    pop->Quit();
}
void Logic::SendMessageW(QString from, QStringList to,QString subject,QString body)
{
    //We create an event loop and connect to it to prevent the main thread from being crippled when sending large or slow emails

    QEventLoop loop;
    Smtp *smtp = new Smtp(strServerName, strLogin, strPassword, from, to, subject, body);
    QObject::connect(smtp, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    CountSentMessage++;
    UpdateCountSentMessage();

    QFile textFile;
    bool endfile;
    endfile = true;
    for (int i=0;endfile;i++)
    {
        textFile.setFileName(QString("send_message%1.txt").arg(i));
        if (!textFile.exists())endfile=false;
    }

    textFile.open(QIODevice::WriteOnly | QIODevice::Text);
    //*******************textFile.write((const char *)body.toAscii());
    textFile.write((const char *)body.toLatin1());
    textFile.close();
}
