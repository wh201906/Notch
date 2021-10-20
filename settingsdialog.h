#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui
{
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QSettings* settings, QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_sizeSlider_valueChanged(int value);

    void on_fixPositionBox_clicked(bool checked);

private:
    Ui::SettingsDialog *ui;
    QSettings* settings;

    void loadSettings();
signals:
    void setWindowSize();
    void setPositionFixed();
};

#endif // SETTINGSDIALOG_H
