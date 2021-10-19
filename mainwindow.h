#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void contextMenuEvent(QContextMenuEvent *e) override;

private:
    Ui::MainWindow *ui;

    // drag
    QPoint startPos;
    bool isMoving = false;

    // menu
    QMenu* contextMenu;
    QAction* action_closeNotch;
    QAction* action_findPosition;
    QAction* action_myInfo;
    QAction* action_currVersion;
    QAction* action_checkUpdate;
    void initMenu();
    void findPosition();
};
#endif // MAINWINDOW_H
