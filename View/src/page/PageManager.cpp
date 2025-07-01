#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QtMultimediaWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include "Defs.h"
#include "PageManager.h"
#include "CardRewardPage.h"

PageManager::PageManager(QWidget *parent, int page_width, int page_height)
    : parent(parent), page_width(page_width), page_height(page_height) {

    music = new Music_Manager();
    music->play("../../OST/ready_to_go.wav");

    page0 = new QWidget(parent);
    page0->setGeometry(0, 0, page_width, page_height);
    page0->setAutoFillBackground(true);

    QGraphicsScene *scene = new QGraphicsScene(page0);
    QGraphicsView *graphicsView = new QGraphicsView(scene, page0);
    graphicsView->setGeometry(0, 0, 1920, 1080);
    graphicsView->setFrameShape(QFrame::NoFrame);
    graphicsView->setStyleSheet("background: transparent; border: none;");
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 创建视频项
    QGraphicsVideoItem *videoItem = new QGraphicsVideoItem;
    videoItem->setSize(QSizeF(1920, 1080));
    scene->addItem(videoItem);

    QAudioOutput *audioOutput = new QAudioOutput();

    // 创建媒体播放器
    QMediaPlayer *videoPlayer = new QMediaPlayer(page0);
    videoPlayer->setVideoOutput(videoItem);
    videoPlayer->setAudioOutput(audioOutput);
    videoPlayer->setLoops(-1);
    videoPlayer->setSource(QUrl::fromLocalFile("../../Videos/video1.mp4"));
    videoPlayer->play();

    // 创建按钮（作为图形代理控件）
    QPushButton *btn = new QPushButton("开始游戏");
    btn->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(50, 150, 250, 200);"
        "   color: white;"
        "   font-size: 16px;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}"
        );
    QGraphicsProxyWidget *buttonProxy = scene->addWidget(btn);
    buttonProxy->setPos(100, 100); // 按钮位置

    // 连接信号
    QAbstractButton::connect(btn, &QPushButton::clicked, [this, videoPlayer](){
        qDebug() << "Game Start";
        enterGame();
        videoPlayer->stop();
        switchToPage(page2, PageAnimationDirection::RightToLeft);
    });

    // 创建页面1
    page1 = new QWidget(parent);
    page1->setGeometry(0, 0, page_width, page_height);
    page1->setAutoFillBackground(true);
    // 加载并设置背景图片
    QPixmap bkgnd1(":/image/images/Background1.jpg");
    if(bkgnd1.isNull()) {
        qDebug() << "[page]: Failed to load background image!";
    } else {
        bkgnd1 = bkgnd1.scaled(page1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette1;
        palette1.setBrush(QPalette::Window, bkgnd1);
        page1->setPalette(palette1);
    }


    // 创建页面2
    page2 = new QWidget(parent);
    page2->setGeometry(0, 0, page_width, page_height);
    page2->setAutoFillBackground(true);
    QPixmap bkgnd2(":/image/images/map_page.png");
    if (bkgnd2.isNull()) {
        qDebug() << "[page2]: Failed to load background image!";
    } else {
        bkgnd2 = bkgnd2.scaled(page2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette2;
        palette2.setBrush(QPalette::Window, bkgnd2);
        page2->setPalette(palette2);
    }

    QPushButton *level1 = new QPushButton(page2);
    level1->resize(128, 128);
    level1->move(500, 500);
    level1->setStyleSheet("QPushButton{border-image: url(:image/images/monster.png);}");

    // 初始化页面2为透明并隐藏在右侧
    page2->setWindowOpacity(0.0);
    page2->move(page_width, 0);

    // 创建切换按钮1
    QPushButton *switchBtn1 = new QPushButton(page1);
    switchBtn1->move(1830, 20);
    switchBtn1->resize(64, 64);
    QString BtnPic = "QPushButton{border-image: url(:image/images/map.png);}";
    switchBtn1->setStyleSheet(BtnPic);

    // 创建切换按钮2
    QPushButton *switchBtn2 = new QPushButton(page2);
    switchBtn2->move(1830, 20);
    switchBtn2->resize(64, 64);
    switchBtn2->setStyleSheet(BtnPic);
    switchBtn2->hide();

    // 连接按钮信号到动画切换
    QAbstractButton::connect(switchBtn1, &QPushButton::clicked, [this](){
        switchToPage(page2, PageAnimationDirection::RightToLeft);
    });

    QAbstractButton::connect(switchBtn2, &QPushButton::clicked, [this](){
        switchToPage(page1, PageAnimationDirection::LeftToRight);
    });

    QAbstractButton::connect(level1, &QPushButton::clicked, [this, switchBtn2](){
        qDebug() << "Level 1";
        // card_view->getButton()->init_combat();
        switchToPage(page1, PageAnimationDirection::LeftToRight);
        switchBtn2->show();
    });


    card_manager = new Card_Manager(page1);
    card_view = new CardView(card_manager, page1);


    page3 = new CardRewardPage(card_manager, parent);
    page3->setGeometry(0, 0, page_width, page_height);
    page3->setAutoFillBackground(true);
    QPushButton *confirm_btn = new QPushButton(page3);
    confirm_btn->setText("确定");
    confirm_btn->resize(64, 64);
    confirm_btn->move(10, 10);
    QAbstractButton::connect(confirm_btn, &QPushButton::clicked, [this]() {
        // page3->deleteReward();
        // card_manager->new_combat();
        // card_view->getButton()->init_combat();

        switchToPage(page1, PageAnimationDirection::RightToLeft);
    });

    QPushButton *reward_btn = new QPushButton(page1);
    reward_btn->setText("奖励");
    reward_btn->resize(64, 64);
    reward_btn->move(10, 10);
    QAbstractButton::connect(reward_btn, &QPushButton::clicked, [this]() {
        // page3->newReward();
        switchToPage(page3, PageAnimationDirection::LeftToRight);
    });


    player = new Player("uika", PLAYER_MAX_HP, page1, PLAYER_MAX_MP);
    enemy = new Enemy("soyo", ENEMY_MAX_HP, page1);

    page0->show();
    page1->show();
    page2->show();
    page3->show();
    page0->raise();
    now_page = page0;
}

PageManager::~PageManager() {
    delete card_manager;
    delete card_view;
    delete music;
    delete player;
    delete enemy;
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
            card_view->getButton()->init_combat();

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
