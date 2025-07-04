#include "MainApp.h"

MainApp::MainApp(){


    manager = new Card_Manager();
    mainwindow = new MainWindow(manager);
    mainwindow->show();
    CardPile *pile = mainwindow->get_page_manager()->getCardView()->getCardPile();
    CardRewardPage *reward = mainwindow->get_page_manager()->getCardRewardPage();

    QObject::connect(manager, &Card_Manager::onSelectedChanged, pile, [this, pile](){
        pile->set_selected(manager->get_selected());
    });

    QObject::connect(manager, &Card_Manager::onHandsChanged, pile, [this, pile](){
        pile->set_hands(manager->get_handcard());
    });

    QObject::connect(pile, &CardPile::onSelectedChanged, manager, [this, pile](){
        manager->select_card(pile->get_selected());
    });

    QObject::connect(pile, &CardPile::onPlayed, manager, [this, pile](){ // only playACard
        manager->playACard(pile->get_played());
    });



    QObject::connect(reward, &CardRewardPage::onGenReward, manager, [this, reward](){
        reward->setReward(manager->gen(3));
        reward->init();
    });

    QObject::connect(reward, &CardRewardPage::onNewCard, manager, [this, reward](){
        manager->new_card(reward->getNewCard());
    });
}

MainApp::~MainApp(){
    delete mainwindow;
    delete manager;
}
