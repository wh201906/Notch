#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    QBitmap bitmap(width(), height());
    QPainter painter(&bitmap);
    painter.drawPixmap(geometry(), QPixmap(":/bg/res/notch.png"));
    setMask(bitmap);
    int screenWidth = QApplication::desktop()->width();
    move((screenWidth - width()) / 2, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    isMoving = false;
}
