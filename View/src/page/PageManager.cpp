#include <QPushButton>
#include <QtMultimediaWidgets>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>
#include "Defs.h"
#include "PageManager.h"
#include "CardRewardPage.h"
#include "HomePage.h"
#include "MapPage.h"
#include "Combat.h"

PageManager::PageManager(QWidget *parent, Card_Manager *manager, int page_width, int page_height)
    : card_manager(manager), parent(parent), page_width(page_width), page_height(page_height) {

    music = new Music_Manager(parent);
    music->play("../../OST/ready_to_go.wav");

    //创建页面0 主界面
    page0 = new HomePage(parent);
    QAbstractButton::connect(page0->startButton, &QPushButton::clicked, [this](){
        qDebug() << "Game Start";
        enterGame();
        page0->videoPlayer->stop();
        switchToPage(page2, PageAnimationDirection::RightToLeft);

    });

    // 创建页面2 地图界面
    page2 = new MapPage(parent);

    // 创建页面1 战斗界面
    page1 = new BattlePage(parent);
    // card_manager = new Card_Manager(page1);
    card_view = new CardView(card_manager, page1);
    player = new Player("uika", PLAYER_MAX_HP, page1, PLAYER_MAX_MP); // test only
    enemy = new Enemy("soyo", ENEMY_MAX_HP, page1); //
    combat = new Combat(page1, card_view, player);


    HoverButton *next_round = card_view->getButton()->get_next_round_button();
    QObject::connect(card_view->getButton(), &Card_Button::finish_round, page1, [this](){
        combat->endOfRound();
    });

    QPushButton *enemy_btn = enemy->getButton();
    QObject::connect(enemy_btn, &QPushButton::clicked, [this](){
        qDebug() << "Enemy";
        combat->setEnemy(enemy);
        combat->playACard();
    });

    QAbstractButton::connect(page1->switchBtn, &QPushButton::clicked, [this](){
        switchToPage(page2, PageAnimationDirection::RightToLeft);
    });

    QAbstractButton::connect(page2->switchBtn, &QPushButton::clicked, [this](){
        switchToPage(page1, PageAnimationDirection::LeftToRight);
    });
    auto spire_tower = page2->spire_tower;
    for(auto &level : spire_tower){
        for(RoomButton *room : level){
            QAbstractButton::connect(room, &QPushButton::clicked, [room, level, this](){
                if(room->getVisit() == visitType::opened){
                    qDebug() << "next Level";
                    for(RoomButton *r : level) if(room != r) r->setVisit(closed);
                    room->openNext();
                    room->setVisit(visited);

                    card_view->getButton()->init_combat();
                    // combat->new_combat();
                    switchToPage(page1, PageAnimationDirection::LeftToRight);
                    page2->switchBtn->show();
                }
            });
        }
    }


    // QAbstractButton::connect(page2->level1, &QPushButton::clicked, [this](){
    //     qDebug() << "Level 1";
    //     card_view->getButton()->init_combat();
    //     switchToPage(page1, PageAnimationDirection::LeftToRight);
    //     // opacity
    //     // page2->level1->setGraphicsEffect();


    //     page2->switchBtn->show();
    // });


    page3 = new CardRewardPage(card_manager, parent);
    QAbstractButton::connect(page3->confirmBtn, &QPushButton::clicked, [this]() {
        // page3->deleteReward();
        // card_manager->new_combat();
        // card_view->getButton()->init_combat();
        switchToPage(page2, PageAnimationDirection::RightToLeft);
    });

    QPushButton *reward_btn = new QPushButton(page1);
    reward_btn->setText("奖励");
    reward_btn->setStyleSheet("QPushButton{border-image: url(:image/images/normalCardReward.png);}");
    reward_btn->resize(64, 64);
    reward_btn->move(10, 10);
    QAbstractButton::connect(reward_btn, &QPushButton::clicked, [this]() {
        // page3->newReward();
        page2->switchBtn->hide();
        switchToPage(page3, PageAnimationDirection::LeftToRight);
    });

    // player->setHP(10);
    // qDebug() << "Test setHP: Player HP set to:" << player->getHP();
    // player->HP_change(-5);
    // qDebug() << "Test HP_change: Player HP changed to:" << player->getHP();
    // player->setMaxHP(200);
    // qDebug() << "Test setMaxHP: Player max HP set to:" << player->getMaxHP();
    // player->maxHP_change(50);
    // qDebug() << "Test maxHP_change: Player max HP changed to:" << player->getMaxHP();
    // player->setMP(5);
    // qDebug() << "Test setMP: Player MP set to:" << player->getMP(); // 3
    // player->MP_change(3);
    // qDebug() << "Test MP_change: Player MP changed to:" << player->getMP();
    // player->setMaxMP(100);
    // qDebug() << "Test setMaxMP: Player max MP set to:" << player->getMaxMP();
    // player->maxMP_change(20);
    // qDebug() << "Test maxMP_change: Player max MP changed to:" << player->getMaxMP();

    // enemy->setHP(10);
    // qDebug() << "Test setHP: Enemy HP set to:" << enemy->getHP();
    // enemy->HP_change(-5);
    // qDebug() << "Test HP_change: Enemy HP changed to:" << enemy->getHP();
    // enemy->setMaxHP(200);
    // qDebug() << "Test setMaxHP: Enemy max HP set to:" << enemy->getMaxHP();
    // enemy->maxHP_change(50);
    // qDebug() << "Test maxHP_change: Enemy max HP changed to:" << enemy->getMaxHP();

    page0->show();
    page1->show();
    page2->show();
    page3->show();
    page0->raise();
    now_page = page0;
}

