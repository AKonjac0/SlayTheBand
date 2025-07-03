#include "mainwindow.h"
#include <QRandomGenerator>
#include <QGraphicsProxyWidget>
#include "Defs.h"
using namespace std;

MainWindow::MainWindow(Card_Manager *manager, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SlayTheBand");
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    page_manager = new PageManager(this, manager, this->width(), this->height());
}

MainWindow::~MainWindow()
{
    qDebug() << "mainwindow close";
    delete page_manager;
}



