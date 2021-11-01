#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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

private slots:
    void setWindowSize(const QSize& size);
    void setWindowSize();  // use parameters in settings
    void setPositionFixed(bool isFixed);
    void setPositionFixed(); // use parameters in settings
    void setCornerSize(double ratio);
    void setCornerSize();
    void setCursorHiding(bool isHiding);
    void setCursorHiding();
private:
    Ui::MainWindow *ui;

    // drag
    QPoint startPos;
    bool isMoving = false;
    bool positionFixed = false;

    // menu
    QMenu* contextMenu;
    QAction* action_closeNotch;
    QAction* action_findPosition;
    QAction* action_settings;
    QAction* action_myInfo;
    QAction* action_currVersion;
    QAction* action_checkUpdate;

    // settings
    QSettings* settings;

    // helper functions
    void initMenu();
    void findPosition();
    void reshape();
    void loadSettings();
};
#endif // MAINWINDOW_H
