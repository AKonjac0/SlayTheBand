#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsOpacityEffect>
#include "Defs.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SlayTheBand");

    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    page_manager = new PageManager(this, this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete page_manager;
    delete ui;
}



