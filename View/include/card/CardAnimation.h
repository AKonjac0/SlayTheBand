#ifndef CARDANIMATION_H
#define CARDANIMATION_H
// #include "Card_Manager.h"
#include "HoverButton.h"
// class CardAnimation : public Animation{


class CardAnimation {
public:
    CardAnimation(QWidget *parent);
    ~CardAnimation() = default;
    void applyButtonAnimation(HoverButton *button);
private:
    QWidget *parent;

};
#endif // CARDANIMATION_H
