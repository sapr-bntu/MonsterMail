#ifndef MAIL_H
#define MAIL_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtSql>
#include <QTreeWidget>
#include <QtGui>

namespace Ui {
    class mail;
}

class mail : public QMainWindow
{
    Q_OBJECT

public:
    explicit mail(QWidget *parent = 0);
    ~mail();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void init();
    void on_action_triggered();
    void on_actionGet_triggered();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_tableView_doubleClicked(const QModelIndex &index);
    void parse(QByteArray arr);
    QByteArray getfrom(QByteArray qb);
    QByteArray getfrommail(QByteArray qb);
    QByteArray getsize(QByteArray qb);
    QByteArray getsubject(QByteArray qb);
    QByteArray getmid(QByteArray qb);
private:
    Ui::mail *ui;
    QSqlTableModel *model;
    QList<QWidget*> list;
};

#endif // MAIL_H
