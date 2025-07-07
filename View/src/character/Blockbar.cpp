#include "Blockbar.h"
#include <QPainter>
#include <QLinearGradient>

BlockBar::BlockBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(10);
    setFixedWidth(168);
    m_animation = new QPropertyAnimation(this, "value", this);
    m_animation->setDuration(500); // 动画时长500ms
    m_animation->setEasingCurve(QEasingCurve::OutQuad);
}

void BlockBar::setMaxBlock(int max)
{
    m_maxBlock = max;
    update();
}

void BlockBar::setCurrentBlock(int current)
{
    m_currentBlock = qBound(0, current, m_maxBlock);
    m_animation->stop();
    m_animation->setStartValue(m_value);
    m_animation->setEndValue(static_cast<float>(m_currentBlock) / m_maxBlock);
    m_animation->start();
}

void BlockBar::setValue(float value)
{
    m_value = value;
    update();
}

void BlockBar::paintEvent(QPaintEvent *event)
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
    QRectF blockRect(1, 1, (width() - 2) * m_value, height() - 2);

    // 创建渐变效果
    QLinearGradient gradient(blockRect.topLeft(), blockRect.topRight());
    QColor startColor(153, 217, 234);
    QColor endColor(153, 217, 234);

    // 根据血量比例调整颜色
    if (m_value > 0.5) {
        endColor = QColor(153, 217, 234);
    } else if (m_value > 0.2) {
        endColor = QColor(153, 217, 234);
    } else {
        endColor = QColor(153, 217, 234);
    }

    gradient.setColorAt(0, startColor);
    gradient.setColorAt(1, endColor);

    painter.setBrush(gradient);
    painter.drawRoundedRect(blockRect, 4, 4);

    // 绘制边框
    painter.setPen(QPen(QColor(150, 150, 150), 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(bgRect, 5, 5);

    // 绘制血量文字
    QString text = QString("%1/%2").arg(m_currentBlock).arg(m_maxBlock);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 9, QFont::Bold));
    painter.drawText(bgRect, Qt::AlignCenter, text);
}

void BlockBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}
