#include "mainwindow.h"
#include "logic.h"
#include <QtDeclarative>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new QDeclarativeView;
    logic = new Logic();
    logic->SetUp();

    ui->setMinimumHeight(480);
    ui->setMinimumWidth(640);
    ui->setSource(QUrl("qrc:/mainform.qml"));

    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    Root = ui->rootObject();

    ui->rootContext()->setContextProperty("window", this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::FunctionC()
{
}


void MainWindow::receiveMessages()
{
    qDebug("button receive pushed");
    QObject* messagesModel = Root->findChild<QObject*>("messages");
    QMetaObject::invokeMethod(messagesModel, "clear");
//    QMetaObject::invokeMethod(messagesModel, "append", Q_ARG(QVariant, QVariant(tr("test"))));
    logic->ReceiveMessages();
    QString from,subject;
    for(int i=1; i <= logic->CountReceiveMessage; i++)
    {
        logic->ParsingFile(i,"From",from);
        logic->ParsingFile(i,"Subject",subject);
        QMetaObject::invokeMethod(messagesModel, "append",
                    Q_ARG(QVariant, QVariant(tr((from + " " + subject).toLatin1())))
                    );
    }
}

void MainWindow::showMessage(int index, int lal)
{
    int NumberMessage = index + 1;
    QString Message;
    if (lal==0)
    {
        logic->ParsingFile(NumberMessage,"\r\n","\r\n",Message);
    }
    else
    if (lal==1)
    {
        logic->ParsingFileForInputMessage(NumberMessage,Message);
    }
    else
    {
        Message = "Kierkegor";
    }
    QObject* message = Root->findChild<QObject*>("message");
    qDebug()<<Message;
    message->setProperty("text", Message);
}

void MainWindow::showNewMessageForm()
{
   // uiNewMessage->setSource(QUrl("qrc:/FormNewMessage.qml"));

    //uiNewMessage->rootContext()
     qDebug(newMessageFormUrl.toString().toLatin1());
     QDeclarativeView *view = new QDeclarativeView();
     view->setSource(newMessageFormUrl);
     view->setMinimumSize(QSize(300,400));
     view->setAttribute(Qt::WA_DeleteOnClose);
     RootNewMessage = view->rootObject();
     view->rootContext()->setContextProperty("window", this);
     view->show();
//     QObject *object = view.rootObject();
}


void MainWindow::showDirectory(int index)

{
    qDebug("button receive pushed");
    QObject* messagesModel = Root->findChild<QObject*>("messages");
    QMetaObject::invokeMethod(messagesModel, "clear");
    if(index == 0)
    {
        QString from,subject;
        for(int i=1; i <= logic->CountReceiveMessage; i++)
        {
            logic->ParsingFile(i,"From",from);
            logic->ParsingFile(i,"Subject",subject);
            QMetaObject::invokeMethod(messagesModel, "append",
                                      Q_ARG(QVariant, QVariant(tr((from + " " + subject).toLatin1())))
                                      );
        }
    }
    if(index == 1)
    {
        for(int i=1;i<=logic->CountSentMessage;i++)
        {
            QMetaObject::invokeMethod(messagesModel, "append",
                                      Q_ARG(QVariant, QVariant(tr(("send_message" + QString::number(i,10)).toLatin1())))
                                      );
        }
    }
}
void MainWindow::sendMessages()
{
         qDebug("button sendMessage pushed!");

          QObject* textInputServerName = Root->findChild<QObject*>("InputLineServer");
          QObject* textInputLogin = Root->findChild<QObject*>("InputLineLogin");
          QObject* textInputPassword = Root->findChild<QObject*>("InputLinePassword");
          QObject* textInputFrom = Root->findChild<QObject*>("InputLineFrom");
          QObject* textInputTo = Root->findChild<QObject*>("InputLineTo");
          QObject* textInputBody = Root->findChild<QObject*>("InputLineBody");
         QObject* textInputSubject = Root->findChild<QObject*>("InputLineSubject");

         QString strServerName;//Создадим новую строковую переменную
         QString strLogin;
         QString strPassword;
         QString strFrom;
         QString strSubject;
         QStringList strTo;
         QString strBody;
             //Считаем информацию со строки ввода через свойство text
             strServerName=(textInputServerName->property("text")).toString();
             strLogin=(textInputLogin->property("text")).toString();
             strPassword=(textInputPassword->property("text")).toString();
             strFrom=(textInputFrom->property("text")).toString();
             QString strToString=(textInputTo->property("text")).toString();
              strBody = (textInputBody->property("text")).toString();
             strSubject= (textInputSubject->property("text")).toString();
             //Ну и наконец выведем в поле вывода нашу информацию
             strTo = strToString.split(";");
             //memo->setProperty("text", str+"+1="+str2);
             logic->strLogin = strLogin;
             logic->strPassword = strPassword;
             logic->strServerName = strServerName;
          logic->SendMessageW(strFrom,strTo,strSubject,strBody);

}
