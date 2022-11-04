#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : m_newMessageEffect(new QSoundEffect)
{
    m_newMessageEffect->setSource(QUrl::fromLocalFile(":/resource/message_tone.wav"));
    m_newMessageEffect->setVolume(0.5f); //音量  0~1之间
}

SoundPlayer::~SoundPlayer()
{
    delete m_newMessageEffect;
}

void SoundPlayer::playNewMessageEffect()
{
    m_newMessageEffect->play();
}
