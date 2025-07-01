#ifndef CARDANIMATION_H
#define CARDANIMATION_H
// #include "Card_Manager.h"
#include "HoverButton.h"
// class CardAnimation : public Animation{


class CardAnimation {
public:
    CardAnimation(QWidget *parent);
    ~CardAnimation() = default;
    void applyButtonClickAnimation(HoverButton *button);
    void applyHighLightAnimation(HoverButton *button);
    void applyDeHighLightAnimation(HoverButton *button);
private:
    QWidget *parent;

};
#endif // CARDANIMATION_H
