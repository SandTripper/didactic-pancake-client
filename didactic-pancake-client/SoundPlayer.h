#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QSoundEffect>

class SoundPlayer
{
public:

    enum SOUND_NAME
    {
        NEW_MESSAGE,
        VOICE_CHAT_RING,
        HANG_UP_RING
    };

    SoundPlayer(SOUND_NAME sound);

    ~SoundPlayer();
    //播放新消息提示音效
    void playSound(float volume,int times);

    //停止播放
    void stop();

private:
    //声音播放
    QSoundEffect *m_soundEffect;
};

#endif // SOUNDPLAYER_H
