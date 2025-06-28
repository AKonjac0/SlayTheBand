#include "healthbar.h"
#include <QPainter>
#include <QLinearGradient>

HealthBar::HealthBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(20);
    m_animation = new QPropertyAnimation(this, "value", this);
    m_animation->setDuration(500); // 动画时长500ms
    m_animation->setEasingCurve(QEasingCurve::OutQuad);
}

void HealthBar::setMaxHealth(int max)
{
    m_maxHealth = max;
    update();
}

void HealthBar::setCurrentHealth(int current)
{
    m_currentHealth = qBound(0, current, m_maxHealth);
    m_animation->stop();
    m_animation->setStartValue(m_value);
    m_animation->setEndValue(static_cast<float>(m_currentHealth) / m_maxHealth);
    m_animation->start();
}

void HealthBar::setValue(float value)
{
    m_value = value;
    update();
}

void HealthBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    QRectF bgRect(0, 0, width(), height());
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(50, 50, 50));
    painter.drawRoundedRect(bgRect, 5, 5);

    // 绘制血条前景
    QRectF healthRect(1, 1, (width() - 2) * m_value, height() - 2);

    // 创建渐变效果
    QLinearGradient gradient(healthRect.topLeft(), healthRect.topRight());
    QColor startColor(255, 60, 60); // 红色
    QColor endColor(50, 200, 50);   // 绿色

    // 根据血量比例调整颜色
    if (m_value > 0.5) {
        endColor = QColor(50, 200, 50);
    } else if (m_value > 0.2) {
        endColor = QColor(255, 165, 0); // 橙色
    } else {
        endColor = QColor(220, 20, 20); // 深红色
    }

    gradient.setColorAt(0, startColor);
    gradient.setColorAt(1, endColor);

    painter.setBrush(gradient);
    painter.drawRoundedRect(healthRect, 4, 4);

    // 绘制边框
    painter.setPen(QPen(QColor(150, 150, 150), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(bgRect, 5, 5);

    // 绘制血量文字
    QString text = QString("%1/%2").arg(m_currentHealth).arg(m_maxHealth);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 9, QFont::Bold));
    painter.drawText(bgRect, Qt::AlignCenter, text);
}

void HealthBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}
