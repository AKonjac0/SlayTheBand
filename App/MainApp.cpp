#include "MainApp.h"

MainApp::MainApp(){


    manager = new Card_Manager();
    mainwindow = new MainWindow(manager);
    mainwindow->show();
    CardPile *pile = mainwindow->get_page_manager()->getCardView()->getCardPile();
    Card_Button *button = mainwindow->get_page_manager()->getCardView()->getButton();
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


//--------------
    QObject::connect(reward, &CardRewardPage::onGenReward, manager, [this, reward](){
        reward->setReward(manager->gen(3));
        // reward->init();
    });

    QObject::connect(reward, &CardRewardPage::onNewCard, manager, [this, reward](){
        manager->new_card(reward->getNewCard());
    });

//--------------

    QObject::connect(button, &Card_Button::onDrawCardStart, manager, [this, button](){
        manager->drawcard();
        // qDebug() << "drawcard finish";
    });

    QObject::connect(button, &Card_Button::onDisCardStart, manager, [this, button](){
        manager->discard();
    });

    QObject::connect(button, &Card_Button::onNewCombat, manager, [this, button](){
        manager->new_combat();
    });

    QObject::connect(button, &Card_Button::onGetDiscardPile, manager, [this, button](){
        button->set_discard_pile(manager->get_discard_pile());
    });

    QObject::connect(button, &Card_Button::onGetDrawcardPile, manager, [this, button](){
        button->set_drawcard_pile(manager->get_drawcard_pile());
    });
}

MainApp::~MainApp(){
    delete mainwindow;
    delete manager;
}
