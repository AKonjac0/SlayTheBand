#include "Player.h"

Player::Player(QString _name, int _HP, MainWindow* _parent, int _MP):Character(_name,_HP, _parent), maxMP(_MP){
    MP = maxMP;
};

void Player::MP_change(int amount){
    this->MP += amount;
}
