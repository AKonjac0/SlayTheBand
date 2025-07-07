#ifndef BLOCKBAR_H
#define BLOCKBAR_H


#include <QWidget>
#include <QPropertyAnimation>

class BlockBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue)
public:
    explicit BlockBar(QWidget *parent = nullptr);

    void setMaxBlock(int max);
    void setCurrentBlock(int current);
    float value() const { return m_value; }
    void setValue(float value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int m_maxBlock = 50;
    int m_currentBlock = 0;
    float m_value = 0.0f; // 0.0 - 1.0
    QPropertyAnimation *m_animation;

    void updateValue();
};


#endif // BLOCKBAR_H
