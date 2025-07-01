#include "Manabar.h"
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>
#include <QTimer>

ManaBar::ManaBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(18);
    m_animation = new QPropertyAnimation(this, "value", this);
    m_animation->setDuration(300); // 动画时长300ms
    m_animation->setEasingCurve(QEasingCurve::OutCubic);

    m_manaParticle = QPixmap(16, 16);
    m_manaParticle.fill(Qt::transparent);
    QPainter p(&m_manaParticle);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(QColor(100, 200, 255, 200));
    p.setPen(Qt::NoPen);
    p.drawEllipse(0, 0, 16, 16);
}

void ManaBar::setMaxMana(int max)
{
    m_maxMana = max;
    update();
}

void ManaBar::setCurrentMana(int current)
{
    m_currentMana = qBound(0, current, m_maxMana);
    m_animation->stop();
    m_animation->setStartValue(m_value);
    m_animation->setEndValue(static_cast<float>(m_currentMana) / m_maxMana);
    m_animation->start();
}

void ManaBar::setValue(float value)
{
    m_value = value;
    update();
}

void ManaBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    QRectF bgRect(0, 0, width(), height());
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(30, 30, 50)); // 深蓝色背景
    painter.drawRoundedRect(bgRect, 4, 4);

    // 绘制法力条前景
    QRectF manaRect(1, 1, (width() - 2) * m_value, height() - 2);

    // 创建蓝色渐变效果
    QLinearGradient gradient(manaRect.topLeft(), manaRect.topRight());
    QColor startColor(100, 180, 255); // 浅蓝色
    QColor endColor(30, 100, 220);    // 深蓝色

    gradient.setColorAt(0, startColor);
    gradient.setColorAt(1, endColor);

    painter.setBrush(gradient);
    painter.drawRoundedRect(manaRect, 3, 3);

    // 添加发光效果
    if (m_value > 0) {
        QLinearGradient glowGradient(manaRect.topLeft(), manaRect.topRight());
        glowGradient.setColorAt(0, QColor(150, 220, 255, 100));
        glowGradient.setColorAt(1, QColor(80, 160, 255, 50));

        painter.setBrush(glowGradient);
        painter.drawRoundedRect(manaRect, 3, 3);
    }

    // 绘制边框
    painter.setPen(QPen(QColor(100, 150, 220), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(bgRect, 4, 4);

    // 绘制法力值文字
    QString text = QString("%1/%2").arg(m_currentMana).arg(m_maxMana);
    painter.setPen(QColor(220, 240, 255)); // 浅蓝色文字
    painter.setFont(QFont("Arial", 8, QFont::Bold));
    painter.drawText(bgRect, Qt::AlignCenter, text);

    // 绘制法力符号
    QRectF symbolRect(width() - 25, 1, 16, 16);
    painter.drawPixmap(symbolRect, m_manaParticle, m_manaParticle.rect());
}

void ManaBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

void ManaBar::playRegenAnimation()
{
    // 创建粒子效果动画组
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);

    // 闪烁效果
    QPropertyAnimation *blinkAnim = new QPropertyAnimation(this, "value", group);
    blinkAnim->setDuration(200);
    blinkAnim->setStartValue(m_value);
    blinkAnim->setEndValue(m_value * 1.05); // 轻微放大效果
    blinkAnim->setEasingCurve(QEasingCurve::OutQuad);

    // 恢复原状
    QPropertyAnimation *restoreAnim = new QPropertyAnimation(this, "value", group);
    restoreAnim->setDuration(200);
    restoreAnim->setStartValue(m_value * 1.05);
    restoreAnim->setEndValue(m_value);

    group->addAnimation(blinkAnim);
    group->addAnimation(restoreAnim);

    // 播放完成后自动删除
    connect(group, &QSequentialAnimationGroup::finished, group, &QSequentialAnimationGroup::deleteLater);
    group->start();
}
