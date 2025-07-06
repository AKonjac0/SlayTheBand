// #include "Player.h"
// #include "PlayerAnimation.h"
//
// Player::Player(QString _name, int _HP, QWidget* _parent, int _MP){
//     playerMeta = new PlayerMeta(_name, _HP, _HP, _MP);
//     playerAnimation = new PlayerAnimation(playerMeta, _parent);
// };
//
// Player::~Player(){
//     if (playerMeta != nullptr)
//         delete playerMeta;
//     if (playerAnimation != nullptr)
//         delete playerAnimation;
// }
//
// void Player::MP_change(int amount){
//     playerMeta->MP_change(amount);
//     int tempMP = playerMeta->getMP();
//     playerAnimation->setManaBarAnimation(tempMP);
// }
//
// void Player::HP_change(int amount){
//     playerMeta->HP_change(amount);
//     int tempHP = playerMeta->getHP();
//     playerAnimation->setHealthBarAnimation(tempHP);
// }
//
// void Player::setMP(int mp){
//     playerMeta->setMP(mp);
//     playerAnimation->setManaBarAnimation(playerMeta->getMP());
// }
//
// void Player::setHP(int hp){
//     playerMeta->setHP(hp);
//     playerAnimation->setHealthBarAnimation(playerMeta->getHP());
// }
//
// void Player::maxMP_change(int amount){
//     playerMeta->maxMP_change(amount);
//     int tempMP = playerMeta->getmaxMP();
//     playerAnimation->setMaxManaBarAnimation(tempMP);
// }
//
// void Player::maxHP_change(int amount){
//     playerMeta->maxHP_change(amount);
//     int tempHP = playerMeta->getmaxHP();
//     playerAnimation->setMaxHealthBarAnimation(tempHP);
// }
//
// void Player::setMaxMP(int mmp){
//     playerMeta->setMaxMP(mmp);
//     playerAnimation->setMaxManaBarAnimation(playerMeta->getmaxMP());
// }
//
// void Player::setMaxHP(int mhp){
//     playerMeta->setMaxHP(mhp);
//     playerAnimation->setMaxHealthBarAnimation(playerMeta->getmaxHP());
// }
//
// void Player::show(int x, int y, int width, int height)
// {
//     playerAnimation->show(x, y, width, height, playerMeta->getmaxHP(), playerMeta->getHP(), playerMeta->getmaxMP(), playerMeta->getMP());
// }
//
