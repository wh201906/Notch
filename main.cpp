#include "mainwindow.h"

#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    // A trick to handle non-ascii path
    // The application cannot find the plugins when the path contains non ascii characters.
    // However, the plugins will be load after creating MainWindow(or QApplication?).
    // QDir will handle the path correctly.
    QDir* pluginDir = new QDir;
    if(pluginDir->cd("plugins")) // has plugins folder
    {
        qputenv("QT_PLUGIN_PATH", pluginDir->absolutePath().toLocal8Bit());
    }
    delete pluginDir;

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
