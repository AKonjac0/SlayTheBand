#include "Card_Button.h"

Card_Button::Card_Button(CardController *control, QWidget *parent) : control(control), parent(parent), next_round_click(true){
    next_round = new QPushButton("next_round", parent);
    next_round->setGeometry(50, 460, 100, 60);
    control->applyDrawCardAnimation();

    QObject::connect(next_round, &QPushButton::clicked, parent, [this]() {
        // 应用动画效果
        if(next_round_click){
            next_round_click = false;

            this->control->applyDisCardAnimation();
            this->control->applyDrawCardAnimation();
            // 这里可以添加按钮原有的点击逻辑
            qDebug() << "下一回合";
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, SLOT(quit()));
            loop.exec();
            if(!loop.isRunning()){
                next_round_click = true;
            }
        }

    });
}

Card_Button::~Card_Button(){
    delete next_round;
}
