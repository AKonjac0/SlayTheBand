#ifndef MAINAPP_H
#define MAINAPP_H
#include "mainwindow.h"
#include "Card_Manager.h"
#include "RoleManager.h"

#include "Combat.h"
class MainApp{
public:
    MainApp();
    ~MainApp();
private:
    MainWindow *mainwindow;
    Combat *combat;
    RoleManager *roleManager;
};
#endif // MAINAPP_H
