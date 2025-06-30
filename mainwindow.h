#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "Card_Manager.h"
#include "CardView.h"
#include "CharacterAnimation.h"
#include "Music_Manager.h"
#include "PageManager.h"

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
    PageManager *page_manager;
    Card_Manager *card_manager;
    CardView *card_view;
    CharacterAnimation* character_animation;
    Music_Manager *music;
};
#endif // MAINWINDOW_H
