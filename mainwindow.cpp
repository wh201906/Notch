#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QBitmap bitmap = QPixmap(":/bg/res/notch.png").mask();
    bitmap = bitmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setMask(bitmap);
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
    connect(action_myInfo, &QAction::triggered, [ = ]()
    {
        QDesktopServices::openUrl(QUrl("https://github.com/wh201906"));
    });
    connect(action_checkUpdate, &QAction::triggered, [ = ]()
    {
        QDesktopServices::openUrl(QUrl("https://github.com/wh201906/Notch/releases"));
    });

    contextMenu = new QMenu();
    contextMenu->addAction(action_closeNotch);
    contextMenu->addAction(action_findPosition);
    contextMenu->addSeparator();
    contextMenu->addAction(action_myInfo);
    action_currVersion->setEnabled(false);
    contextMenu->addAction(action_currVersion);
    contextMenu->addAction(action_checkUpdate);

}

void MainWindow::findPosition()
{
    int screenWidth = QApplication::desktop()->width();
    move((screenWidth - width()) / 2, 0);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
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
