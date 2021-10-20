#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    loadSettings();
    reshape();
    findPosition();
    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    action_closeNotch = new QAction(tr("Close"), this);
    action_findPosition = new QAction(tr("Find position"), this);
    action_settings = new QAction(tr("Settings"), this);
    action_myInfo = new QAction("wh201906", this);
    action_currVersion = new QAction(tr("Ver: ") + QApplication::applicationVersion().section('.', 0, -2), this); // ignore the 4th version number
    action_checkUpdate = new QAction(tr("Check Update"), this);
    connect(action_closeNotch, &QAction::triggered, [ = ]()
    {
        close();
    });
    connect(action_findPosition, &QAction::triggered, [ = ]()
    {
        findPosition();
    });
    connect(action_settings, &QAction::triggered, [ = ]()
    {
        SettingsDialog dialog(settings);
        connect(&dialog, &SettingsDialog::setWindowSize, this, QOverload<>::of(&MainWindow::setWindowSize));
        connect(&dialog, &SettingsDialog::setPositionFixed, this, QOverload<>::of(&MainWindow::setPositionFixed));
        dialog.exec();
    });
    connect(action_myInfo, &QAction::triggered, [ = ]()
    {
        QDesktopServices::openUrl(QUrl("https://github.com/wh201906"));
    });
    action_currVersion->setEnabled(false);
    connect(action_checkUpdate, &QAction::triggered, [ = ]()
    {
        QDesktopServices::openUrl(QUrl("https://github.com/wh201906/Notch/releases"));
    });

    contextMenu = new QMenu();
    contextMenu->addAction(action_closeNotch);
    contextMenu->addAction(action_findPosition);
    contextMenu->addAction(action_settings);
    contextMenu->addSeparator();
    contextMenu->addAction(action_myInfo);
    contextMenu->addAction(action_currVersion);
    contextMenu->addAction(action_checkUpdate);

}

void MainWindow::reshape()
{
    QBitmap bitmap = QPixmap(":/bg/res/notch.png").mask();
    bitmap = bitmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setMask(bitmap);
}

void MainWindow::findPosition()
{
    int screenWidth = QApplication::desktop()->width();
    move((screenWidth - width()) / 2, 0);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && !positionFixed)
    {
        startPos = e->pos();
        isMoving = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(isMoving)
    {
        this->move(geometry().topLeft() + (e->pos() - startPos));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    isMoving = false;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *e)
{
    contextMenu->exec(e->globalPos());
}

void MainWindow::setWindowSize(const QSize& size)
{
    bool refind = (geometry().x() == (QApplication::desktop()->width() - width()) / 2);
    setFixedSize(size);
    if(refind)
        findPosition();
    reshape();
}

void MainWindow::setWindowSize()
{
    int size = settings->value("WindowSize").toInt();
    int ratio = settings->value("WindowRatio").toInt();
    QSize windowSize(size * ratio * 5, size * 5);
    setWindowSize(windowSize);
}

void MainWindow::setPositionFixed(bool isFixed)
{
    positionFixed = isFixed;
}

void MainWindow::setPositionFixed()
{
    setPositionFixed(settings->value("PositionFixed").toBool());
}

void MainWindow::loadSettings()
{
    // default settings is defined there
    int defaultWindowSize = 8;
    int deaultWindowRatio = 6;
    bool PositionFixed = false;
    if(settings->value("WindowSize").isNull())
        settings->setValue("WindowSize", defaultWindowSize);
    if(settings->value("WindowRatio").isNull())
        settings->setValue("WindowRatio", deaultWindowRatio);
    if(settings->value("PositionFixed").isNull())
        settings->setValue("PositionFixed", PositionFixed);

    // init by settings
    setWindowSize();
    setPositionFixed();
}
