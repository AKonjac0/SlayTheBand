#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPainter>

#include <QWidget>


// class MyWidget : public QWidget {

// public:
//     explicit MyWidget(QWidget *parent = nullptr) : QWidget(parent) {}

// protected:
//     // 重写 paintEvent 事件处理函数
//     void paintEvent(QPaintEvent *event) override {
//         Q_UNUSED(event); // 避免未使用参数警告

//         QPainter painter(this); // 创建 QPainter 对象，绑定到当前窗口

//         // === 在此处添加绘图代码 ===
//         // 示例：绘制一个红色矩形
//         QImage bg;
//         bg.load("E:/shrike_sos/images/scene.png");



//         QImage silent;
//         silent.load("E:/shrike_sos/images/image.png");


//         painter.drawImage(0, 0, bg);
//         painter.drawImage(300, 300, silent);


//     }
// };
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();
}

