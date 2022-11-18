#include "VoiceChat.h"


VoiceChat::VoiceChat(int chat_id):
    m_udpSocket( new QUdpSocket(this)),
    m_audioSendThread(new AudioSendThread(chat_id,m_udpSocket)),
    m_audioRecvThread(new AudioRecvThread(m_udpSocket))
{
    m_udpSocket -> bind(QHostAddress::Any, UDP_PORT);

    //发送线程
    m_audioSendThread->setAudioFormat(8000,1,16);
    //接受线程
    m_audioRecvThread->setAudioFormat(8000,1,16);
}

VoiceChat::~VoiceChat()
{
    delete m_udpSocket;
    delete m_audioSendThread;
    delete m_audioRecvThread;
}

void VoiceChat::start()
{
    m_audioSendThread->myStart();
    m_audioRecvThread->start();
}

void VoiceChat::stop()
{
    m_audioSendThread->myStop();
    m_audioRecvThread->stop();
}

///////////////////////////////////////////////////////////////////////

AudioSendThread::AudioSendThread(int chat_id, QUdpSocket *udpSocket, QObject *parent):
    QThread(parent)
{
    m_udpSocket = udpSocket;

    m_chat_id = chat_id;

    m_tarAddress.setAddress("1.117.146.195");
}

AudioSendThread::~AudioSendThread()
{
    delete m_input;
    delete m_inputDevice;
}

void AudioSendThread::setAudioFormat(int sampleRate, int channelCount, int sampleSize)
{
    QAudioFormat format;

    format.setSampleRate(sampleRate);
    format.setChannelCount(channelCount);
    format.setSampleSize(sampleSize);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);

    m_input = new QAudioInput(format, this);
}


void AudioSendThread::myStart()
{
    m_inputDevice = m_input->start();
    connect(m_inputDevice,SIGNAL(readyRead()),this,SLOT(readVoice()));
}

void AudioSendThread::myStop()
{
    m_input->stop();
    disconnect(m_inputDevice,SIGNAL(readyRead()),this,SLOT(readVoice()));
}

void AudioSendThread::readVoice()
{

    voice vp;
    memset(&vp,0,sizeof(vp));

    //读取音频
    vp.lens = m_inputDevice->read(vp.data,960);//读取音频
    vp.id = m_chat_id;
    m_tarAddress.setAddress("1.117.146.195");
    m_udpSocket->writeDatagram((const char*)&vp,sizeof(vp),m_tarAddress,4400);//将此结构体发送给目标主机
}
/////////////////////////////////////////////////////////////////

AudioRecvThread::AudioRecvThread(QUdpSocket *udpSocket, QObject *parent):
    QThread(parent)
{

    m_udpSocket = udpSocket;

    m_PCMDataBuffer.clear();
    connect(m_udpSocket,SIGNAL(readyRead()),this,SLOT(writeVoice()));//收到网络数据报就开始往outputDevice写入，进行播放

    m_CurrentPlayIndex = 0;
    m_isStop = false;
}

AudioRecvThread::~AudioRecvThread()
{
    delete m_output;
    delete m_outputDevice;
}

void AudioRecvThread::setAudioFormat(int sampleRate, int channelCount, int sampleSize)
{
    QAudioFormat format;
    format.setSampleRate(sampleRate);
    format.setSampleSize(sampleSize);
    format.setChannelCount(channelCount);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);

    m_output = new QAudioOutput(format,this);
    m_outputDevice = m_output->start();
}

void AudioRecvThread::run()
{
    while (!this->isInterruptionRequested())
    {
        QMutexLocker locker(&m_lock);
        if(m_isStop)
            break;
        if(m_PCMDataBuffer.size() < m_CurrentPlayIndex + FRAME_LEN_60ms)
        {//缓冲区不够播放60ms音频
            continue;
        }
        else{

            //拷贝960字节的数据
            char *writeData = new char[FRAME_LEN_60ms];
            memcpy(writeData,&m_PCMDataBuffer.data()[m_CurrentPlayIndex], FRAME_LEN_60ms);
            // 写入音频数据
            m_outputDevice->write(writeData, FRAME_LEN_60ms);
            m_CurrentPlayIndex += FRAME_LEN_60ms;
            delete []writeData;

            //如果长度超过了MAX_AUDIO_LEN就截掉
            if(m_CurrentPlayIndex > MAX_AUDIO_LEN)
            {
                m_PCMDataBuffer = m_PCMDataBuffer.right(m_PCMDataBuffer.size()-MAX_AUDIO_LEN);
                m_CurrentPlayIndex -= MAX_AUDIO_LEN;
            }
        }
    }
    m_PCMDataBuffer.clear();
}

void AudioRecvThread::stop()
{
    m_udpSocket->close();
    m_output->stop();
    cleanAllAudioBuffer();
}

void AudioRecvThread::writeVoice()
{
    while(m_udpSocket->hasPendingDatagrams())
    {
        QHostAddress senderip;
        quint16 senderport;
        voice vp;
        memset(&vp,0,sizeof(vp));
        m_udpSocket->readDatagram((char*)&vp,sizeof(vp),&senderip,&senderport);
        addAudioBuffer(vp.data, vp.lens);
    }
}

void AudioRecvThread::addAudioBuffer(char *pData, int len)
{
    QMutexLocker locker(&m_lock);

    m_PCMDataBuffer.append(pData, len);
}

void AudioRecvThread::cleanAllAudioBuffer()
{
    QMutexLocker locker(&m_lock);
    m_CurrentPlayIndex = 0;
    m_PCMDataBuffer.clear();
    m_isStop = true;
}
