#include "MainApp.h"
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainApp *mainapp = new MainApp();


    return app.exec();
}

