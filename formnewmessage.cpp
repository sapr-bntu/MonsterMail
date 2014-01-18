#include "formnewmessage.h"
#include "ui_formnewmessage.h"
#include <QSettings>
#include <smtp.h>
#include <QMessageBox>

FormNewMessage::FormNewMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormNewMessage)
{
    ui->setupUi(this);
   }

FormNewMessage::~FormNewMessage()
{
    delete ui;
}

void FormNewMessage::on_pushButton_clicked()
{
    QSettings *settingObject = new QSettings("setting.ini",QSettings::IniFormat,0);
    settingObject->beginGroup("MailServerSettings");
     QString username = settingObject->value("Login","0").toString();
     QString password = settingObject->value("Password","0").toString();
     QString from = settingObject->value("Login","0").toString();
    settingObject->endGroup();

    QString serverName(ui->lineEditServerIsxod->text());
    QStringList to = ui->lineEditTo->text().split(";");
    QString subject(ui->lineEditSubject->text());
    QString body(ui->textEdit->toPlainText());

        //We create an event loop and connect to it to prevent the main thread from being crippled when sending large or slow emails
        QEventLoop loop;
        Smtp *smtp = new Smtp(serverName, username, password, from, to, subject, body);
        QObject::connect(smtp, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QMessageBox QMB;
        QMB.setText("Message is sent");
        QMB.exec();
}
