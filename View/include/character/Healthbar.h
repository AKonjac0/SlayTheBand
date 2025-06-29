#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QWidget>
#include <QPropertyAnimation>

class HealthBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue)
public:
    explicit HealthBar(QWidget *parent = nullptr);

    void setMaxHealth(int max);
    void setCurrentHealth(int current);
    float value() const { return m_value; }
    void setValue(float value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int m_maxHealth = 100;
    int m_currentHealth = 100;
    float m_value = 1.0f; // 0.0 - 1.0
    QPropertyAnimation *m_animation;

    void updateValue();
};

#endif // HEALTHBAR_H
