#ifndef CHARACTERANIMATION_H
#define CHARACTERANIMATION_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QSize>
#include <QPushButton>
#include <QString>
#include <QObject>

#include "Healthbar.h"


class CharacterAnimation : public QObject{
    Q_OBJECT
public:
    CharacterAnimation(QWidget*);
    virtual ~CharacterAnimation() = 0;

    void init();
    void setName(QString name) { this->name = name; }
    QLabel* getAvatar() const { return character_avatar; }
    QPushButton* getButton() const { return button; }
    HealthBar* getHealthBar() const { return healthBar; }
    QMovie* getIllustration() const { return illustration; }
    QSize getSize() const { return size; }
protected:
    // View
    QString name;
    QWidget* parent;
    QLabel* character_avatar;
    QMovie* illustration;
    HealthBar* healthBar;
    // Literally size of avatar
    QSize size;
    QPushButton *button;
};

#endif // CHARACTERANIMATION_H
