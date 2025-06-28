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
    Player* player = new Player("slime_balloon", PLAYER_MAX_HP, this, PLAYER_MAX_MP);
    player->show_character(100,700,100,200);
    // 添加一些按钮用于演示
    QPushButton *next_round =new QPushButton("next_round", this);
    next_round->setGeometry(50, 460, 100, 60);
    // 设置所有按钮的动画效果
    setupButtonAnimations();

}

MainWindow::~MainWindow()
{
    delete card_manager;
}

void MainWindow::setupButtonAnimations()
{
    // 为每个按钮连接点击事件
    QList<QPushButton *> button_list = findChildren<QPushButton*>();
    QPushButton *next_round;
    foreach (QPushButton *button, button_list){
        if(button->text() == "next_round") next_round = button;
    }

    applyDrawCardAnimation();

    connect(next_round, &QPushButton::clicked, this, [this]() {
        // 应用动画效果
        applyDisCardAnimation();
        applyDrawCardAnimation();

        // 这里可以添加按钮原有的点击逻辑
        qDebug() << "下一回合";
    });

}

void MainWindow::applyDisCardAnimation(){
    // animation first
    card_manager->discard();
}

void MainWindow::applyDrawCardAnimation(){
    static bool isAnimating = false;
    if(isAnimating == false) isAnimating = true;
    else return;

    card_manager->drawcard();

    const QSize startSize(31, 41);
    const QSize endSize(310, 410);
    const int parentWidth = 1920 - 200;
    const int parentHeight = 1080;
    const int spacing = -70; // 卡片间距
    QVector<Card *> cards = card_manager->get_handcard();

    // 计算卡片排列的总宽度
    int totalWidth = cards.size() * endSize.width() + (cards.size() - 1) * spacing;
    int startX = parentWidth - totalWidth - 50; // 右侧起始位置
    int yPos = 50;
    // 使用并行动画组管理所有卡片动画
    const int animationDuration = 600; // 每个卡片动画总时长

    for(Card *i : cards){
        QPushButton *card = i->getButton();

        // 设置初始状态：左下角外、小尺寸、完全透明
        card->setGeometry(0, parentHeight, startSize.width(), startSize.height());

        // 设置透明度效果
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(card);
        opacityEffect->setOpacity(1.0);
        card->setGraphicsEffect(opacityEffect);
    }
    QParallelAnimationGroup *final_group;
    int card_size = cards.size();
    for (int i = 0; i < card_size; ++i) {
        QPushButton *card = cards[i]->getButton();

        // 设置初始状态：左下角外、小尺寸、完全透明
        card->setGeometry(0, parentHeight, startSize.width(), startSize.height());

        // 设置透明度效果
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(card);
        opacityEffect->setOpacity(0.0);
        card->setGraphicsEffect(opacityEffect);

        // 目标位置（从右向左排列）
        int targetX = startX + i * (endSize.width() + spacing);
        QPoint endPos(targetX, yPos);

        // 位置动画（左下角 -> 目标位置）
        QPropertyAnimation *posAnim = new QPropertyAnimation(card, "pos", this);
        posAnim->setDuration(animationDuration);
        posAnim->setStartValue(QPoint(0, parentHeight));
        posAnim->setEndValue(endPos);
        posAnim->setEasingCurve(QEasingCurve::OutBack);

        // 大小动画（31x41 -> 310x410）
        QPropertyAnimation *sizeAnim = new QPropertyAnimation(card, "geometry", this);
        sizeAnim->setDuration(animationDuration);
        sizeAnim->setStartValue(QRect(0, parentHeight, startSize.width(), startSize.height()));
        sizeAnim->setEndValue(QRect(endPos, endSize));
        sizeAnim->setEasingCurve(QEasingCurve::OutBack);

        // 透明度动画（0 -> 1）
        QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacityEffect, "opacity", this);
        opacityAnim->setDuration(animationDuration);
        opacityAnim->setStartValue(0.0);
        opacityAnim->setEndValue(1.0);

        opacityAnim->setEasingCurve(QEasingCurve::InQuad);

        // 组合动画（位置+大小+透明度同步）
        QParallelAnimationGroup *cardGroup = new QParallelAnimationGroup(this);
        cardGroup->addAnimation(posAnim);
        cardGroup->addAnimation(sizeAnim);
        cardGroup->addAnimation(opacityAnim);

        // 设置卡片动画的延迟启动（每个卡片比前一个卡片延迟overlapDelay毫秒）
        QEventLoop loop;
        QTimer::singleShot(100, &loop, SLOT(quit()));
        loop.exec();
        if(!loop.isRunning()){
            cardGroup->start(QAbstractAnimation::DeleteWhenStopped);
        }
        if(i == cards.size() - 1) final_group = cardGroup;
    }
    connect(final_group, &QParallelAnimationGroup::finished, []() {
        isAnimating = false;
    });
}
