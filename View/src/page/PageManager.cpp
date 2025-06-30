#include "PageManager.h"
#include "Arrow.h"
#include <QPushButton>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
PageManager::PageManager(QWidget *parent, int page_width, int page_height)
    : parent(parent), page_width(page_width), page_height(page_height) {
    // 创建页面1
    page1 = new Arrow(parent);
    page1->setGeometry(0, 0, page_width, page_height);
    page1->setAutoFillBackground(true);

    // 加载并设置背景图片
    QPixmap bkgnd(":/image/images/Background1.jpg");
    if(bkgnd.isNull()) {
        qDebug() << "Failed to load background image!";
    } else {
        bkgnd = bkgnd.scaled(page1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        page1->setPalette(palette);
    }

    // 创建页面2
    page2 = new QWidget(parent);
    page2->setGeometry(0, 0, page_width, page_height);
    page2->setAutoFillBackground(true);

    // 初始化页面2为透明并隐藏在右侧
    page2->setWindowOpacity(0.0);
    page2->move(page_width, 0);

    // 创建切换按钮1
    switchBtn1 = new QPushButton(page1);
    switchBtn1->move(1830, 20);
    switchBtn1->resize(64, 64);
    QString BtnPic = "QPushButton{border-image: url(:image/images/map.png);}";
    switchBtn1->setStyleSheet(BtnPic);

    // 创建切换按钮2
    switchBtn2 = new QPushButton(page2);
    switchBtn2->move(1830, 20);
    switchBtn2->resize(64, 64);
    switchBtn2->setStyleSheet(BtnPic);

    // 连接按钮信号到动画切换
    QAbstractButton::connect(switchBtn1, &QPushButton::clicked, [this](){
        switchToPage(page2, PageAnimationDirection::RightToLeft);
    });

    QAbstractButton::connect(switchBtn2, &QPushButton::clicked, [this](){
        switchToPage(page1, PageAnimationDirection::LeftToRight);
    });

    page1->show();
    page2->show();
    now_page = page1;
}

void PageManager::switchToPage(QWidget *targetPage, PageAnimationDirection direction) {
    if (now_page == targetPage || animationInProgress) {
        return;
    }

    animationInProgress = true;
    QWidget *currentPage = now_page;
    now_page = targetPage;

    // 创建动画组
    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;

    // 当前页面动画 - 淡出
    QPropertyAnimation *fadeOut = new QPropertyAnimation(currentPage, "windowOpacity");
    fadeOut->setDuration(300);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    // 当前页面动画 - 滑动
    QPropertyAnimation *slideOut = new QPropertyAnimation(currentPage, "pos");
    slideOut->setDuration(300);
    slideOut->setStartValue(currentPage->pos());

    // 目标页面动画 - 淡入
    QPropertyAnimation *fadeIn = new QPropertyAnimation(targetPage, "windowOpacity");
    fadeIn->setDuration(300);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    // 目标页面动画 - 滑动
    QPropertyAnimation *slideIn = new QPropertyAnimation(targetPage, "pos");
    slideIn->setDuration(300);

    // 根据方向设置滑动动画
    if (direction == PageAnimationDirection::RightToLeft) {
        // 从右向左滑动
        targetPage->move(page_width, 0);
        slideIn->setStartValue(QPoint(page_width, 0));
        slideIn->setEndValue(QPoint(0, 0));

        slideOut->setEndValue(QPoint(-page_width, 0));
    } else {
        // 从左向右滑动
        targetPage->move(-page_width, 0);
        slideIn->setStartValue(QPoint(-page_width, 0));
        slideIn->setEndValue(QPoint(0, 0));

        slideOut->setEndValue(QPoint(page_width, 0));
    }

    // 将动画添加到动画组
    animationGroup->addAnimation(fadeOut);
    animationGroup->addAnimation(slideOut);
    animationGroup->addAnimation(fadeIn);
    animationGroup->addAnimation(slideIn);

    // 动画完成后的处理
    QAbstractButton::connect(animationGroup, &QParallelAnimationGroup::finished, [this, animationGroup, currentPage]() {
        // 重置当前页面位置和透明度
        currentPage->move(0, 0);
        currentPage->setWindowOpacity(1.0);

        // 清理动画对象
        animationGroup->deleteLater();

        animationInProgress = false;
    });

    // 开始动画
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);

    // 提升目标页面
    targetPage->raise();
}

PageManager::~PageManager() {
    delete switchBtn1;
    delete page1;
    delete switchBtn2;
    delete page2;
}

QWidget *PageManager::get_now_page() {
    return now_page;
}
