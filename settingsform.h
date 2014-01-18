#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

    
private slots:
     void on_checkBox_clicked();

     void on_pushButtonSave_clicked();

     void on_pushButtonExit_clicked();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
