#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    QBitmap bitmap = QPixmap(":/bg/res/notch.png").mask();
    bitmap = bitmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
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
