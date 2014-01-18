#ifndef FMAIL_H
#define FMAIL_H

#include <QObject>
#include <QtNetwork>

class fmail : public QObject
{
    Q_OBJECT
public:
    explicit fmail(QObject *parent = 0);
    enum State  {Unconnected,HostLookup,Connecting,Connected,LoggedIn,Closing};
private:
    QTcpSocket *socket;
    int lstate;

signals:

public slots:
        bool	connectToHost ( const QString & host, quint16 port = 110 );
        bool	login ( const QString & user = QString(), const QString & password = QString() );
        State	state ();
        bool	close ();//int
        QString mails();
        int list();
        QByteArray  retr(int n);
        QByteArray  top(int n,int st);
};

#endif // FMAIL_H
