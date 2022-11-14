#include "SelectNewAvatarWindow.h"
#include "ui_SelectNewAvatarWindow.h"

#include <QCloseEvent>
#include <QPainter>
#include <QString>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>

#include "Config.h"
#include "FileProcess.h"

using namespace std;

SelectNewAvatarWindow::SelectNewAvatarWindow(QWidget *parent) : BaseWindow(parent),
                                                                ui(new Ui::SelectNewAvatarWindow),
                                                                m_tcpConnect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
    initTitleBar();
}

SelectNewAvatarWindow::~SelectNewAvatarWindow()
{
    delete ui;
}

void SelectNewAvatarWindow::initThis()
{
    //设置背景颜色
    setBackgroundColor(255, 255, 255);

    connect(m_tcpConnect, &TcpConnect::SAVpackAdd, this, &SelectNewAvatarWindow::handleSAVpackAdd);
}

void SelectNewAvatarWindow::initTitleBar()
{
    m_titleBar->setBackgroundColor(255, 255, 255);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}

void SelectNewAvatarWindow::initControl()
{
    QPixmap pix;
    QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" + Config::loginedUserName + ".png");
    if (file.open(QIODevice::ReadOnly))
    {
        pix.loadFromData(file.readAll());
        file.close();
    }
    else
    {
        pix.load(":/resource/default_avatar.png");
    }
    ui->lbl_new_avator->setPixmap(pix.scaled(ui->lbl_new_avator->width(), ui->lbl_new_avator->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->lbl_new_avator->setScaledContents(true);

    QString qss_btn_select_avatar_file =
        "QPushButton{background-color:rgb(255,255,255);}" //按钮颜色
        "QPushButton{color: rgb(0,0,0); }"                //文字颜色
        "QPushButton{border-radius: 2px;}"                //圆角半径
        "QPushButton{border: 1px solid rgb(235,235,235)}" //边框
        "QPushButton:hover{background-color:rgb(255,255,255);}"
        "QPushButton:hover{color: rgb(25,198,136); }"
        "QPushButton:hover{border-radius: 2px;}"
        "QPushButton:hover{border: 1px solid rgb(25,198,136)}"
        "QPushButton:pressed{background-color:rgb(255,255,255);}"
        "QPushButton:pressed{color: rgb(20,168,106); }"
        "QPushButton:pressed{border-radius: 2px;}"
        "QPushButton:pressed{border: 1px solid rgb(20,168,106)}";
    ui->btn_select_avatar_file->setStyleSheet(qss_btn_select_avatar_file);

    QString qss_btn_yes =
        "QPushButton{background-color:rgb(25,198,136);}" //按钮颜色
        "QPushButton{color: rgb(255,255,255); }"         //文字颜色
        "QPushButton{border-radius: 2px;}"               //圆角半径
        "QPushButton:hover{background-color:rgb(20,168,106);}"
        "QPushButton:hover{color: rgb(255,255,255); }"
        "QPushButton:hover{border-radius: 2px;}"
        "QPushButton:pressed{background-color:rgb(15,138,76);}"
        "QPushButton:pressed{color: rgb(255,255,255); }"
        "QPushButton:pressed{border-radius: 2px;}";
    ui->btn_yes->setStyleSheet(qss_btn_yes);

    QString qss_btn_cancel =
        "QPushButton{background-color:rgb(255,255,255);}" //按钮颜色
        "QPushButton{color: rgb(0,0,0); }"                //文字颜色
        "QPushButton{border-radius: 2px;}"                //圆角半径
        "QPushButton{border: 1px solid rgb(235,235,235)}" //边框
        "QPushButton:hover{background-color:rgb(255,255,255);}"
        "QPushButton:hover{color: rgb(25,198,136); }"
        "QPushButton:hover{border-radius: 2px;}"
        "QPushButton:hover{border: 1px solid rgb(25,198,136)}"
        "QPushButton:pressed{background-color:rgb(255,255,255);}"
        "QPushButton:pressed{color: rgb(20,168,106); }"
        "QPushButton:pressed{border-radius: 2px;}"
        "QPushButton:pressed{border: 1px solid rgb(20,168,106)}";
    ui->btn_cancel->setStyleSheet(qss_btn_cancel);
}

//模态显示函数
void SelectNewAvatarWindow::exec()
{
    show();
    m_Loop = new QEventLoop(this);
    m_Loop->exec(); //利用事件循环实现模态
}

//重写关闭事件
void SelectNewAvatarWindow::closeEvent(QCloseEvent *event)
{
    if (m_Loop != NULL)
    {
        m_Loop->exit();
    }
    event->accept();
}

void SelectNewAvatarWindow::on_btn_select_avatar_file_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "更换头像", "", "图片文件(*png *jpg *jpeg)");
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "打开文件失败！", file.errorString());
    }
    else
    {
        m_byteArray = file.readAll();
        m_avatar_pix.loadFromData(m_byteArray);
        ui->lbl_new_avator->setPixmap(m_avatar_pix);

        file.close();
    }
}

void SelectNewAvatarWindow::on_btn_yes_clicked()
{
    if (m_byteArray.size() == 0)
    {
        return;
    }
    m_tcpConnect->write_data(DataPacket(TcpConnect::SAV, m_byteArray.size(), m_byteArray.data()));
}

void SelectNewAvatarWindow::handleSAVpackAdd()
{
    for (const auto &data : m_tcpConnect->vec[TcpConnect::SAV])
    {
        if (data.content_len == 0)
            continue;
        FileProcess::saveFile(m_byteArray, QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original", Config::loginedUserName + ".png");
        QPixmap pix;
        pix.loadFromData(m_byteArray);
        FileProcess::saveQPixmap(pix.scaled(40, 40, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/40x40", Config::loginedUserName + ".png");
        FileProcess::saveQPixmap(pix.scaled(34, 34, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/34x34", Config::loginedUserName + ".png");
        emit myAvatarChanged();
        m_tcpConnect->vec[TcpConnect::SAV].clear();
        close();
        return;
    }
    m_tcpConnect->vec[TcpConnect::SAV].clear();
}

void SelectNewAvatarWindow::on_btn_cancel_clicked()
{
    close();
}
