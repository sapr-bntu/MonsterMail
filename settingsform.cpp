#include "settingsform.h"
#include <mainwindow.h>
#include "ui_settingsform.h"
#include <QLineEdit>
#include <QSettings>

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
   QSettings *settingObject = new QSettings("setting.ini",QSettings::IniFormat,0);
   settingObject->beginGroup("Proxy");
  QString use = settingObject->value("UseProxy","0").toString();
  settingObject->endGroup();
  if(use=="1")
  {
      ui->checkBox->setChecked(true);
      ui->groupBox->setEnabled(true);
  }
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
void SettingsForm::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()!=true)
    {
       ui->groupBox->setEnabled(false);
    }
    else
    {
       ui->groupBox->setEnabled(true);
    }
}

void SettingsForm::on_pushButtonSave_clicked()
{
   QSettings *settingObject = new QSettings("setting.ini",QSettings::IniFormat,0);

    settingObject->beginGroup("MailServerSettings");
    settingObject->setValue("MailServer",ui->lineEditServer->text());
    settingObject->setValue("Port",ui->lineEditPort->text());
    settingObject->setValue("Login",ui->lineEditLogin->text());
    settingObject->setValue("Password",ui->lineEditPassword->text());
    settingObject->endGroup();

   settingObject->beginGroup("Proxy");

   QString useProxy = "0";
   if(ui->checkBox->isChecked()==true)
   {
       useProxy = "1";
   }
   settingObject->setValue("UseProxy",useProxy);
    settingObject->setValue("ProxyServer",ui->lineEditProxySer->text());
    settingObject->setValue("ProxyPort",ui->lineEditProxyPort->text());
    settingObject->setValue("ProxyUserName",ui->lineEditProxyUserName->text());
    settingObject->setValue("ProxyPassword",ui->lineEditProxyPass->text());
    settingObject->endGroup();
}

void SettingsForm::on_pushButtonExit_clicked()
{
    this->close();
}
