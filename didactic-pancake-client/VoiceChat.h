#ifndef VOICECHAT_H
#define VOICECHAT_H

#include <QtNetwork/QUdpSocket>
#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#define UDP_PORT 10086
#define MAX_AUDIO_LEN 960000 //如果接收缓冲区大于这个数值就剪掉
#define FRAME_LEN_60ms 960 //每一个语音帧长度是960字节

class AudioSendThread;
class AudioRecvThread;

class VoiceChat:public QObject
{
    Q_OBJECT
public:
    VoiceChat(int chat_id);

    ~VoiceChat();

    void start();

    void stop();

private:
    QUdpSocket *m_udpSocket;

    AudioSendThread *m_audioSendThread;

    AudioRecvThread *m_audioRecvThread;


};

//发送线程
class AudioSendThread:public QThread
{
    Q_OBJECT
public:
    explicit AudioSendThread(int chat_id, QUdpSocket *udpSocket,QObject *parent = nullptr);

    ~AudioSendThread();

    struct voice
    {
        int id;
        int lens;
        char data[960];
    };


    QUdpSocket *m_udpSocket;//用于音频信号的发送

    QAudioInput *m_input;

    QIODevice *m_inputDevice;

    QHostAddress m_tarAddress;

    int m_chat_id;

    // 设置当前的采样率、采样位数、通道数目
    void setAudioFormat(int sampleRate, int channelCount, int sampleSize);

    void myStart();

    void myStop();

private slots:
    void readVoice();
};

//接收线程
class AudioRecvThread:public QThread
{
    Q_OBJECT
public:
    struct voice
    {
        int id;
        int lens;
        char data[960];
    };

    explicit AudioRecvThread(QUdpSocket *udpSocket,QObject *parent = nullptr);

    ~AudioRecvThread();

    // 设置当前的采样率、采样位数、通道数目
    void setAudioFormat(int sampleRate, int channelCount, int sampleSize);

    virtual void run(void) override;//多线程重载运行函数run

    void stop();


private slots:
    void writeVoice();

private:

    // 添加数据
    void addAudioBuffer(char* pData, int len);
    // 清空当前的数据
    void cleanAllAudioBuffer(void);

private:

    QUdpSocket *m_udpSocket;//用于音频信号的接收

    QAudioOutput *m_output;

    QIODevice *m_outputDevice;

    QAudioFormat m_format;

    QHostAddress m_tarAddress;

    QByteArray m_PCMDataBuffer;

    int m_CurrentPlayIndex;

    QMutex m_lock;

    int m_isStop;
};


#endif // VOICECHAT_H
