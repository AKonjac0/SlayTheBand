#include "RoleManager.h"
#include <QString>

RoleManager::RoleManager(QString enemyName, int enemyHP, int enemyMaxHP, QString playerName, int playerHP, int playerMaxHP, int playerMP)
    : enemyMeta(new EnemyMeta(enemyName, enemyHP, enemyMaxHP)), playerMeta(new PlayerMeta(playerName, playerHP, playerMaxHP, playerMP)) {}

RoleManager::~RoleManager() {
    delete enemyMeta;
    delete playerMeta;
}

void RoleManager::addPlayerBuff(Buff &new_buff) {
    playerMeta->addBuff(new_buff);
    emit repaintPlayerBlock(&new_buff);
}
void RoleManager::clearPlayerBuff() {
    playerMeta->clearBuff();
    emit repaintPlayerBlock(nullptr);
}

void RoleManager::updatePlayerHP(int hp) {
    playerMeta->setHP(hp);
    emit repaintPlayerHP(hp);
}

void RoleManager::updatePlayerMaxHP(int mhp) {
    playerMeta->setMaxHP(mhp);
    emit repaintPlayerMaxHP(mhp);
}

void RoleManager::updatePlayerMP(int mp) {
    playerMeta->setMP(mp);
    emit repaintPlayerMP(mp);
}

void RoleManager::updatePlayerMaxMP(int mmp) {
    playerMeta->setMaxMP(mmp);
    emit repaintPlayerMaxMP(mmp);
}

void RoleManager::updateEnemyHP(int hp) {
    enemyMeta->setHP(hp);
    emit repaintEnemyHP(hp);
}

void RoleManager::updateEnemyMaxHP(int mhp) {
    enemyMeta->setMaxHP(mhp);
    emit repaintEnemyMaxHP(mhp);
}

const Buff &RoleManager::getEnemyIntent() {
    return enemyMeta->getIntent();
}
const Buff &RoleManager::nextEnemyIntent() {
    const Buff &buff = enemyMeta->nextIntent();
    emit repaintEnemyIntent(buff);
    return buff;
}
