#ifndef CARDANIMATION_H
#define CARDANIMATION_H
// #include "Card_Manager.h"
#include "HoverButton.h"
// class CardAnimation : public Animation{


class CardAnimation {
public:
    CardAnimation(QWidget *parent);
    ~CardAnimation() = default;
    QAbstractAnimation *applyButtonClickAnimation(HoverButton *button);
    QAbstractAnimation *applyHighLightAnimation(HoverButton *button);
    QAbstractAnimation *applyDeHighLightAnimation(HoverButton *button);
private:
    QWidget *parent;

};
#endif // CARDANIMATION_H
