#ifndef CARDANIMATION_H
#define CARDANIMATION_H
// #include "Card_Manager.h"
#include <QPushButton>
// class CardAnimation : public Animation{


class CardAnimation {
public:
    CardAnimation(QWidget *parent);
    ~CardAnimation() = default;
    void applyButtonAnimation(QPushButton *button);
private:
    QWidget *parent;

};
#endif // CARDANIMATION_H
