#include "MainApp.h"
#include "Defs.h"

MainApp::MainApp(){


    cardManager = new Card_Manager();
    roleManager = new RoleManager("soyo", ENEMY_MAX_HP, ENEMY_MAX_HP, "uika", PLAYER_MAX_HP, PLAYER_MAX_HP, PLAYER_MAX_MP);
    mainwindow = new MainWindow(cardManager);
    mainwindow->show();
    PageManager *pageManager = mainwindow->get_page_manager();
    CardPile *pile = pageManager->getCardView()->getCardPile();
    Card_Button *button = pageManager->getCardView()->getButton();
    CardRewardPage *reward = pageManager->getCardRewardPage();
    EnemyAnimation *enemyAnimation = pageManager->getEnemyAnimation();
    PlayerAnimation *playerAnimation = pageManager->getPlayerAnimation();

    QObject::connect(cardManager, &Card_Manager::onSelectedChanged, pile, [this, pile](){
        pile->set_selected(cardManager->get_selected());
    });

    QObject::connect(cardManager, &Card_Manager::onHandsChanged, pile, [this, pile](){
        pile->set_hands(cardManager->get_handcard());
    });

    QObject::connect(pile, &CardPile::onSelectedChanged, cardManager, [this, pile](){
        cardManager->select_card(pile->get_selected());
    });

    QObject::connect(pile, &CardPile::onPlayed, cardManager, [this, pile](){ // only playACard
        cardManager->playACard(pile->get_played());
    });


//--------------
    QObject::connect(reward, &CardRewardPage::onGenReward, cardManager, [this, reward](){
        reward->setReward(cardManager->gen(3));
        // reward->init();
    });

    QObject::connect(reward, &CardRewardPage::onNewCard, cardManager, [this, reward](){
        cardManager->new_card(reward->getNewCard());
    });

//--------------

    QObject::connect(button, &Card_Button::onDrawCardStart, cardManager, [this, button](){
        cardManager->drawcard();
        // qDebug() << "drawcard finish";
    });

    QObject::connect(button, &Card_Button::onDisCardStart, cardManager, [this, button](){
        cardManager->discard();
    });

    QObject::connect(button, &Card_Button::onNewCombat, cardManager, [this, button](){
        cardManager->new_combat();
    });

    QObject::connect(button, &Card_Button::onGetDiscardPile, cardManager, [this, button](){
        button->set_discard_pile(cardManager->get_discard_pile());
    });

    QObject::connect(button, &Card_Button::onGetDrawcardPile, cardManager, [this, button](){
        button->set_drawcard_pile(cardManager->get_drawcard_pile());
    });

//--------------

    QObject::connect(playerAnimation, &PlayerAnimation::getName, roleManager, [this, playerAnimation]() {
        playerAnimation->setName(roleManager->getPlayerName());
    });

    QObject::connect(enemyAnimation, &EnemyAnimation::getName, roleManager, [this, enemyAnimation]() {
        enemyAnimation->setName(roleManager->getEnemyName());
    });

    QObject::connect(pageManager, &PageManager::startGame, roleManager, [this, playerAnimation, enemyAnimation]() {
        playerAnimation->show(
            PLAYER_POSITION_X,
            SCREEN_HEIGHT - PLAYER_POSITION_Y - playerAnimation->getSize().height(),
            playerAnimation->getSize().width(),
            playerAnimation->getSize().height(),
            roleManager->getPlayerMaxHP(),
            roleManager->getPlayerHP(),
            roleManager->getPlayerMaxMP(),
            roleManager->getPlayerMP()
            );
        enemyAnimation->show(
            SCREEN_WIDTH-PLAYER_POSITION_X-enemyAnimation->getSize().width(),
            SCREEN_HEIGHT-PLAYER_POSITION_Y-enemyAnimation->getSize().height(),
            enemyAnimation->getSize().width(),
            enemyAnimation->getSize().height(),
            roleManager->getEnemyMaxHP(),
            roleManager->getEnemyHP()
            );
    });

    QObject::connect(roleManager, &RoleManager::repaintPlayerHP, playerAnimation, [this, playerAnimation](int hp) {
        playerAnimation->setHealthBarAnimation(hp);
    });

    QObject::connect(roleManager, &RoleManager::repaintPlayerMaxHP, playerAnimation, [this, playerAnimation](int mhp) {
        playerAnimation->setMaxHealthBarAnimation(mhp);
    });

    QObject::connect(roleManager, &RoleManager::repaintPlayerMP, playerAnimation, [this, playerAnimation](int mp) {
        playerAnimation->setManaBarAnimation(mp);
    });

    QObject::connect(roleManager, &RoleManager::repaintPlayerMaxMP, playerAnimation, [this, playerAnimation](int mmp) {
        playerAnimation->setMaxManaBarAnimation(mmp);
    });

    QObject::connect(roleManager, &RoleManager::repaintEnemyHP, enemyAnimation, [this, enemyAnimation](int hp) {
        enemyAnimation->setHealthBarAnimation(hp);
    });

    QObject::connect(roleManager, &RoleManager::repaintEnemyMaxHP, enemyAnimation, [this, enemyAnimation](int mhp) {
        enemyAnimation->setMaxHealthBarAnimation(mhp);
    });

    pageManager->init();
}

MainApp::~MainApp(){
    delete mainwindow;
    delete cardManager;
}
