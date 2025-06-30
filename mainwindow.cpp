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
    setWindowTitle("SlayTheBand");
    setFixedSize(1920, 1080);

    page_manager = new PageManager(this, this->width(), this->height());
    QWidget *page = page_manager->get_now_page();

    card_manager = new Card_Manager(page);
    card_view = new CardView(card_manager, page);

    player = new Player("uika", PLAYER_MAX_HP, page, PLAYER_MAX_MP);
    player->show_character(300, 280, 248, 328);

    // 音乐播放器
    music = new Music_Manager();
    music->play(":/music/OST/haruhikage.wav");
}

MainWindow::~MainWindow()
{
    delete card_manager;
    delete card_view;
    delete player;
    delete page_manager;
    delete music;
    delete ui;
}



