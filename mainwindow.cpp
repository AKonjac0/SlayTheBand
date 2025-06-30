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

#include "Arrow.h"
#include "HoverButton.h"
#include "Defs.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SlayTheBand");

    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // setFixedSize(1440, 1080);
    // QPixmap bkgnd(":/image/images/Background1.jpg");
    // bkgnd = bkgnd.scaled(this -> size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


    page_manager = new PageManager(this, this->width(), this->height());
    QWidget *page = page_manager->get_now_page();

    // Arrow *arrow = new Arrow(this);
    // arrow->show();

    card_manager = new Card_Manager(page);
    card_view = new CardView(card_manager, page);
    QPair<Player*,Enemy*>* opponents = new QPair(
        new Player("uika", PLAYER_MAX_HP, page, PLAYER_MAX_MP),
        new Enemy("soyo", ENEMY_MAX_HP, page)
    );
    character_animation = new CharacterAnimation(opponents);
    character_animation->show();

    // 音乐播放器
    music = new Music_Manager();
    music->play(":/music/OST/haruhikage.wav");


}

MainWindow::~MainWindow()
{
    delete card_manager;
    delete card_view;
    delete character_animation;
    delete page_manager;
    delete music;
    delete ui;
}



