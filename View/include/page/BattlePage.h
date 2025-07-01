#ifndef BATTLEPAGE_H
#define BATTLEPAGE_H
#include <QWidget>
#include "QPushButton"

class BattlePage : public QWidget
{
public:
    BattlePage(QWidget *parent);
    ~BattlePage() = default;
private:
    QWidget *parent;
    QPushButton *switchBtn;

    friend class PageManager;
};

#endif //BATTLEPAGE_H
