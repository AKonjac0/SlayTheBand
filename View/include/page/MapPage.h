#ifndef MAPPAGE_H
#define MAPPAGE_H
#include <QWidget>
#include <QPushButton>

class MapPage : public QWidget
{
public:
    MapPage(QWidget *parent = nullptr);
    ~MapPage() = default;
private:
    QWidget *parent;
    QPushButton *level1;
    QPushButton *switchBtn;

    friend class PageManager;
};

#endif //MAPPAGE_H