PageManager::~PageManager() {
    qDebug() << "dtor";
    // delete card_manager;
    delete card_view;
    delete music;
    delete player;
    delete enemy;
    delete combat;
    delete page0;
    delete page1;
    delete page2;
    delete page3;
}

void PageManager::switchToPage(QWidget *targetPage, PageAnimationDirection direction) {
    if (now_page == targetPage || animationInProgress) {
        return;
    }

    animationInProgress = true;
    QWidget *currentPage = now_page;
    now_page = targetPage;

    // 创建动画组
    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;

    // 当前页面动画 - 淡出
    QPropertyAnimation *fadeOut = new QPropertyAnimation(currentPage, "windowOpacity");
    fadeOut->setDuration(300);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    // 当前页面动画 - 滑动
    QPropertyAnimation *slideOut = new QPropertyAnimation(currentPage, "pos");
    slideOut->setDuration(300);
    slideOut->setStartValue(currentPage->pos());

    // 目标页面动画 - 淡入
    QPropertyAnimation *fadeIn = new QPropertyAnimation(targetPage, "windowOpacity");
    fadeIn->setDuration(300);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    // 目标页面动画 - 滑动
    QPropertyAnimation *slideIn = new QPropertyAnimation(targetPage, "pos");
    slideIn->setDuration(300);

    // 根据方向设置滑动动画
    if (direction == PageAnimationDirection::RightToLeft) {
        // 从右向左滑动
        targetPage->move(page_width, 0);
        slideIn->setStartValue(QPoint(page_width, 0));
        slideIn->setEndValue(QPoint(0, 0));

        slideOut->setEndValue(QPoint(-page_width, 0));
    } else {
        // 从左向右滑动
        targetPage->move(-page_width, 0);
        slideIn->setStartValue(QPoint(-page_width, 0));
        slideIn->setEndValue(QPoint(0, 0));

        slideOut->setEndValue(QPoint(page_width, 0));
    }

    // 将动画添加到动画组
    animationGroup->addAnimation(fadeOut);
    animationGroup->addAnimation(slideOut);
    animationGroup->addAnimation(fadeIn);
    animationGroup->addAnimation(slideIn);

    // 动画完成后的处理
    QAbstractButton::connect(animationGroup, &QParallelAnimationGroup::finished, [this, animationGroup, currentPage, targetPage]() {
        // 重置当前页面位置和透明度
        currentPage->move(0, 0);
        currentPage->setWindowOpacity(1.0);

        // 清理动画对象
        animationGroup->deleteLater();

        animationInProgress = false;
        if(currentPage == page0) delete page0, page0 = nullptr;

        if(targetPage == page3) page3->newReward();
        else if(targetPage == page1){
            qDebug() << "return to page1";

            // QEventLoop loop;
            // QTimer::singleShot(1000, &loop, SLOT(quit()));
            // loop.exec();
            // if(!loop.isRunning()){
            // }
        }
    });

    // 开始动画
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);

    // 提升目标页面
    targetPage->raise();

}

void PageManager::enterGame() {
    music->play("../../OST/haruhikage.wav");

    player->show(
        PLAYER_POSITION_X,
        SCREEN_HEIGHT-PLAYER_POSITION_Y-player->getSize().height(),
        player->getSize().width(),
        player->getSize().height()
    );

    enemy->show(
        SCREEN_WIDTH-PLAYER_POSITION_X-enemy->getSize().width(),
        SCREEN_HEIGHT-PLAYER_POSITION_Y-enemy->getSize().height(),
        enemy->getSize().width(),
        enemy->getSize().height()
    );

    // character_animation->show();

}

Card_Manager *PageManager::getCardManager() {
    return card_manager;
}

CardView *PageManager::getCardView() {
    return card_view;
}
