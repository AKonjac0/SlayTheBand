#ifndef MAINAPP_H
#define MAINAPP_H
#include "mainwindow.h"
#include "Card_Manager.h"
#include "RoleManager.h"

class MainApp{
public:
    MainApp();
    ~MainApp();
private:
    MainWindow *mainwindow;
    Card_Manager *cardManager;
    RoleManager *roleManager;
};
#endif // MAINAPP_H
