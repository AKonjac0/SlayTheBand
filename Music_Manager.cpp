#include "Music_Manager.h"


Music_Manager::Music_Manager() : effect (new QSoundEffect){

}

Music_Manager::~Music_Manager(){
    delete effect;
}
void Music_Manager::play(QString s){
    effect->setSource(QUrl::fromLocalFile(s));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.25f); //音量  0~1之间
    effect->play();
}
