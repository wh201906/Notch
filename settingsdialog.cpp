#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QSettings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->settings = settings;
    loadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_windowSizeSlider_valueChanged(int value)
{
    settings->setValue("WindowSize", value);
    ui->windowSizeLabel->setText(QString::number(value));
    emit setWindowSize();
}


void SettingsDialog::on_fixPositionBox_clicked(bool checked)
{
    settings->setValue("PositionFixed", checked);
    emit setPositionFixed();
}

void SettingsDialog::loadSettings()
{
    ui->windowSizeSlider->setValue(settings->value("WindowSize").toInt());
    ui->windowSizeLabel->setText(QString::number(ui->windowSizeSlider->value()));
    ui->windowRatioBox->setValue(settings->value("WindowRatio").toDouble());
    ui->cornerRatioBox->setValue(settings->value("CornerRatio").toDouble());
    ui->fixPositionBox->setChecked(settings->value("PositionFixed").toBool());
    ui->hideCursorBox->setChecked(settings->value("HideCursor").toBool());
}

void SettingsDialog::on_windowRatioBox_valueChanged(double arg1)
{
    settings->setValue("WindowRatio", arg1);
    emit setWindowSize();
}


void SettingsDialog::on_cornerRatioBox_valueChanged(double arg1)
{
    settings->setValue("CornerRatio", arg1);
    emit setCornerSize();
}


void SettingsDialog::on_hideCursorBox_clicked(bool checked)
{
    settings->setValue("HideCursor", checked);
    emit setCursorHiding();
}

