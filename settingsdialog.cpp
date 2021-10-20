#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QSettings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->settings = settings;
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_sizeSlider_valueChanged(int value)
{
    settings->setValue("WindowSize", value);
    emit setWindowSize();
}


void SettingsDialog::on_fixPositionBox_clicked(bool checked)
{
    settings->setValue("PositionFixed", checked);
    emit setPositionFixed();
}

void SettingsDialog::loadSettings()
{
    ui->sizeSlider->setValue(settings->value("WindowSize").toInt());
    ui->fixPositionBox->setChecked(settings->value("PositionFixed").toBool());
}
