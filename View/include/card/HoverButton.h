#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H
#include <QPushButton>
#include <QPropertyAnimation>
#include <QEvent>
#include <QEasingCurve>

// test only

class HoverButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QPoint posOffset READ posOffset WRITE setPosOffset) // 声明可动画属性

public:
    explicit HoverButton(const QString &name, QWidget *parent = nullptr, bool isHover = false)
        : QPushButton(name, parent), m_originalPos(this->pos()), m_posOffset(QPoint(0, 0)), parent(parent), isAnimating(false), isHover(isHover), isSelected(false)
    {
        // if(isHover)
        installEventFilter(this);  // 安装事件过滤器
    }

    // 获取当前偏移量
    QPoint posOffset() const; // used only in moc

    // 设置偏移量并更新位置
    void setPosOffset(const QPoint &offset); // used only in moc

    bool &Animating(){
        return isAnimating;
    }
    bool &Hover(){
        return isHover;
    }
    bool &Selected(){
        return isSelected;
    }

protected:
    // 事件过滤器处理鼠标进入/离开
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    // 启动动画效果
    void startHoverAnimation(int yOffset);
private:

    QPoint m_originalPos;     // 原始位置
    QPoint m_posOffset;       // 当前位置偏移量
    QWidget *parent;
    QPropertyAnimation *m_animation = nullptr; // 动画指针
    bool isAnimating = false;
    bool isHover = false;
    bool isSelected = false;
};

#endif // HOVERBUTTON_H
