// #include "Combat.h"
// #include <QVector>
// Combat::Combat(QObject *parent, CardView *cardView, Player *player)
//     : QObject(parent), cardView(cardView), player(player), cardMeta(nullptr), enemy(nullptr) {}
//
// void Combat::setEnemy(Enemy *enemy) {
//     this->enemy = enemy;
// }
//
// bool Combat::playACard() {
//     if (!check()) {
//         return false;
//     }
//     Card_Meta *cardMeta = cardView->getCardPile()->get_selected();
//     if (player->getMP() < cardMeta->getEnergyConsumption()) {
//         return false;
//     }
//     player->setMP(player->getMP() - cardMeta->getEnergyConsumption());
//     QVector<Buff> buffs = cardMeta->getBuff();
//     for (auto &buff : buffs) {
//         applyBuff(buff);
//     }
//     // cardView->getManager()->playACard(cardMeta);
//     cardView->getCardPile()->playACard(cardMeta);
//     return true;
// }
//
// bool Combat::check() {
//     if (cardView->getCardPile()->get_selected() == nullptr || enemy == nullptr){
//         return false;
//     }
//     return true;
// }
//
// void Combat::applyBuff(Buff &buff) {
//     if (buff.getType() == No) return;
//     if (buff.getType() == Damage) {
//         enemy->setHP(enemy->getHP() - buff.getLevel());
//     } else if (buff.getType() == Block) {
//         player->addBuff(buff);
//     }
// }
//
// void Combat::endOfRound() {
//     int enemyDamage = 2; //TODO: enemy attack logic
//     int lossHP = enemyDamage;
//     for (auto& buff : player->getBuff()) {
//         if (buff.getType() == Block) {
//             int gap = buff.getLevel() - enemyDamage;
//             if (gap < 0) {
//                 lossHP = -gap;
//             } else {
//                 lossHP = 0;
//             }
//             break;
//         }
//     }
//     player->clearBuff();
//     // enemy->clearBuff();
//     player->setHP(player->getHP() - lossHP); // 已经在 setHP 实现中确保设置的 HP 会在 [0,maxHP] 之间，不会小于 0（MP 同理）
//     if (player->getHP() == 0) {
//         // GameOver()
//     } else {
//         // next round
//         player->setMP(player->getMaxMP());
//     }
// }
