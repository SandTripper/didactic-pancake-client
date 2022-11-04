#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QSoundEffect>

class SoundPlayer
{
public:
    SoundPlayer();

    ~SoundPlayer();
    //播放新消息提示音效
    void playNewMessageEffect();

private:
    //新消息提示音效
    QSoundEffect *m_newMessageEffect;
};

#endif // SOUNDPLAYER_H
