#include "VoiceChatWindow.h"
#include "ui_VoiceChatWindow.h"

#include <QCloseEvent>
#include <QPainter>
#include <QString>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QPixmap>

#include "BaseTitleBar.h"
#include "Config.h"
#include "FileProcess.h"

using namespace std;

VoiceChatWindow::VoiceChatWindow(const QString &targetUserName, MY_TYPE type, QWidget *parent) : BaseWindow(parent),
    ui(new Ui::VoiceChatWindow),
    m_tcpConnect(TcpConnect::getInstance()),
    m_targetUserName(targetUserName),
    m_type(type),
    m_wait_ball_type_cnt(0),
    m_soundHangUp(new SoundPlayer(SoundPlayer::HANG_UP_RING)),
    m_soundVoiceChat(new SoundPlayer(SoundPlayer::VOICE_CHAT_RING))
{
    ui->setupUi(this);

    initThis();
    initControl();
    initTitleBar();
    tick(0);
}

VoiceChatWindow::~VoiceChatWindow()
{
    delete m_soundVoiceChat;
    delete m_soundHangUp;
    delete ui;
}

void VoiceChatWindow::initThis()
{
    //设置背景颜色
    setBackgroundColor(25, 25, 25);

    //关闭自动释放内存
    setAttribute(Qt::WA_DeleteOnClose);

    connect(m_tcpConnect,&TcpConnect::AOCpackAdd,this,&VoiceChatWindow::handleAOCpackAdd);

    connect(m_tcpConnect,&TcpConnect::SOCpackAdd,this,&VoiceChatWindow::handleSOCpackAdd);

    connect(m_tcpConnect,&TcpConnect::DOCpackAdd,this,&VoiceChatWindow::handleDOCpackAdd);

    connect(m_titleBar,&BaseTitleBar::signalButtonCloseClicked,this,&VoiceChatWindow::on_btn_close_clicked);
}

void VoiceChatWindow::initTitleBar()
{

    m_titleBar->setBackgroundColor(25, 25, 25);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);

    QString qss_pButtonMin =
            "QPushButton:!hover:!pressed{border-image: url(:/resource/m_btn_min_normal.png)}" //默认
            "QPushButton:hover{border-image: url(:/resource/m_btn_min_normal.png)}"            //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/m_btn_min_press.png)}";         //鼠标点击
    QString qss_pButtonClose =
            "QPushButton:!hover:!pressed{border-image: url(:/resource/m_btn_close_normal.png)}" //默认
            "QPushButton:hover{border-image: url(:/resource/m_pButtonClose_hover.png)}"            //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/m_pButtonClose_press.png)}";         //鼠标点击
    m_titleBar->setButtonStyle(qss_pButtonMin,"","",qss_pButtonClose);

}

