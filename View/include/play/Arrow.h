#ifndef ARROW_H
#define ARROW_H
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <cmath>

class Arrow : public QWidget
{
    Q_OBJECT

public:
    Arrow(const QPointF &pos, QWidget *parent = nullptr);


protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    // 在指定位置绘制旋转后的图像
    void drawRotatedImage(QPainter &painter, const QImage &img, const QPointF &pos, qreal rotation);
private:
    QPointF mousePos;
    QPointF basePos;
    QImage blockImg;
    QImage arrowImg;
};

#endif // ARROW_H
