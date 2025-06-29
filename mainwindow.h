#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Card_Manager.h"
#include "CardView.h"
#include "Player.h"
#include "Music_Manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Card_Manager *card_manager;
    CardView *card_view;
    Player *player;
    Music_Manager *music;
};
#endif // MAINWINDOW_H
