#include "HoverButton.h"
#include <QDebug>
// test only

QPoint HoverButton::posOffset() const
{
    return m_posOffset;
}

// 设置偏移量并更新位置
void HoverButton::setPosOffset(const QPoint &offset)
{
    m_posOffset = offset;
    move(m_originalPos + offset);
}


// 事件过滤器处理鼠标进入/离开
bool HoverButton::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::Enter) {
            startHoverAnimation(-100); // 向上移动100像素
            return true;
        } else if (event->type() == QEvent::Leave) {
            startHoverAnimation(0);   // 回到原始位置
            return true;
        }
    }
    return QPushButton::eventFilter(obj, event);
}


// 启动动画效果
void HoverButton::startHoverAnimation(int yOffset)
{
    // 停止当前动画（如果正在运行）


    if(!isHover){
        qDebug() << "error:can't hover";
        return;
    }
    isAnimating = true;
    // 创建新动画
    m_animation = new QPropertyAnimation(this, "posOffset");
    m_animation->setDuration(300); // 动画时长300ms

    // 设置弹性曲线（弹动效果）
    m_animation->setEasingCurve(QEasingCurve::OutBack);


    QPoint point(this->x(), (parent->height() - this->height() + 100) + yOffset);
    // 设置目标值
    m_animation->setStartValue(this->pos());
    m_animation->setEndValue(point);

    // 启动动画
    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(m_animation, &QPropertyAnimation::finished, [this]() {
        this->isAnimating = false;
    });
}



