#include "Card_Button.h"

// View

Card_Button::Card_Button(Card_Manager *manager, QWidget *parent, CardPile *pile) : manager(manager), parent(parent), next_round_click(true), pile(pile){
    next_round = new QPushButton("下一回合", parent);
    next_round->setGeometry(1600, 650, 200, 200);
    next_round->setFont(QFont("Microsoft YaHei UI", 16, QFont::Bold));
    QString next_round_button_pic = "QPushButton{color: white; border-image: url(:image/images/endTurnButton.png);}";
    next_round->setStyleSheet(next_round_button_pic);
    animation = new CardPileAnimation(parent);
    next_round_button_animation = new CardAnimation(parent);

    drawcards();

    QObject::connect(next_round, &QPushButton::clicked, parent, [this]() {
        // 应用动画效果
        next_round_button_animation->applyButtonAnimation(next_round);
        if(next_round_click){
            next_round_click = false;
            this->discards();
            this->drawcards();
            // 这里可以添加按钮原有的点击逻辑
            qDebug() << "下一回合";
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, SLOT(quit()));
            loop.exec();
            if(!loop.isRunning()){
                next_round_click = true;
            }
        }

    });
}

Card_Button::~Card_Button(){
    delete next_round;
    delete animation;
}

void Card_Button::drawcards(){

    this->manager->drawcard();
    this->pile->create_cards();
    this->animation->applyDrawCardAnimation(this->pile->get_cards());
}

void Card_Button::discards(){
    this->animation->applyDisCardAnimation(this->pile->get_cards());
    this->manager->discard();
    this->pile->clear_cards();
}
