#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "Card_Manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void onButtonClicked();
    // void applyButtonAnimation(QPushButton *button);
    void applyDrawCardAnimation();
    void applyDisCardAnimation();

private:
    Ui::MainWindow *ui;
    Card_Manager *card_manager;
    void setupButtonAnimations();
};
#endif // MAINWINDOW_H
