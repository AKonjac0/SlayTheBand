#include "CardReward.h"

CardReward::CardReward(Card_Manager *manager, QWidget *parent) : manager(manager), parent(parent){
        QVector<Card_Meta*> gen = manager->gen(3);

        card1 = new Card(gen[0], manager, parent, false);
        card2 = new Card(gen[1], manager, parent, false);
        card3 = new Card(gen[2], manager, parent, false);
        card1->getButton()->show();
        card2->getButton()->show();
        card3->getButton()->show();
        card1->getButton()->raise();
        card2->getButton()->raise();
        card3->getButton()->raise();

        QObject::connect(card1->getButton(), &QPushButton::clicked, parent, [this](){
            this->card1->getAnimation()->applyButtonClickAnimation(this->card1->getButton());
            this->manager->new_card(this->card1->getMeta());
            card1->getButton()->hide();
            card2->getButton()->hide();
            card3->getButton()->hide();
        });

        QObject::connect(card2->getButton(), &QPushButton::clicked, parent, [this](){
            this->card2->getAnimation()->applyButtonClickAnimation(this->card2->getButton());
            this->manager->new_card(this->card2->getMeta());
            card1->getButton()->hide();
            card2->getButton()->hide();
            card3->getButton()->hide();
        });

        QObject::connect(card3->getButton(), &QPushButton::clicked, parent, [this](){
            this->card3->getAnimation()->applyButtonClickAnimation(this->card3->getButton());
            this->manager->new_card(this->card3->getMeta());
            card1->getButton()->hide();
            card2->getButton()->hide();
            card3->getButton()->hide();
        });

        // 统一设置按钮大小
        QSize btnSize(248, 328);
        card1->getButton()->setFixedSize(btnSize);
        card2->getButton()->setFixedSize(btnSize);
        card3->getButton()->setFixedSize(btnSize);

        // 初始位置 (500, 500)
        QPoint startPos(500, 500);
        card1->getButton()->move(startPos);
        card2->getButton()->move(startPos);
        card3->getButton()->move(startPos);

        // 创建动画
        QPropertyAnimation *animation1 = new QPropertyAnimation(card1->getButton(), "pos");
        animation1->setDuration(1000);  // 动画时长1秒
        animation1->setStartValue(QPoint(startPos.x(), startPos.y()));  // 向左移动400
        animation1->setEndValue(QPoint(startPos.x() - 400, startPos.y()));  // 向左移动400
        animation1->setEasingCurve(QEasingCurve::OutBack);

        QPropertyAnimation *animation3 = new QPropertyAnimation(card3->getButton(), "pos");
        animation3->setDuration(1000);
        animation3->setStartValue(QPoint(startPos.x(), startPos.y()));  // 向左移动400
        animation3->setEndValue(QPoint(startPos.x() + 400, startPos.y()));  // 向右移动400
        animation3->setEasingCurve(QEasingCurve::OutBack);


        // 使用动画组同时执行
        QParallelAnimationGroup *group = new QParallelAnimationGroup;
        group->addAnimation(animation1);
        group->addAnimation(animation3);

        // QEventLoop loop;
        // QTimer::singleShot(2000, &loop, SLOT(quit()));
        // loop.exec();
        // if(!loop.isRunning()){
        //     group->start(QAbstractAnimation::DeleteWhenStopped);
        // }

        group->start(QAbstractAnimation::DeleteWhenStopped);

        // QObject::connect(&btn4, &QPushButton::clicked, parent, [group](){

        // });
}


CardReward::~CardReward(){
    delete card1;
    delete card2;
    delete card3;
}
