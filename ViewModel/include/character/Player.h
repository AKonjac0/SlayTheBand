#ifndef PLAYER_H
#define PLAYER_H
#include <QWidget>
#include "PlayerMeta.h"
#include "PlayerAnimation.h"
// #include "Card_Manager.h"
// #include "CardView.h"

class Player
{
public:
    Player(QString _name, int _HP, QWidget* _parent, int _MP);
    ~Player();

    // Uppermost interface for manipulating player's statistics
    // 两种改变当前 MP HP 的方法，结果值均在 [0, maxMP/maxHP] 间
    // Player 的 MP 增加 amount
    void MP_change(int amount);

    // Player 的 HP 增加 amount
    void HP_change(int amount);

    // 将 Player 的 MP 设置为 mp
    void setMP(int mp);
    // 将 Player 的 HP 设置为 hp
    void setHP(int hp);

    // 两种改变 Player 最大 MP, HP 的方法，当前逻辑中最大 HP/MP 增加并不会影响当前的 HP/MP
    // Player 的最大 MP 增加 amount
    void maxMP_change(int amount);
    // Player 的最大 HP 增加 amount
    void maxHP_change(int amount);
    // 将 Player 的最大 MP 设置为 mmp
    void setMaxMP(int mmp);
    // 将 Player 的最大 HP 设置为 mhp
    void setMaxHP(int mhp);

    // 获取一些 meta 信息
    int getHP() const { return playerMeta->getHP(); }
    int getMaxHP() const { return playerMeta->getmaxHP(); }
    int getMP() const { return playerMeta->getMP(); }
    int getMaxMP() const { return playerMeta->getmaxMP(); }
    QString getName() const { return playerMeta->getname(); }
    QVector<Buff> getBuff() const { return playerMeta->getBuff(); }
    QSize getSize() const { return playerAnimation->getSize(); }
    void addBuff(Buff &buff) { playerMeta->addBuff(buff); }

    // 通过 PlayerAnimation 控制 Player 的动画
    void show(int x, int y, int width, int height);
private:
    PlayerMeta* playerMeta;
    PlayerAnimation* playerAnimation;

    // TBD: encapsule card logic into player
    // Card_Manager* cardManager;
    // CardView* cardView;

};

#endif // PLAYER_H
