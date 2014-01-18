#include <QtGui/QApplication>
#include "mail.h"
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    mail w;
    qDebug() << QByteArray::fromBase64("0KHQvtCx0LXRgNC40YLQtSDQstGB0Y4g0L/QvtGH0YLRgyDQsiDRjdGC0L4");
    qDebug() << QByteArray::fromBase64("0YIg0Y/RidC40Lo");
    w.show();
    return a.exec();
}
