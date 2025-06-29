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

#define PLAYER_MAX_HP 100
#define PLAYER_MAX_MP 3

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题和大小
    setWindowTitle("SlayTheBand");
    setFixedSize(1920, 1080);
    QPixmap bkgnd(":/image/images/Background1.jpg");
    bkgnd = bkgnd.scaled(this -> size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);

    this -> setPalette(palette);

    card_manager = new Card_Manager(this);
    card_view = new CardView(card_manager, this);


    player = new Player("uika", PLAYER_MAX_HP, this, PLAYER_MAX_MP);
    player->show_character(300, 280, 248, 328);
    music = new Music_Manager();
    music->play(":/music/OST/haruhikage.wav");

}

MainWindow::~MainWindow()
{
    delete card_manager;
    delete card_view;
    delete player;
    delete music;
    delete ui;
}



