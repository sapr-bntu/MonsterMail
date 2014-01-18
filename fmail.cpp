#include "fmail.h"

fmail::fmail(QObject *parent) :
    QObject(parent)
{
    //    lstate=Unconnected;
    socket = new QTcpSocket(this);
}
bool fmail::connectToHost(const QString &host, quint16 port)
{//неблокирующая функция возвращает ид
    socket->connectToHost(host,port);
    if(socket->waitForReadyRead(3000))
    {
        QString result = socket->readAll();
        return false;
    }
    else
        return true;
}
bool fmail::login(const QString &user, const QString &password)
{
    QString result;
    socket->write(QString("USER %1\r\n").arg(user).toLocal8Bit());
    if(socket->waitForReadyRead(3000))
    {
        result = socket->readAll();
    }
    else
        return true;
    socket->write(QString("PASS %1\r\n").arg(password).toLocal8Bit());
    if(socket->waitForReadyRead(3000))
    {
        result = result+socket->readAll();
        return false;
    }
    else
        return true;
}
fmail::State fmail::state()
{
    return Unconnected;
}
bool fmail::close()
{
    socket->write(QString("QUIT\r\n").toLocal8Bit());
    if(socket->waitForReadyRead(3000))
        return true;
    else
        return false;
}
QString fmail::mails()
{
    socket->write(QString("STAT\r\n").toLocal8Bit());
    if(socket->waitForReadyRead(3000))
    {
        QString result = socket->readAll();
        return result;
    }
    else
        return QString("bad");
}
int fmail::list()
{
    socket->write(QString("LIST\r\n").toLocal8Bit());
    if(socket->waitForReadyRead(3000))
    {
        QString result = socket->readAll();
        if(result.startsWith("+OK"))
        {
            QStringList slist,slist2;
            slist =result.split("\n");
            slist2 = slist.at(0).split(" ");
            return slist2.at(1).toInt();
            //            qDebug()<<slist2.at(1);
        }
        else
            return -1;
    }
    else
        return -1;
}
QByteArray fmail::retr(int n)
{
    socket->write(QString("RETR  %1\r\n").arg(n).toLocal8Bit());
    QByteArray result;
    while (1)
    {
        if(socket->waitForReadyRead(3000))
        {
            QByteArray tmpString;
            tmpString = socket->readAll();
//            qDebug()<<"tmpString "<<tmpString;
            result.append(tmpString);
            if (tmpString.size() == 0)
                return result;
        }
        else
            return result;

    }
}
QByteArray fmail::top(int n, int st)
{
    socket->write(QString("TOP %1 %2\r\n").arg(n).arg(st).toLocal8Bit());
    if(socket->waitForReadyRead(3000))
    {
        QByteArray result = socket->readAll();
        return result;
    } else {
        return false;
    }
}
