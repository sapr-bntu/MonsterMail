#include "pop3.h"
#include <iostream>
#include <QString>

POP3::POP3(QObject *parent) :
    QObject(parent)
{
}
    bool POP3::Connect(QString host,short unsigned int port)
    {
        socket.connectToHost(host,port);
        if (!socket.waitForConnected(CONNECT_TIMEOUT))
        {
           debugStr = "Could not connect: ";
            return false;
        }
        QString response;
        ReadResponse(false,response);
        if (response.startsWith("+OK"))
          {
            debugStr =  " connected";
            }
        return true;
    }

    QString POP3::doCommand(QString command,bool isMultiline)
    {
      debugStr =  "sending command: " + command;
        QString response;
        qint64 writeResult = socket.write(command.toAscii());
        if (writeResult != command.size())
        {
        }
         debugStr =  "Could not write all bytes: ";
        if (writeResult > 0 && !socket.waitForBytesWritten(WRITE_TIMEOUT))
       {}
            debugStr =  "Could not write bytes from buffer: ";
        if (!ReadResponse(isMultiline,response))
            return "";
        debugStr =  response;
        return response;
    }

    bool POP3::ReadResponse(bool isMultiline,QString& response)
    {
        char buff[512+1];
        bool couldRead = socket.waitForReadyRead( READ_TIMEOUT ) ;
        if (!couldRead)
           debugStr =  "could not receive data: ";
        bool complete=false;
        bool completeLine=false;
        unsigned int offset=0;
        while (couldRead && !complete)
        {
            //qDebug() << "reading front\n";
            if (offset >= sizeof(buff))
            {
             //   qDebug() << "avoiding buffer overflow, server is not RFC1939 compliant\n";
                return false;
            }
            qint64 bytesRead = socket.readLine(buff + offset,sizeof(buff)-offset);
            if (bytesRead == -1)
                return false;
            couldRead = bytesRead > 0;
            completeLine = buff[offset+bytesRead-1]=='\n';
            if (couldRead)
            {
                if (completeLine)
                {
                 //   //qDebug() << "Line Complete\n";
                    offset = 0;
                    if (response.size() == 0)
                    {//first line, check for error
                        response.append(buff);
                        if (!response.startsWith("+OK"))
                            complete = true;
                        else
                            complete = !isMultiline;
                    }
                    else
                    {//NOT first line, check for byte-stuffing
                        //check if the response was complete
                        complete = ( strcmp(buff,".\r\n") == 0 );
                        if (!complete)
                        {
                            if (buff[0] == '.' && buff[1]== '.')
                                response.append(buff+1);	//remove the stuffed byte and add to the response
                            else
                                response.append(buff);	//add to the response
                        }
                    }
                }
                else
                {
                  //  //qDebug() << "Line INComplete: " << buff <<"\n";
                    offset += bytesRead;
                }
            }
            if (couldRead && !complete)
            {
                if (socket.bytesAvailable() <= 0)
                {
                //  //  qDebug() << "waiting for data\n";
                    couldRead = socket.waitForReadyRead( READ_TIMEOUT ) ;
                //  //  qDebug() << "waiting for data finished, couldread: " << couldRead << "\n";
                }
            }
        }
        return couldRead && complete;
    }

    bool POP3::Login(QString user, QString pwd)
    {
        if (!SendUser(user))
            return false;
        if (!SendPasswd(pwd))
            return false;
        return true;
    }
    bool POP3::SendUser(QString& user)
    {
        QString res = doCommand("USER "+user+"\r\n",false);
        if (res.startsWith("+OK"))
            return true;
        else
            return false;
    }
    bool POP3::SendPasswd(QString& pwd)
    {
        QString res = doCommand("PASS "+pwd+"\r\n",false);
        if (res.startsWith("+OK"))
            return true;
        else
            return false;
    }
    bool POP3::GetMessageTop(QString msgId, int nbLines, QString& msgTop)
    {
        QString res = doCommand("TOP "+msgId+" "+QString::number(nbLines)+"\r\n",true);
        if (res.startsWith("+OK"))
        {
            msgTop = res.section("\r\n",1);
            return true;
        }
        else
            return false;
    }
    bool POP3::GetMessage(QString msgId, QString& msg)
    {
        QString res = doCommand("RETR "+msgId+"\r\n",true);
        if (res.size() == 0)
            return false;
        if (res.startsWith("+OK"))
        {
            msg = res.section("\r\n",1);
            return true;
        }
        else
        {
            debugStr =  "ErrResponse: " + res;
            return false;
        }
    }

    bool POP3::Quit()
    {
        QString res = doCommand("QUIT\r\n",false);
        if (res.startsWith("+OK"))
        {
            if (!socket.waitForDisconnected(DISCONNECT_TIMEOUT))
            {
               debugStr =  "Connection was not closed by server: ";
                return false;
            }
            return true;
        }
        else
        {
            return false;
        }
}

