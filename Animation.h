#ifndef ANIMATION_H
#define ANIMATION_H
#include "Card_Manager.h"
class Animation{

public:
    Animation(Card_Manager *manager, QWidget *parent);
    ~Animation() = default;
public:
    QWidget *parent;
    Card_Manager *manager;
};
#endif // ANIMATION_H
