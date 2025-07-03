#include "MainApp.h"
#include "Card_Manager.h"
#include "CardPile.h"

MainApp::MainApp(){


    manager = new Card_Manager();
    mainwindow = new MainWindow(manager);
    mainwindow->show();
    CardPile *pile = mainwindow->get_page_manager()->getCardView()->getCardPile();

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
}

MainApp::~MainApp(){
    delete mainwindow;
    delete manager;
}
