#ifndef MANABAR_H
#define MANABAR_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QPixmap>

class ManaBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue)
public:
    explicit ManaBar(QWidget *parent = nullptr);

    void setMaxMana(int max);
    void setCurrentMana(int current);
    float value() const { return m_value; }
    void setValue(float value);

    void playRegenAnimation(); // 播放法力恢复动画

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int m_maxMana = 10;
    int m_currentMana = 10;
    float m_value = 1.0f; // 0.0 - 1.0
    QPropertyAnimation *m_animation;

    QPixmap m_manaParticle; // 法力粒子效果

    void updateValue();
    void drawRegenEffect(QPainter &painter, float progress);
};

#endif // MANABAR_H
