#include "Card_Button.h"
#include <QDebug>
// View

Card_Button::Card_Button(QWidget *parent, CardPile *pile) : parent(parent), next_round_click(true), pile(pile){
    next_round = new HoverButton("下一回合", parent, false);
    next_round->setGeometry(parent->width() - 400, parent->height() - 300, 200, 200);
    next_round->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    QString next_round_button_pic = "QPushButton{color: white; border-image: url(:image/images/endTurnButton.png);}";
    next_round->setStyleSheet(next_round_button_pic);

    discard_pile_button = new HoverButton("", parent, false);
    discard_pile_button->setGeometry(parent->width() - 130, parent->height() - 130, 100, 100);
    discard_pile_button->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    discard_pile_button->setStyleSheet("QPushButton{color: white; border-image: url(:image/images/discard_pile.png);}");

    drawcard_pile_button = new HoverButton("", parent, false);
    drawcard_pile_button->setGeometry(30, parent->height() - 130, 100, 100);
    drawcard_pile_button->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    drawcard_pile_button->setStyleSheet("QPushButton{color: white; border-image: url(:image/images/drawcard_pile.png);}");


    discard_num = new CountButton(QPointF(parent->width() - 110, parent->height() - 100), parent);
    discard_num->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    discard_num->setStyleSheet("QPushButton{color: white; border-image: url(:image/images/countCircle.png);}");
    drawcard_num = new CountButton(QPointF(70, parent->height() - 100), parent);
    drawcard_num->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    drawcard_num->setStyleSheet("QPushButton{color: white; border-image: url(:image/images/countCircle.png);}");

    animation = new CardPileAnimation(parent);
    next_round_button_animation = new CardAnimation(parent);
    discard_pile_animation = new CardAnimation(parent);
    drawcard_pile_animation = new CardAnimation(parent);

    // init_combat();

    QObject::connect(discard_pile_button, &QPushButton::clicked, parent, [this]() {
        discard_pile_animation->applyButtonClickAnimation(discard_pile_button);
    });

    QObject::connect(drawcard_pile_button, &QPushButton::clicked, parent, [this]() {
        drawcard_pile_animation->applyButtonClickAnimation(drawcard_pile_button);
    });
    QObject::connect(next_round, &QPushButton::clicked, parent, [this]() {
        // 应用动画效果
        if(next_round_click){
            next_round_button_animation->applyButtonClickAnimation(next_round);
            this->pile->unselect(); // very important!
            next_round_click = false;
            QAbstractAnimation *disanim = this->discards();

            QObject::connect(disanim, &QAbstractAnimation::finished, this->parent, [this](){
                QAbstractAnimation *drawanim = this->drawcards();
                QObject::connect(drawanim, &QAbstractAnimation::finished, this->parent, [this](){
                    qDebug() << "下一回合";
                    next_round_click = true;
                    this->pile->setAnimating(false);
                    this->pile->setHover(true);
                    emit finish_round();
                });
            });
        }
    });
}

Card_Button::~Card_Button(){
    delete next_round;
    delete discard_pile_button;
    delete drawcard_pile_button;
    delete discard_num;
    delete drawcard_num;
    delete animation;
    delete next_round_button_animation;
    delete discard_pile_animation;
    delete drawcard_pile_animation;
}

QAbstractAnimation *Card_Button::drawcards(){
    // this->manager->drawcard();
    emit onDrawCardStart();


    this->pile->create_cards();
    this->pile->setHover(false); // need this because cards are newly constructed
    this->pile->setAnimating(true);
    QAbstractAnimation *anim = this->animation->applyDrawCardAnimation(this->pile->get_cards());

    emit onGetDrawcardPile();
    emit onGetDiscardPile();

    drawcard_num->setNumber(drawcard_pile.count());
    discard_num->setNumber(discard_pile.count());
    return anim;
}


QAbstractAnimation * Card_Button::discards(){
    this->pile->setHover(false);
    this->pile->setAnimating(true);
    QAbstractAnimation *anim = this->animation->applyDisCardAnimation(this->pile->get_cards());

    QObject::connect(anim, &QAbstractAnimation::finished, parent, [this, anim](){
        // this->manager->discard();
        emit onDisCardStart();
        this->pile->clear_cards();
    });
    // discard_num->setNumber(manager->get_discard_pile().count());
    return anim;
}

void Card_Button::init_combat(){
    this->pile->unselect();
    next_round_click = false;
    pile->clear_cards();
    // manager->new_combat();
    emit onNewCombat();
    QAbstractAnimation *anim = drawcards();
    QObject::connect(anim, &QAbstractAnimation::finished, parent, [this](){
        qDebug() << "战斗开始";
        next_round_click = true;
        pile->setHover(true);
        pile->setAnimating(false);
    });
}

bool Card_Button::get_clickable(){
    return next_round_click;
}
