#include "mainwindow.h"
#include <QRandomGenerator>
#include <QGraphicsProxyWidget>
#include "Defs.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SlayTheBand");
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    page_manager = new PageManager(this, this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete page_manager;
}



