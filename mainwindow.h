#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "PageManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Card_Manager *maanger, QWidget *parent = nullptr);
    ~MainWindow();
    PageManager *get_page_manager(){return page_manager;}

private:
    PageManager *page_manager;
};
#endif // MAINWINDOW_H
