#include "Arrow.h"

Arrow::Arrow(QWidget *parent) : QWidget(parent), mousePos(100, 100)
{
    setMouseTracking(true);
    // 加载图片资源 (确保图片文件在可执行文件目录或正确路径)
    blockImg.load(":image/images/reticleBlock.png");
    arrowImg.load(":image/images/reticleArrow.png");
    setFixedSize(1920, 1080);
    // setAttribute(Qt::WA_TransparentForMouseEvents, true);

    // 如果加载失败，使用彩色方块替代
    if(blockImg.isNull()) {
        blockImg = QImage(20, 20, QImage::Format_ARGB32);
        blockImg.fill(Qt::blue);
    }
    if(arrowImg.isNull()) {
        arrowImg = QImage(20, 20, QImage::Format_ARGB32);
        arrowImg.fill(Qt::red);
    }
}
void Arrow::mouseMoveEvent(QMouseEvent *event) {
    mousePos = event->pos();
    update(); // 触发重绘
}

void Arrow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. 计算起点（屏幕底部中心）
    QPointF startPoint(width() / 2.0, height());
    QPointF endPoint = mousePos;

    // 2. 计算直线和中点
    QLineF line(startPoint, endPoint);
    painter.drawLine(line);
    QPointF midPoint = line.center();
    if(mousePos.x() - width() / 2 == 0){
        return;
    }
    // qDebug() << mousePos.x() << " " << width() / 2.0;
    double d = 160000.0 / abs(mousePos.x() - width() / 2.0);


    // 3. 计算圆心（中点垂直上方100单位）
    // 获取直线方向向量
    QPointF lineVec = line.p2() - line.p1();
    // 计算垂直向量（逆时针旋转90度）
    QPointF perpendicularVec;
    if(lineVec.x() < 0){
        perpendicularVec = QPointF(lineVec.y(), -lineVec.x());
    }else{
        perpendicularVec = QPointF(-lineVec.y(), lineVec.x());
    }

    // 归一化
    qreal length = std::sqrt(perpendicularVec.x()*perpendicularVec.x() +
                             perpendicularVec.y()*perpendicularVec.y());
    if (length > 0.0001) {
        perpendicularVec /= length;
    }


    // 计算圆心位置（中点 + 垂直方向100单位）
    QPointF circleCenter = midPoint + d * perpendicularVec;

    // 4. 计算半径和角度
    qreal radius = QLineF(circleCenter, startPoint).length();

    // 计算圆弧起始角度和结束角度
    QPointF startVec = startPoint - circleCenter;
    QPointF endVec = endPoint - circleCenter;

    qreal startAngle = std::atan2(startVec.y(), startVec.x());
    qreal endAngle = std::atan2(endVec.y(), endVec.x());

    // 5. 绘制圆弧
    QRectF arcRect(circleCenter.x() - radius,
                   circleCenter.y() - radius,
                   2 * radius, 2 * radius);
    qreal startDeg = qRadiansToDegrees(startAngle) * 16;
    qreal endDeg = qRadiansToDegrees(endAngle) * 16;
    qreal spanDeg = endDeg - startDeg;

    // 确保绘制的是劣弧（小于180度）
    if (spanDeg > 180 * 16) {
        spanDeg -= 360 * 16;
    } else if (spanDeg < -180 * 16) {
        spanDeg += 360 * 16;
    }

    painter.drawArc(arcRect, startDeg, spanDeg);
    // paint center

    painter.setPen(Qt::red);  // 设置红色画笔
    painter.setBrush(Qt::red);  // 设置红色填充
    painter.drawEllipse(circleCenter, 5, 5);  // 绘制半径为5的实心圆点

    // 6. 在圆弧上均匀分布10个Block - 关键修改在这里
    // 计算实际绘制的劣弧的结束角度
    qreal actualEndAngle = startAngle + qDegreesToRadians(spanDeg / 16);

    for (int i = 1; i <= 10; ++i) {
        qreal t = i / 11.0; // 均匀分布（不包括端点）
        // 使用调整后的实际劣弧角度进行插值
        qreal angle = startAngle + t * (actualEndAngle - startAngle);

        QPointF pointOnArc(
            circleCenter.x() + radius * std::cos(angle),
            circleCenter.y() + radius * std::sin(angle)
            );

        // 计算切线方向（圆弧的切线方向）
        QPointF tangent;
        if(lineVec.x() < 0) tangent = QPointF(-std::sin(angle), std::cos(angle));
        else tangent = QPointF(std::sin(angle), -std::cos(angle));
        qreal rotation = qRadiansToDegrees(std::atan2(-tangent.x(), tangent.y()));

        // 绘制旋转后的图像
        drawRotatedImage(painter, blockImg, pointOnArc, rotation);
    }

    // 7. 在鼠标位置（终点）绘制Arrow
    // 计算终点处的切线方向
    QPointF endTangent;
    if(lineVec.x() < 0) endTangent = QPointF(-std::sin(endAngle), std::cos(endAngle));
    else endTangent = QPointF(std::sin(endAngle), -std::cos(endAngle));
    qreal endRotation = qRadiansToDegrees(std::atan2(-endTangent.x(), endTangent.y()));
    drawRotatedImage(painter, arrowImg, endPoint, endRotation);
}
void Arrow::drawRotatedImage(QPainter &painter, const QImage &img, const QPointF &pos, qreal rotation) {
    painter.save();
    painter.translate(pos);
    painter.rotate(rotation);
    painter.drawImage(-img.width() / 2, -img.height() / 2, img);
    painter.restore();
}

