#ifndef POP3_H
#define POP3_H

#include <QObject>
#include <QTcpSocket>

#define CONNECT_TIMEOUT 3*1000
#define DISCONNECT_TIMEOUT 3*1000
#define READ_TIMEOUT 15*1000
#define WRITE_TIMEOUT 3*1000

class POP3 : public QObject
{
    Q_OBJECT
private:
    QTcpSocket socket;



    bool ReadResponse(bool isMultiline,QString& response);
    bool SendUser(QString& user);
    bool SendPasswd(QString& pwd);

public:

    explicit POP3(QObject *parent = 0);
  //  POP3(QObject *parent = 0);
    QString debugStr;
    QString doCommand(QString command,bool isMultiline);
        bool Connect(QString host,short unsigned  port);
        bool Login(QString user, QString pwd);
        bool GetMessageTop(QString msgId, int nbLines, QString& msgTop);
        bool GetMessage(QString msgId, QString& msg);
        bool Quit();
signals:
    
public slots:
    
};

#endif // POP3_H
