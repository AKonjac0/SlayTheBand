#include <CardRewardPage.h>
#include <QPushButton>

CardRewardPage::CardRewardPage(QWidget *parent) : QWidget(parent), parent(parent), reward(nullptr)
{
    this->setGeometry(0, 0, parent->width(), parent->height());
    this->setAutoFillBackground(true);
    confirmBtn = new QPushButton(this);
    confirmBtn->setText("确定");
    confirmBtn->resize(64, 64);
    confirmBtn->move(10, 10);
}

void CardRewardPage::newReward(){
    if(reward) delete reward, reward = nullptr;

    fireGenReward();
    init();
}


void CardRewardPage::init(){
    reward = new CardReward(gen, this);

    QObject::connect(reward->card1->getButton(), &QPushButton::clicked, parent, [this](){
        reward->card1->getAnimation()->applyButtonClickAnimation(reward->card1->getButton());
        // this->manager->new_card(this->card1->getMeta());
        setNewCard(reward->card1->getMeta());
        reward->card1->getButton()->hide();
        reward->card2->getButton()->hide();
        reward->card3->getButton()->hide();
    });

    QObject::connect(reward->card2->getButton(), &QPushButton::clicked, parent, [this](){
        reward->card2->getAnimation()->applyButtonClickAnimation(reward->card2->getButton());
        // this->manager->new_card(this->card2->getMeta());
        setNewCard(reward->card2->getMeta());
        reward->card1->getButton()->hide();
        reward->card2->getButton()->hide();
        reward->card3->getButton()->hide();
    });

    QObject::connect(reward->card3->getButton(), &QPushButton::clicked, parent, [this](){
        reward->card3->getAnimation()->applyButtonClickAnimation(reward->card3->getButton());
        // this->manager->new_card(this->card3->getMeta());
        setNewCard(reward->card3->getMeta());
        reward->card1->getButton()->hide();
        reward->card2->getButton()->hide();
        reward->card3->getButton()->hide();
    });
}