void Arrow::mousePressEvent(QMouseEvent *event)
{
    if (this->parentWidget())
    {
        //点下去的那一刻屏蔽当前窗口及其所有子部件的事件，此时被当前窗口遮挡住的父窗口的控件的事件被响应
        //为什么不到这里就结束，因为如果这样做，只要点击过一次，当前窗口及其子部件就再也不会响应鼠标事件，比如移入移出
        //因此点击之后还必须要把这个屏蔽取消掉
        //但如果中间什么也不做的话，这个属性的设置就没有意义，因为最终是false
        //所以需要手动将鼠标点击事件下发给父窗口中的对应部件
        this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        QPoint point = this->mapTo(this->parentWidget(), event->pos());    //将点击事件在当前部件的坐标转换为在父窗口坐标系中的坐标
        QWidget *widget = this->parentWidget()->childAt(point);   //判断当前点击的位置是否是父窗口的一个子部件
        if (widget)
        {
            point = widget->mapFrom(this->parentWidget(), point);    //将当前部件在父窗口的坐标转为在当前部件自己的坐标系中的坐标
            QMouseEvent *mouseEvent = new QMouseEvent(event->type(), point, event->button(), event->buttons(), event->modifiers());
            QApplication::postEvent(widget, mouseEvent);
        }
        this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}
void Arrow::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->parentWidget())
    {
        //点下去的那一刻屏蔽当前窗口及其所有子部件的事件，此时被当前窗口遮挡住的父窗口的控件的事件被响应
        //为什么不到这里就结束，因为如果这样做，只要点击过一次，当前窗口及其子部件就再也不会响应鼠标事件，比如移入移出
        //因此点击之后还必须要把这个屏蔽取消掉
        //但如果中间什么也不做的话，这个属性的设置就没有意义，因为最终是false
        //所以需要手动将鼠标点击事件下发给父窗口中的对应部件
        this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        QPoint point = this->mapTo(this->parentWidget(), event->pos());    //将点击事件在当前部件的坐标转换为在父窗口坐标系中的坐标
        QWidget *widget = this->parentWidget()->childAt(point);   //判断当前点击的位置是否是父窗口的一个子部件
        if (widget)
        {
            point = widget->mapFrom(this->parentWidget(), point);    //将当前部件在父窗口的坐标转为在当前部件自己的坐标系中的坐标
            QMouseEvent *mouseEvent = new QMouseEvent(event->type(), point, event->button(), event->buttons(), event->modifiers());
            QApplication::postEvent(widget, mouseEvent);
        }
        this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}
