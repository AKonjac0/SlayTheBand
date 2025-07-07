#include "Combat.h"
#include <QVector>
Combat::Combat(RoleManager *role)
    : role(role), played(nullptr) {
    card_manager = new Card_Manager();
}

Card_Meta *Combat::get_played() { return played; }

Card_Manager *Combat::get_card_manager(){
    return card_manager;
}

void Combat::setEnemy(){
    // if(enemy == nullptr)
    enemy = role->getEnemyMeta();
    // else enemy = nullptr;
}
bool Combat::playACard() {
    if (!check()) {
        return false;
    }
    played = card_manager->get_selected();
    if (role->getPlayerMP() < played->getEnergyConsumption()) {
        return false;
    }
    role->updatePlayerMP((role->getPlayerMP() - played->getEnergyConsumption()));
    QVector<Buff> buffs = played->getBuff();
    for (auto &buff : buffs) {
        applyBuff(buff);
    }
    // cardView->getManager()->playACard(cardMeta);

    card_manager->playACard(played);
    emit onPlayed();


    return true;
}

bool Combat::check() {
    if (card_manager->get_selected() == nullptr || enemy == nullptr){
        return false;
    }
    return true;
}

void Combat::applyBuff(Buff &buff) {
    if (buff.getType() == No) return;
    if (buff.getType() == Damage) {
        // enemy->setHP(enemy->getHP() - buff.getLevel());
        role->updateEnemyHP(role->getEnemyHP() - buff.getLevel());
        if(role->getEnemyHP() == 0){
            emit onEnemyDefeated();
        }
    } else if (buff.getType() == Block) {
        role->addPlayerBuff(buff);
    }
}

void Combat::new_combat(){
    role->nextEnemyIntent();
}

void Combat::endOfRound() {
    // qDebug() << "ok";
    Buff enemyBuff = role->getEnemyIntent();
    role->nextEnemyIntent();
    // qDebug() << "ok";
    int enemyDamage = 0, enemyBlock = 0;
    if(enemyBuff.getType() == Damage) enemyDamage = enemyBuff.getLevel();
    else enemyBlock = enemyBuff.getLevel();
    int lossHP = enemyDamage;
    for (auto& buff : role->getPlayerBuff()) {
        if (buff.getType() == Block) {
            int gap = buff.getLevel() - enemyDamage;
            if (gap < 0) {
                lossHP = -gap;
            } else {
                lossHP = 0;
            }
            break;
        }
    }
    role->clearPlayerBuff();
    // enemy->clearBuff();
    role->updatePlayerHP(role->getPlayerHP() - lossHP);
    if (role->getPlayerHP() == 0) {
        // GameOver()
        emit onPlayerDead();
    } else {
        // next round
        role->updatePlayerMP(role->getPlayerMaxMP());
    }
}
