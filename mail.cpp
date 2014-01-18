#include "mail.h"
#include "ui_mail.h"
#include "fmail.h"
#include <QDebug>

mail::mail(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::mail)
{
    ui->setupUi(this);
    ui->textBrowser->hide();
    QFile base("mail.db");
    if(base.exists())
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("mail.db");
        db.open();
        QSqlQuery query;
        query.exec("CREATE TABLE main.mail ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "catalog TEXT, "
                   "name TEXT, "
                   "size TEXT, "
                   "body TEXT, "
                   "subject TEXT, "
                   "fromname TEXT, "
                   "frommail TEXT, "
                   "mid TEXT);");
        query.exec("CREATE TABLE main.files ("
                   "id INTEGER PRIMARY KEY, "
                   "idmail INTEGER, "
                   "file BLOB );");

    }
    else
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("mail.db");
        db.open();
    }
    model = new QSqlTableModel(this);
}
mail::~mail()
{  
    delete ui;
}
//test.pop3.110
//Qwertyasdfgh
//pop.gmail.com
//    test.pop.110@yandex.ru
//    Asdfgh
//http://www.codenet.ru/webmast/pop3.php
///http://ru.wikipedia.org/wiki/POP3

void mail::closeEvent(QCloseEvent *event)
 {
    qDebug()<<list.isEmpty();
    while (!list.isEmpty())
        delete list.takeFirst();

}

void mail::on_action_triggered()
{
    ui->tableView->hide();
    ui->textBrowser->show();
}
void mail::on_actionGet_triggered()
{
    QTreeWidgetItem *item =new QTreeWidgetItem;
    item->setText(0,"yandex");
    ui->treeWidget->addTopLevelItem(item);
    fmail mails;
    if(mails.connectToHost("pop.yandex.ru")!=0)
        qDebug()<<"не коннект";
    mails.login("test.pop.110","Asdfgh");
    int i = mails.list();
    QSqlQuery query;
    if (i>0)
        for(int index = 1;index<=i;index++)
        {
            QByteArray tm = mails.retr(index);
//            qDebug()<<tm;
            parse(tm);
            query.prepare("INSERT INTO main.mail ("
                          "catalog,"
                          "name, "
                          "size, "
                          "subject, "
                          "fromname, "
                          "frommail, "
                          "mid, "
                          "body ) VALUES('yandex','name-name',?,?,?,?,?,?);");
            query.addBindValue(getsize(tm).data());
            query.addBindValue(getsubject(tm).data());
            query.addBindValue(getfrom(tm).data());
            query.addBindValue(getfrommail(tm).data());
            query.addBindValue(getmid(tm).data());
            query.addBindValue(tm.data());
            query.exec();
            //            qDebug()<<"sql"<<query.lastError().text()<<query.lastQuery();
        }
    qDebug()<<"close "<<mails.close();
    //
}
QByteArray mail::getsize(QByteArray qb){
    int begin, end;
    begin = qb.indexOf("+OK ");
    begin+=4;
    end = qb.indexOf(" octets.");
    return QByteArray::fromBase64(qb.mid(begin, end-begin));
}

QByteArray mail::getsubject(QByteArray qb){
    int begin, end;
    begin = qb.indexOf("Subject: =?utf-8?b?");
    begin+=20;
    end = qb.indexOf("=?=");
    QByteArray part1 = QByteArray::fromBase64(qb.mid(begin, end-begin));
    begin = qb.indexOf("=?utf-8?b?");
    begin +=11;
    end = qb.indexOf("=?=");
    QByteArray part2 = QByteArray::fromBase64(qb.mid(begin, end-begin));
    part1+=part2;
    return part1;
}
QByteArray mail::getfrommail(QByteArray qb) {
    int begin, end;
    begin = qb.indexOf("?= <");
    begin+=4;
    end = qb.indexOf(">");
    return QByteArray::fromBase64(qb.mid(begin, end-begin));
}
QByteArray mail::getfrom(QByteArray qb) {
    int begin, end;
    begin = qb.indexOf("From: =?utf-8?b?");
    begin+=17;
    end = qb.indexOf("?=");
    return QByteArray::fromBase64(qb.mid(begin, end-begin));

}
QByteArray mail::getmid(QByteArray qb) {
    int begin, end;
    begin = qb.indexOf("Message-Id: <");
    begin+=14;
    end = qb.indexOf(">");
    return QByteArray::fromBase64(qb.mid(begin, end-begin));

}

void mail::init()
{

}
void mail::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //    qDebug()<<"item "<<QString("catalog =%1").arg( item->text(0));

    ui->textBrowser->hide();
    ui->tableView->show();
    model->setTable("mail");
    model->setFilter(QString("catalog = '%1'").arg( item->text(0)));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
}
void mail::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->tableView->hide();
    ui->textBrowser->show();
    ui->textBrowser->setText(model->record(index.row()).value(4).toString());
}


void mail::parse(QByteArray arr)
{
    int beginBoundary = arr.indexOf("boundary=");
    beginBoundary  += 10;
    int endBoundary = arr.indexOf("\"",beginBoundary);
    int sizeBoundary =endBoundary-beginBoundary;
    QByteArray boundary = arr.mid(beginBoundary,sizeBoundary);
    QList<QByteArray> parts;
    int beginPart,endPart;
    beginPart = arr.indexOf(boundary,endBoundary);
    beginPart = beginPart + sizeBoundary;
    while(arr.indexOf(boundary,beginPart)>0)
    {

        endPart = arr.indexOf(boundary,beginPart);
        parts.append(arr.mid(beginPart+2,(endPart - beginPart)));
        QByteArray tmmp =arr.mid(beginPart+2,(endPart - beginPart));
        int tm1=tmmp.indexOf("\r\n\r\n");
        qDebug()<<tmmp.indexOf("Content-Type: text/html; charset=\"utf-8\"");
        if ((tmmp.indexOf("Content-Type: text")>=0) )
        {
            if (tmmp.indexOf("Content-Transfer-Encoding: base64")>=0)
                tmmp = QByteArray::fromBase64(tmmp.mid(tm1));
            else
                tmmp = tmmp.mid(tm1);
            QTextBrowser  *l;
            l = new QTextBrowser();
            l->setHtml(tmmp.data());
            l->show();
            list.append(l);
        }
        if ((tmmp.indexOf("Content-Type: text/plain; charset=UTF-8;")>=0) &&(tmmp.indexOf("Content-Transfer-Encoding: 8bit")>=0) )
        {
            tmmp = tmmp.mid(tm1);
            QTextBrowser  *l;
            l = new QTextBrowser();
            l->setHtml(tmmp.data());
            l->show();
            list.append(l);
        }
        if ((tmmp.indexOf("Content-Type: image")>=0) )
        {
            tmmp = QByteArray::fromBase64(tmmp.mid(tm1));
            QLabel  *l;
            l = new QLabel();
            QPixmap p;
            p.loadFromData(tmmp);
            l->setPixmap(p);
            l->show();
            list.append(l);
        }

        beginPart = endPart + sizeBoundary;
    }

}
