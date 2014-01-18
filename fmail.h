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
//    Signals
//    void	commandFinished ( int id, bool error )
//    void	commandStarted ( int id )
//    void	dataTransferProgress ( qint64 done, qint64 total )
//    void	done ( bool error )
//    void	listInfo ( const QUrlInfo & i )
//    void	rawCommandReply ( int replyCode, const QString & detail )
//    void	readyRead ()
//    void	stateChanged ( int state )

public slots:
    //    int	close ()
        int	connectToHost ( const QString & host, quint16 port = 110 );
    //    Error	error () const
        int	login ( const QString & user = QString(), const QString & password = QString() );
    //    int	setProxy ( const QString & host, quint16 port )
        State	state ();
        bool	close ();//int
        QString mails();
        int list();
        QByteArray  retr(int n);
        QByteArray  top(int n,int st);
};

#endif // FMAIL_H

//реализация базовых команд POP3

//        Команда: USER [имя]

//        Команда: PASS [пароль]

//        Команда: STAT

//        Команда: NOOP

//        Команда: LIST [сообщение]
//        Команда:RETR [сообщение]
//        Аргументы: [сообщение] - номер сообщения
//        Описание: После положительного ответа сервер передаёт содержание сообщения.
//        Возможные ответы:
//        +OK message follows


    //        Команда: QUIT

//    QFtp ( QObject * parent = 0 )
//    virtual	~QFtp ()
//    qint64	bytesAvailable () const
//    int	cd ( const QString & dir )
//    void	clearPendingCommands ()
//    int	close ()
//    int	connectToHost ( const QString & host, quint16 port = 21 )
//    Command	currentCommand () const
//    QIODevice *	currentDevice () const
//    int	currentId () const
//    Error	error () const
//    QString	errorString () const
//    int	get ( const QString & file, QIODevice * dev = 0, TransferType type = Binary )
//    bool	hasPendingCommands () const
//    int	list ( const QString & dir = QString() )
//    int	login ( const QString & user = QString(), const QString & password = QString() )
//    int	mkdir ( const QString & dir )
//    int	put ( QIODevice * dev, const QString & file, TransferType type = Binary )
//    int	put ( const QByteArray & data, const QString & file, TransferType type = Binary )
//    int	rawCommand ( const QString & command )
//    qint64	read ( char * data, qint64 maxlen )
//    QByteArray	readAll ()
//    int	remove ( const QString & file )
//    int	rename ( const QString & oldname, const QString & newname )
//    int	rmdir ( const QString & dir )
//    int	setProxy ( const QString & host, quint16 port )
//    int	setTransferMode ( TransferMode mode )
//    State	state () const

//enum QHttp::Error
//This enum identifies the error that occurred.
//Constant	Value	Description
//QHttp::NoError	0	No error occurred.
//QHttp::HostNotFound	2	The host name lookup failed.
//QHttp::ConnectionRefused	3	The server refused the connection.
//QHttp::UnexpectedClose	4	The server closed the connection unexpectedly.
//QHttp::InvalidResponseHeader	5	The server sent an invalid response header.
//QHttp::WrongContentLength	6	The client could not read the content correctly because an error with respect to the content length occurred.
//QHttp::Aborted	7	The request was aborted with abort().
//QHttp::ProxyAuthenticationRequiredError	9	QHttp is using a proxy, and the proxy server requires authentication to establish a connection.
//QHttp::AuthenticationRequiredError	8	The web server requires authentication to complete the request.
//QHttp::UnknownError	1	An error other than those specified above occurred.


//This enum is used to specify the state the client is in:
//Constant	Value	Description
//::Unconnected	0	There is no connection to the host.
//::HostLookup	1	A host name lookup is in progress.
//::Connecting	2	An attempt to connect to the host is in progress.
//::Sending	3	The client is sending its request to the server.
//::Reading	4	The client's request has been sent and the client is reading the server's response.
//::Connected	5	The connection to the host is open, but the client is neither sending a request, nor waiting for a response.
//::Closing	6	The connection is closing down, but is not yet closed. (The state will be Unconnected when the connection is closed.)
