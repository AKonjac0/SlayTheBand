#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QRandomGenerator>
#include <vector>
#include <string>
#include <QGraphicsOpacityEffect>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题和大小
    setWindowTitle("按钮动画效果演示");
    resize(1920, 1080);

    vector<string> cardNames = {"strike", "defend", "bash", "second_wind", "power_through"};
    // 添加一些按钮用于演示
    int cardNum = QRandomGenerator::global()->bounded(10);
    for(int i = 0; i < 5; ++i){
        int cardType = QRandomGenerator::global()->bounded(5);
        QPushButton *card = new QPushButton("card", this);
        card->setGeometry(50 + 320 * i, 50, 310, 410);

        string cardName = "QPushButton{border-image: url(:image/images/" + cardNames[cardType] + ".png);}";
        card->setStyleSheet(cardName.c_str());
    }

    QPushButton *next_round =new QPushButton("next_round", this);
    next_round->setGeometry(50, 460, 100, 60);
    // 设置所有按钮的动画效果
    setupButtonAnimations();

}

MainWindow::~MainWindow()
{
    // delete ui;
}

void MainWindow::setupButtonAnimations()
{
    // 查找所有按钮
    QList<QPushButton*> buttons = findChildren<QPushButton*>();

    // 为每个按钮连接点击事件
    QPushButton *next_round = nullptr;
    QList<QPushButton*> cards;
    foreach (QPushButton *button, buttons) {
        if(button->text() == "card"){
            cards.push_back(button);
        }else if(button->text() == "next_round"){
            next_round = button;
        }
    }
    foreach (QPushButton *button, cards){
        connect(button, &QPushButton::clicked, this, [this, button]() {
            // 应用动画效果
            applyButtonAnimation(button);

            // 这里可以添加按钮原有的点击逻辑
            qDebug() << "按钮被点击:" << button->text();
        });
    }

    connect(next_round, &QPushButton::clicked, this, [this, cards]() {
        // 应用动画效果
        applyDrawCardAnimation(cards);

        // 这里可以添加按钮原有的点击逻辑
        qDebug() << "牌堆被洗混";
    });

}

void MainWindow::applyDrawCardAnimation(QList<QPushButton*> cards){




    // QVector<QParallelAnimationGroup*> animationGroups;

    // const int buttonWidth = 310;
    // const int buttonHeight = 410;
    // const int spacing = -10;
    // foreach (QPushButton *btn, cards) {
    //     // 按钮设置初始状态
    //     // btn->hide();
    //     btn->setGeometry(50, 1080, 310, 410);

    //     // 设置透明度效果
    //     QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(btn);
    //     opacityEffect->setOpacity(0.0);
    //     btn->setGraphicsEffect(opacityEffect);
    // }
    // int buttonCount = cards.count();
    // // 计算最终位置（从右向左排列）
    // int totalWidth = buttonCount * buttonWidth + (buttonCount - 1) * spacing;
    // int startX = this->width() - totalWidth;  // 右侧起始位置
    // int yPos = 50;
    // 创建动画序列
    // QSequentialAnimationGroup *mainGroup = new QSequentialAnimationGroup;


    const QSize startSize(31, 41);
    const QSize endSize(310, 410);
    const int parentWidth = this->width();
    const int parentHeight = this->height();
    const int spacing = 20; // 卡片间距

    // 计算卡片排列的总宽度
    int totalWidth = cards.size() * endSize.width() + (cards.size() - 1) * spacing;
    int startX = this->width() - totalWidth - 50; // 右侧起始位置
    int yPos = 50;
    // 使用并行动画组管理所有卡片动画
    QParallelAnimationGroup *mainGroup = new QParallelAnimationGroup(this);
    const int animationDuration = 600; // 每个卡片动画总时长
    const int overlapDelay = animationDuration / 2; // 卡片间重叠延迟（前一个动画执行一半时开始下一个）

    for (int i = 0; i < cards.size(); ++i) {
        QPushButton *card = cards[i];
        card->show();

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

        mainGroup->addAnimation(cardGroup);
    }

    // mainGroup->start(QAbstractAnimation::DeleteWhenStopped);

    // 按钮显示控制
    QObject::connect(mainGroup, &QPropertyAnimation::currentTimeChanged,
                     [&cards, animationGroups](QAbstractAnimation *current){
                         if (auto group = qobject_cast<QParallelAnimationGroup*>(current)) {
                             int idx = animationGroups.indexOf(group);
                             if (idx >= 0 && idx < cards.size()) {
                                cards[idx]->show();
                             }
                         }
                     });


}

void MainWindow::applyButtonAnimation(QPushButton *button)
{
    // 停止按钮上所有正在运行的动画
    QList<QAbstractAnimation*> animations = button->findChildren<QAbstractAnimation*>();
    for (QAbstractAnimation *anim : animations) {
        if (anim->state() == QAbstractAnimation::Running) {
            anim->stop();
            anim->deleteLater();
        }
    }


    // QPushButton* button = ui->pushButton;
    QSequentialAnimationGroup* group = new QSequentialAnimationGroup(this);

    // 1. 缩小按钮
    QPropertyAnimation* shrink = new QPropertyAnimation(button, "geometry", this);
    shrink->setDuration(80);
    shrink->setStartValue(button->geometry());
    shrink->setEndValue(button->geometry().adjusted(5, 5, -5, -5));

    // 2. 向上弹跳+放大
    QParallelAnimationGroup* jumpGroup = new QParallelAnimationGroup(this);

    // 位置动画
    QPropertyAnimation* posAnim = new QPropertyAnimation(button, "pos", this);
    posAnim->setDuration(150);
    posAnim->setStartValue(button->pos());
    posAnim->setEndValue(button->pos() + QPoint(0, -20));
    posAnim->setEasingCurve(QEasingCurve::OutBack);

    // 缩放动画
    QPropertyAnimation* grow = new QPropertyAnimation(button, "geometry", this);
    grow->setDuration(150);
    grow->setStartValue(button->geometry().adjusted(5, 5, -5, -5));
    grow->setEndValue(button->geometry().adjusted(-10, -10, 10, 10));

    jumpGroup->addAnimation(posAnim);
    jumpGroup->addAnimation(grow);

    // 3. 返回原位
    QPropertyAnimation* reset = new QPropertyAnimation(button, "geometry", this);
    reset->setDuration(100);
    reset->setEndValue(button->geometry());

    // 组合所有动画
    group->addAnimation(shrink);
    group->addAnimation(jumpGroup);
    group->addAnimation(reset);
    group->start(QAbstractAnimation::DeleteWhenStopped);


}
