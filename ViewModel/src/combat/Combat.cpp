#include "Combat.h"
#include <QVector>
Combat::Combat(QObject *parent, CardView *cardView, Player *player)
    : QObject(parent), cardView(cardView), player(player), cardMeta(nullptr), enemy(nullptr) {}

void Combat::setCard(Card_Meta *card) {
    this->cardMeta = card;
}

void Combat::setEnemy(Enemy *enemy) {
    this->enemy = enemy;
}

bool Combat::playACard() {
    if (!check()) {
        return false;
    }
    if (player->getMP() < cardMeta->getEnergyConsumption()) {
        return false;
    }
    player->setMP(player->getMP() - cardMeta->getEnergyConsumption());
    QVector<Buff> buffs = cardMeta->getBuff();
    for (auto &buff : buffs) {
        applyBuff(buff);
    }
    cardView->getManager()->playACard(cardMeta);
    cardView->getCardPile()->playACard(cardMeta);
    return true;
}

bool Combat::check() {
    if (cardMeta == nullptr || enemy == nullptr){
        return false;
    }
    return true;
}

void Combat::applyBuff(Buff &buff) {
    if (buff.getType() == No) return;
    if (buff.getType() == Damage) {
        enemy->setHP(enemy->getHP() - buff.getLevel());
    } else if (buff.getType() == Block) {
        player->addBuff(buff);
    }
}