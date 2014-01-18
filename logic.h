#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QNetworkProxy>
#include "pop3.h"
#include <QSettings>
#include <QFile>
#include "smtp.h"

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = 0);
    void ReceiveMessages();
    void ParsingFile(int NumberMessage,QString filter,QString& Output);
    void ParsingFileForInputMessage(int NumberMessage,QString& Output);
    void ParsingFile(int NumberMessage,QString filterStart,QString filterFinish,QString& Output);
    int GetCountMessage(QString strInput);
    void SetUp();
    void SendMessageW(QString from, QStringList to,QString subject,QString body);
    int CountReceiveMessage;
    int CountSentMessage;
    QString strServerName,strLogin,strPassword;
    
signals:
    
public slots:

private:
    POP3 *pop;
    QSettings *settingObject;
    void UpdateCountSentMessage();
};

#endif // LOGIC_H
