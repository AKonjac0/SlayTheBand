#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H
#include "EnemyMeta.h"
#include "PlayerMeta.h"

class RoleManager : public QObject {
    Q_OBJECT
public:
    RoleManager(QString enemyName, int enemyHP, int enemyMaxHP, QString playerName, int playerHP, int playerMaxHP, int playerMP);
    ~RoleManager();
    int getPlayerHP() {return playerMeta->getHP();}
    int getPlayerMaxHP() {return playerMeta->getmaxHP();}
    int getPlayerMP() {return playerMeta->getMP();}
    int getPlayerMaxMP() {return playerMeta->getmaxMP();}
    QString getPlayerName() {return playerMeta->getname();}
    QVector<Buff> getPlayerBuff() {return playerMeta->getBuff();}
    void addPlayerBuff(Buff &new_buff) {playerMeta->addBuff(new_buff);}
    void clearPlayerBuff() {playerMeta->clearBuff();}
    void updatePlayerHP(int hp);
    void updatePlayerMaxHP(int mhp);
    void updatePlayerMP(int mp);
    void updatePlayerMaxMP(int mmp);

    int getEnemyHP() {return enemyMeta->getHP();}
    int getEnemyMaxHP() {return enemyMeta->getmaxHP();}
    QString getEnemyName() {return enemyMeta->getname();}
    QVector<Buff> getEnemyBuff() {return enemyMeta->getBuff();}
    void addEnemyBuff(Buff &new_buff) {enemyMeta->addBuff(new_buff);}
    void clearEnemyBuff() {enemyMeta->clearBuff();}
    void updateEnemyHP(int hp);
    void updateEnemyMaxHP(int hp);
    EnemyMeta *getEnemyMeta() { return enemyMeta; }
    PlayerMeta *getPlayerMeta() { return playerMeta; }
signals:
    void repaintPlayerHP(int hp);
    void repaintPlayerMP(int mp);
    void repaintPlayerMaxHP(int mhp);
    void repaintPlayerMaxMP(int mmp);

    void repaintEnemyHP(int hp);
    void repaintEnemyMaxHP(int mhp);
private:
    EnemyMeta *enemyMeta;
    PlayerMeta *playerMeta;
};
#endif //ROLEMANAGER_H
