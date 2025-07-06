#include "MainApp.h"
#include "Defs.h"

MainApp::MainApp(){


    // manager = new Card_Manager();


    combat = new Combat(nullptr);
    Card_Manager *manager = combat->get_card_manager();

    mainwindow = new MainWindow();
    combat->setPlayer(mainwindow->get_page_manager()->getPlayer());

    roleManager = new RoleManager("soyo", ENEMY_MAX_HP, ENEMY_MAX_HP, "uika", PLAYER_MAX_HP, PLAYER_MAX_HP, PLAYER_MAX_MP);
    mainwindow->show();
    PageManager *pageManager = mainwindow->get_page_manager();
    CardPile *pile = mainwindow->get_page_manager()->getCardView()->getCardPile();
    Card_Button *button = mainwindow->get_page_manager()->getCardView()->getButton();
    CardRewardPage *reward = mainwindow->get_page_manager()->getCardRewardPage();
    CombatView *combat_view = mainwindow->get_page_manager()->getCombatView();
    EnemyAnimation *enemyAnimation = pageManager->getEnemyAnimation();
    PlayerAnimation *playerAnimation = pageManager->getPlayerAnimation();
    QObject::connect(manager, &Card_Manager::onSelectedChanged, pile, [this, pile, manager](){
        pile->set_selected(manager->get_selected());
    });

    QObject::connect(manager, &Card_Manager::onHandsChanged, pile, [this, pile, manager](){
        pile->set_hands(manager->get_handcard());
    });

    QObject::connect(pile, &CardPile::onSelectedChanged, manager, [this, pile, manager](){
        manager->select_card(pile->get_selected());
    });

    // QObject::connect(pile, &CardPile::onPlayed, manager, [this, pile](){ // only playACard
    //     manager->playACard(pile->get_played());
    // });

//-------------- Combat ~ CardPile

    QObject::connect(combat, &Combat::onPlayed, pile, [this, pile](){ // only playACard
        pile->playACard(combat->get_played());
    });

//-------------- Combat ~ CombatView

    QObject::connect(combat_view, &CombatView::onEndOfRound, combat, [this](){
        combat->endOfRound();
    });

    QObject::connect(combat_view, &CombatView::onPlayACard, combat, [this](){
        combat->playACard();
    });

    QObject::connect(combat_view, &CombatView::onSetEnemy, combat, [this, combat_view](){
        combat->setEnemy(combat_view->getEnemy());
    });

//-------------- CardRewardPage ~ Card_Manager
    QObject::connect(reward, &CardRewardPage::onGenReward, manager, [this, reward, manager](){
        reward->setReward(manager->gen(3));
        // reward->init();
    });

    QObject::connect(reward, &CardRewardPage::onNewCard, manager, [this, reward, manager](){
        manager->new_card(reward->getNewCard());
    });

//--------------Card_Button ~ Card_Manager

    QObject::connect(button, &Card_Button::onDrawCardStart, manager, [this, button, manager](){
        manager->drawcard();
        // qDebug() << "drawcard finish";
    });

    QObject::connect(button, &Card_Button::onDisCardStart, manager, [this, button, manager](){
        manager->discard();
    });

    QObject::connect(button, &Card_Button::onNewCombat, manager, [this, button, manager](){
        manager->new_combat();
    });

    QObject::connect(button, &Card_Button::onGetDiscardPile, manager, [this, button, manager](){
        button->set_discard_pile(manager->get_discard_pile());
    });

    QObject::connect(button, &Card_Button::onGetDrawcardPile, manager, [this, button, manager](){
        button->set_drawcard_pile(manager->get_drawcard_pile());
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
    delete combat;
}
