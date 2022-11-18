#include "SoundPlayer.h"



SoundPlayer::SoundPlayer(SoundPlayer::SOUND_NAME sound): m_soundEffect(new QSoundEffect)
{
    switch (sound)
    {
    case NEW_MESSAGE:
        m_soundEffect->setSource(QUrl::fromLocalFile(":/resource/message_tone.wav"));
        break;
    case VOICE_CHAT_RING:
        m_soundEffect->setSource(QUrl::fromLocalFile(":/resource/voice_chat_ring.wav"));
        break;
    case HANG_UP_RING:
        m_soundEffect->setSource(QUrl::fromLocalFile(":/resource/hang_up_ring.wav"));
        break;
    }
}

SoundPlayer::~SoundPlayer()
{
    delete m_soundEffect;
}

void SoundPlayer::playSound(float volume,int times)
{
    m_soundEffect->setVolume(volume); //音量  0~1之间
    if(times==-1)
    {
        m_soundEffect->setLoopCount(QSoundEffect::Infinite);
    }
    else
    {
        m_soundEffect->setLoopCount(times);
    }
    m_soundEffect->play();
}

void SoundPlayer::stop()
{
    m_soundEffect->stop();
}
