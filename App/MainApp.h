#ifndef MAINAPP_H
#define MAINAPP_H
#include "mainwindow.h"
#include "Combat.h"
class MainApp{
public:
    MainApp();
    ~MainApp();
private:
    MainWindow *mainwindow;
    // Card_Manager *manager;
    Combat *combat;
};
#endif // MAINAPP_H
