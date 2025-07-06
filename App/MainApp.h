#ifndef MAINAPP_H
#define MAINAPP_H
#include "mainwindow.h"
#include "RoleManager.h"

#include "Combat.h"
#include "Map.h"
class MainApp{
public:
    MainApp();
    ~MainApp();
private:
    MainWindow *mainwindow;
    Combat *combat;
    RoleManager *roleManager;
    Map *map;

};
#endif // MAINAPP_H
