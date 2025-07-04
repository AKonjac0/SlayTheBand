#ifndef MAINAPP_H
#define MAINAPP_H
#include "mainwindow.h"
#include "Card_Manager.h"
class MainApp{
public:
    MainApp();
    ~MainApp();
private:
    MainWindow *mainwindow;
    Card_Manager *manager;
};
#endif // MAINAPP_H