void VoiceChatWindow::initControl()
{
    //设置头像
    QPixmap pix;
    QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" +m_targetUserName+ ".png");
    if (file.open(QIODevice::ReadOnly))
    {
        pix.loadFromData(file.readAll());
        file.close();
    }
    else
    {
        pix.load(":/resource/default_avatar.png");
    }
    ui->lbl_avatar->setPixmap(pix.scaled(ui->lbl_avatar->width(), ui->lbl_avatar->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->lbl_avatar->setScaledContents(true);

    //设置聊天对象名字
    QString qss_lbl_target_name =
            "color:rgb(255,255,255)"; //默认
    ui->lbl_target_name->setStyleSheet(qss_lbl_target_name);
    ui->lbl_target_name->setText(m_targetUserName);

    //设置text1
    QString qss_lbl_text1 =
            "color:rgb(127,127,127)"; //默认
    ui->lbl_text1->setStyleSheet(qss_lbl_text1);

    //设置lbl_cancel
    QString qss_lbl_cancel =
            "color:rgb(255,255,255)"; //默认
    ui->lbl_cancel->setStyleSheet(qss_lbl_cancel);

    //设置lbl_hang_up
    QString qss_lbl_hang_up =
            "color:rgb(255,255,255)"; //默认
    ui->lbl_hang_up->setStyleSheet(qss_lbl_hang_up);

    //设置接通时间显示
    QString qss_lbl_chat_time =
            "color:rgb(255,255,255)"; //默认
    ui->lbl_chat_time->setStyleSheet(qss_lbl_chat_time);

    //设置挂断按钮和取消按钮
    QString qss_btn_hang_up =
            "QPushButton{border-image: url(:/resource/btn_hang_up_normal.png)}"         //默认
            "QPushButton:hover{border-image: url(:/resource/btn_hang_up_hover.png)}"    //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/btn_hang_up_press.png)}"; //鼠标点击
    ui->btn_cancel->setStyleSheet(qss_btn_hang_up);
    ui->btn_hang_up->setStyleSheet(qss_btn_hang_up);
    ui->btn_cancel->setToolTip(QStringLiteral("取消"));
    ui->btn_hang_up->setToolTip(QStringLiteral("挂断"));
    ui->btn_cancel->setCursor(QCursor(Qt::PointingHandCursor));
    ui->btn_hang_up->setCursor(QCursor(Qt::PointingHandCursor));

    m_wait_ball_types_pix[0]=QPixmap(":resource/lbl_voice_chat_wait_ball_type1");
    m_wait_ball_types_pix[1]=QPixmap(":resource/lbl_voice_chat_wait_ball_type2");
    m_wait_ball_types_pix[2]=QPixmap(":resource/lbl_voice_chat_wait_ball_type3");

    //设置接听按钮
    QString qss_btn_accept =
            "QPushButton{border-image: url(:/resource/video_chat_btn_accept_normal_60x60.png)}"         //默认
            "QPushButton:hover{border-image: url(:/resource/video_chat_btn_accept_hover_60x60.png)}"    //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/video_chat_btn_accept_press_60x60.png)}"; //鼠标点击
    ui->btn_accept->setStyleSheet(qss_btn_accept);

    //设置拒绝按钮
    QString qss_btn_reject =
            "QPushButton{border-image: url(:/resource/video_chat_btn_reject_normal_60x60.png)}"         //默认
            "QPushButton:hover{border-image: url(:/resource/video_chat_btn_reject_hover_60x60.png)}"    //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/video_chat_btn_reject_press_60x60.png)}"; //鼠标点击
    ui->btn_reject->setStyleSheet(qss_btn_reject);

    //设置lbl_accept
    QString qss_lbl_accept =
            "color:rgb(255,255,255)"; //默认
    ui->lbl_accept->setStyleSheet(qss_lbl_accept);

    //设置lbl_reject
    QString qss_lbl_reject =
            "color:rgb(255,255,255)"; //默认
    ui->lbl_reject->setStyleSheet(qss_lbl_reject);

    //设置等待动效图片
    m_wait_ball_types[0][0] = 2;
    m_wait_ball_types[0][1] = 1;
    m_wait_ball_types[0][2] = 0;
    m_wait_ball_types[1][0] = 1;
    m_wait_ball_types[1][1] = 2;
    m_wait_ball_types[1][2] = 0;
    m_wait_ball_types[2][0] = 0;
    m_wait_ball_types[2][1] = 1;
    m_wait_ball_types[2][2] = 2;

    ui->lbl_wait_ball_1->setScaledContents(true);
    ui->lbl_wait_ball_2->setScaledContents(true);
    ui->lbl_wait_ball_3->setScaledContents(true);

    if(m_type==WAITING_FOR_ACCEPT)
    {
        ui->btn_hang_up->hide();
        ui->lbl_hang_up->hide();

        ui->btn_accept->hide();
        ui->btn_reject->hide();

        ui->lbl_accept->hide();
        ui->lbl_reject->hide();
        ui->lbl_chat_time->hide();
    }
    else if(m_type==CHOOSE_ACCEPT_OR_NOT)
    {
        ui->btn_hang_up->hide();
        ui->lbl_hang_up->hide();

        ui->btn_cancel->hide();
        ui->lbl_cancel->hide();

        ui->lbl_text1->hide();
        ui->lbl_chat_time->hide();
    }
}

void VoiceChatWindow::tick(int tot)
{
    if(m_type==WAITING_FOR_ACCEPT&&tot==0)
    {
        ui->lbl_wait_ball_1->setPixmap(m_wait_ball_types_pix[m_wait_ball_types[m_wait_ball_type_cnt%3][0]]);
        ui->lbl_wait_ball_2->setPixmap(m_wait_ball_types_pix[m_wait_ball_types[m_wait_ball_type_cnt%3][1]]);
        ui->lbl_wait_ball_3->setPixmap(m_wait_ball_types_pix[m_wait_ball_types[m_wait_ball_type_cnt%3][2]]);
        ++m_wait_ball_type_cnt;
    }
    else if(m_type==CHATTING)
    {
        uint curTime = QDateTime::currentDateTime().toTime_t();

        if(m_chatTime!=curTime-m_startTime)
        {
            m_chatTime = curTime-m_startTime;

            ui->lbl_chat_time->setText(formatTime(m_chatTime));
        }
    }
    QTimer::singleShot(100, this, [=]()
    { tick((tot+1)%5); });
}

void VoiceChatWindow::changeTypeToChatting()
{
    if(m_type==WAITING_FOR_ACCEPT)
    {
        ui->btn_cancel->hide();
        ui->lbl_cancel->hide();

        ui->lbl_text1->hide();
        ui->lbl_wait_ball_1->hide();
        ui->lbl_wait_ball_2->hide();
        ui->lbl_wait_ball_3->hide();
    }
    else if(m_type==CHOOSE_ACCEPT_OR_NOT)
    {
        ui->btn_accept->hide();
        ui->btn_reject->hide();

        ui->lbl_accept->hide();
        ui->lbl_reject->hide();
    }

    ui->btn_hang_up->show();
    ui->lbl_hang_up->show();
    ui->lbl_chat_time->show();

    m_type = CHATTING;

    m_startTime = QDateTime::currentDateTime().toTime_t();

    m_chatTime = 0;
}

QString VoiceChatWindow::formatTime(uint times)
{
    QString formatTime = "";
    uint curMinute = times/60;
    uint curSecond = times%60;
    if(curMinute==0)
    {
        formatTime += "00:";
    }
    else if(0<curMinute&&curMinute<10)
    {
        formatTime += "0"+QString::number(curMinute)+":";
    }
    else
    {
       formatTime += QString::number(curMinute)+":";
    }

    if(curSecond==0)
    {
        formatTime += "00";
    }
    else if(0<curSecond&&curSecond<10)
    {
        formatTime += "0"+QString::number(curSecond);
    }
    else
    {
       formatTime += QString::number(curSecond);
    }

    return formatTime;
}

//模态显示函数
void VoiceChatWindow::exec()
{
    show();
    m_Loop = new QEventLoop(this);
    m_Loop->exec(); //利用事件循环实现模态
}

void VoiceChatWindow::show()
{
    BaseWindow::show();
    m_soundVoiceChat->playSound(0.5,-1);
}


void VoiceChatWindow::handleAOCpackAdd()
{
    for (const auto &data : m_tcpConnect->vec[TcpConnect::AOC])
    {
        if (data.content_len == 0)
            continue;

        QString str_id = "";

        for (int i = 0; i < data.content_len - 1; i++)
        {
            if (data.content[i] == '\r' && data.content[i + 1] == '\n')
            {
                break;
            }
            if (isdigit(data.content[i]))
            {
                str_id += data.content[i];
            }
            else
            {
                m_tcpConnect->vec[TcpConnect::AOC].clear();
                return;
            }
        }
        m_voiceChat=new VoiceChat(str_id.toInt());
        m_voiceChat->start();
        break;
    }
    m_tcpConnect->vec[TcpConnect::AOC].clear();
    m_soundVoiceChat->stop();
    changeTypeToChatting();
}

void VoiceChatWindow::handleSOCpackAdd()
{
    for (const auto &data : m_tcpConnect->vec[TcpConnect::SOC])
    {
        if (data.content_len == 0)
            continue;

        if (strncmp(data.content, "-1", 2) == 0) //对方不在线
        {
            m_tcpConnect->vec[TcpConnect::SOC].clear();
            m_soundHangUp->playSound(0.5,1);
            emit closed(FRIEND_OFFLINE,"");
            QTimer::singleShot(1000, this, [=]()
            { close(); });
            return;
        }
        else if (strncmp(data.content, "0", 1) == 0) //对方忙
        {
            m_tcpConnect->vec[TcpConnect::SOC].clear();
            m_soundVoiceChat->stop();
            m_soundHangUp->playSound(0.5,1);
            emit closed(FRIEND_BUSY,"");
            QTimer::singleShot(1000, this, [=]()
            { close(); });
            return;
        }
    }
    m_tcpConnect->vec[TcpConnect::SOC].clear();
}

void VoiceChatWindow::handleDOCpackAdd()
{
    m_tcpConnect->vec[TcpConnect::DOC].clear();
    switch (m_type)
    {
    case WAITING_FOR_ACCEPT:
        emit closed(FRIEND_REJECT,"");
        break;
    case CHOOSE_ACCEPT_OR_NOT:
        emit closed(FRIEND_CANCEL,"");
        break;
    case CHATTING:
        emit closed(NORMAL_CALL,formatTime(m_chatTime));
        m_voiceChat->stop();
        break;
    }
    m_soundVoiceChat->stop();
    m_soundHangUp->playSound(0.5,1);
    QTimer::singleShot(1000, this, [=]()
    { close(); });
}

void VoiceChatWindow::on_btn_accept_clicked()
{
    m_tcpConnect->write_data(DataPacket(TcpConnect::ROC,3,"1\r\n"));
}

void VoiceChatWindow::on_btn_reject_clicked()
{
    m_tcpConnect->write_data(DataPacket(TcpConnect::ROC,3,"0\r\n"));
    m_soundVoiceChat->stop();
    m_soundHangUp->playSound(0.5,1);
    emit closed(REJECT,"");
    QTimer::singleShot(1000, this, [=]()
    { close(); });
}

void VoiceChatWindow::on_btn_cancel_clicked()
{
    m_tcpConnect->write_data(DataPacket(TcpConnect::EOC,0,""));
    m_soundVoiceChat->stop();
    m_soundHangUp->playSound(0.5,1);
    emit closed(CANCEL,"");
    QTimer::singleShot(1000, this, [=]()
    { close(); });
}

void VoiceChatWindow::on_btn_hang_up_clicked()
{
    m_tcpConnect->write_data(DataPacket(TcpConnect::EOC,0,""));
    m_voiceChat->stop();
    m_soundHangUp->playSound(0.5,1);
    emit closed(NORMAL_CALL,formatTime(m_chatTime));
    QTimer::singleShot(1000, this, [=]()
    { close(); });
}

void VoiceChatWindow::on_btn_close_clicked()
{
    switch (m_type)
    {
    case WAITING_FOR_ACCEPT:
        on_btn_cancel_clicked();
        break;
    case CHOOSE_ACCEPT_OR_NOT:
        on_btn_reject_clicked();
        break;
    case CHATTING:
        on_btn_hang_up_clicked();
        break;
    }
}
