#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H
#include <QSoundEffect>

class Music_Manager{

public:
    void play(QString);
    Music_Manager();
    ~Music_Manager();
private:
    QSoundEffect *effect;
};
#endif // MUSIC_MANAGER_H
