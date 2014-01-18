#ifndef FORMNEWMESSAGE_H
#define FORMNEWMESSAGE_H

#include <QWidget>

namespace Ui {
class FormNewMessage;
}

class FormNewMessage : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormNewMessage(QWidget *parent = 0);
    ~FormNewMessage();

    
private slots:
    void on_pushButton_clicked();

private:
    Ui::FormNewMessage *ui;
};

#endif // FORMNEWMESSAGE_H
