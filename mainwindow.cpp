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
#include "Card_Manager.h"
#include "Player.h"
#include "Enemy.h"
#include "Music_Manager.h"
#define PLAYER_MAX_HP 100
#define PLAYER_MAX_MP 3

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题和大小
    setWindowTitle("按钮动画效果演示");
    resize(1920, 1080);

    card_manager = new Card_Manager(this);
    card_view = new CardView(card_manager, this);


    Player* player = new Player("slime_balloon", PLAYER_MAX_HP, this, PLAYER_MAX_MP);
    player->show_character(100,700,100,200);
    Music_Manager *music = new Music_Manager();
    music->play(":/music/OST/haruhikage.wav");

}

MainWindow::~MainWindow()
{
    delete card_manager;
    delete card_view;
    delete ui;
}



