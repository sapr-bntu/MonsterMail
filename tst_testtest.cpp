//#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QTest>
#include <QtCore>
#include <QtGui/QApplication>
#include <QDialog>
#include <QtGui>
#include <QtSql>
#include <QtNetwork>
#include "fmail.h"

class TestTest : public QObject
{
    Q_OBJECT
    char* login;// = "test.pop.110@yandex.ru";
    char* pass;// = "Asdfgh";

public:
    TestTest();
    bool Connected();

private Q_SLOTS:
 void testCase1();
 void testCase2();
 void testCase3();
 void testCase4();
 void testCase5();
 void testCase6();
 void testCase7();
 void testCase8();
};

TestTest::TestTest()
{
    TestTest::login = "test.pop.110@yandex.ru";
    TestTest::pass = "Asdfgh";
}

bool TestTest::Connected() {
    fmail fm;
    if(fm.connectToHost("pop.yandex.ru", 110))
        if(fm.login(login, pass)) return true;
            else return false;
    else return false;
}

void TestTest::testCase1()
{
    fmail fm;
    bool state = fm.connectToHost("pop.yandex.ru", 110);
    QVERIFY2(state != true, "Can't connect to the server!");
}

void TestTest::testCase2()
{
    fmail fm;
    bool connect = fm.connectToHost("pop.yandex.ru");
    bool auth;
    if (connect == false) {
        QVERIFY2(connect == false, "Can't connect to the server");
    } else {
        auth = fm.login(login, pass);
        if(auth) {
            int lst = fm.list();
            QVERIFY2(lst != -1, "Can't get message list");
        } else {
            QVERIFY2(auth == false, "Can't authorize to test.pop.110@yandex.ru");
        }
    }

}

void TestTest::testCase3()
{
    fmail fm;
    bool flag;
    if (fm.connectToHost("pop.yandex.ru")) {
        flag = fm.login("test.pop.110@yandex.ru", "Asdfgh");
    }
    QVERIFY2(flag == FALSE, "Can't authorize to test.pop.110@yandex.ru");
}
void TestTest::testCase4()
{
    fmail fm;
    Connected();
    QString str = fm.mails();
    QVERIFY2(str.contains("bad") == true, "Can't read mail");
}
void TestTest::testCase5()
{
    fmail fm;
    Connected();
    bool flag = fm.close();
    QCOMPARE(FALSE, flag);
}
void TestTest::testCase6()
{
    fmail fm;
    Connected();
    int flag = fm.list();
    QCOMPARE(flag, -1);
}
void TestTest::testCase7()
{
    fmail fm;
    Connected();
    QByteArray empty;
    QByteArray arr = fm.retr(1);
    QCOMPARE(arr, empty);
}
void TestTest::testCase8()
{
    fmail fm;
    Connected();
    QByteArray empty;
    QByteArray arr = fm.top(0, 10);
    QCOMPARE(arr, empty);
}

QTEST_MAIN(TestTest)

#include "tst_testtest.moc"
