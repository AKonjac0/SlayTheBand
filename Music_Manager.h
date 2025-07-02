#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H
#include <QSoundEffect>
#include <QWidget>
class Music_Manager{

public:
    void play(QString);
    Music_Manager(QWidget *parent = nullptr);
    ~Music_Manager();
private:
    QSoundEffect *effect;
    QWidget *parent;
};
#endif // MUSIC_MANAGER_H
