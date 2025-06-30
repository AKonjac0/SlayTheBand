#include "mainwindow.h"
#include "Arrow.h"
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

