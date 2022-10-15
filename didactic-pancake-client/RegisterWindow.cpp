#include <QCloseEvent>
#include <QPainter>
#include <QString>
#include <QRegExpValidator>
#include <windows.h>

#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"
#include "LabelPlus.h"

using namespace std;

RegisterWindow::RegisterWindow(QWidget *parent) : BaseWindow(parent),
                                                  ui(new Ui::RegisterWindow),
                                                  m_username(""),
                                                  m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
    initTitleBar();
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::initThis()
{
    connect(m_connect, &TcpConnect::RGTpackAdd, this, &RegisterWindow::checkRegister);

    setBackgroundColor(255, 255, 255); //设置窗口背景颜色
}

void RegisterWindow::initTitleBar()
{
    m_titleBar->setBackgroundColor(255, 255, 255);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}

void RegisterWindow::initControl()
{
    //用以用户名和密码的格式限制
    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{16}"), this);

    QString qss_edit_username =
        "QLineEdit{border: 1px solid rgb(25,198,136);}" //边框粗细和颜色
        "QLineEdit{padding-left: 5px; }"                //文本和左边界的距离
        "QLineEdit{border-radius: 3px;}";               //圆角半径
    ui->edit_username->setStyleSheet(qss_edit_username);
    ui->edit_username->setValidator(pRevalidotor);

    QString qss_edit_password =
        "QLineEdit{border: 1px solid rgb(25,198,136);}" //边框粗细和颜色
        "QLineEdit{padding-left: 5px; }"                //文本和左边界的距离
        "QLineEdit{border-radius: 3px;}";               //圆角半径
    ui->edit_password1->setStyleSheet(qss_edit_password);
    ui->edit_password2->setStyleSheet(qss_edit_password);
    ui->edit_password1->setValidator(pRevalidotor);
    ui->edit_password2->setValidator(pRevalidotor);

    //注册按钮
    QString qss_btn_register =
        "QPushButton{background-color:rgb(25,198,136);}" //按钮颜色
        "QPushButton{color: rgb(255,255,255); }"         //文字颜色
        "QPushButton{border-radius: 15px;}"              //圆角半径
        "QPushButton:hover{background-color:rgb(20,168,106);}"
        "QPushButton:hover{color: rgb(255,255,255); }"
        "QPushButton:hover{border-radius: 15px;}"
        "QPushButton:pressed{background-color:rgb(15,138,76);}"
        "QPushButton:pressed{color: rgb(255,255,255); }"
        "QPushButton:pressed{border-radius: 15px;}"
        "QPushButton:disabled{background-color:rgb(143,217,152);}"
        "QPushButton:disabled{color: rgb(255,255,255); }"
        "QPushButton:disabled{border-radius: 15px;}";
    ui->btn_register->setStyleSheet(qss_btn_register);

    QString qss_lbl_wrongtip =
        "QLabel{color:rgb(197,34,31)};"; //文字颜色
    ui->lbl_wrongtip->setStyleSheet(qss_lbl_wrongtip);
}

//模态显示函数
QString RegisterWindow::exec()
{
    show();
    m_Loop = new QEventLoop(this);
    m_Loop->exec(); //利用事件循环实现模态

    return m_username;
}

//重写关闭事件
void RegisterWindow::closeEvent(QCloseEvent *event)
{
    if (m_Loop != NULL)
    {
        m_Loop->exit();
    }
    event->accept();
}

void RegisterWindow::on_btn_register_clicked()
{
    //禁用注册按钮，输入框
    ui->btn_register->setDisabled(true);
    ui->edit_username->setDisabled(true);
    ui->edit_password1->setDisabled(true);
    ui->edit_password2->setDisabled(true);

    ui->lbl_wrongtip->setText("");

    if (ui->edit_username->text() == "")
    {
        ui->lbl_wrongtip->setText("用户名不得为空");
        //启用注册按钮，输入框
        ui->btn_register->setDisabled(false);
        ui->edit_username->setDisabled(false);
        ui->edit_password1->setDisabled(false);
        ui->edit_password2->setDisabled(false);

        ui->edit_username->setFocus();
        return;
    }
    else if (ui->edit_password1->text() == "")
    {
        ui->lbl_wrongtip->setText("密码不得为空");
        //启用注册按钮，输入框
        ui->btn_register->setDisabled(false);
        ui->edit_username->setDisabled(false);
        ui->edit_password1->setDisabled(false);
        ui->edit_password2->setDisabled(false);

        ui->edit_password1->setFocus();
        return;
    }
    else if (ui->edit_password1->text() != ui->edit_password2->text())
    {
        ui->lbl_wrongtip->setText("两次密码不一致");

        //启用注册按钮，输入框
        ui->btn_register->setDisabled(false);
        ui->edit_username->setDisabled(false);
        ui->edit_password1->setDisabled(false);
        ui->edit_password2->setDisabled(false);

        ui->edit_password1->setFocus();
        return;
    }

    //向服务器发送注册请求
    QString content = ui->edit_username->text() + "\r\n" + ui->edit_password1->text() + "\r\n";
    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();
    m_connect->write_data(DataPacket(TcpConnect::RGT, content.length(), ctmp));
}

void RegisterWindow::checkRegister()
{
    for (const auto &data : m_connect->vec[TcpConnect::RGT])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-1", 2) == 0) //用户名非法
        {
            ui->lbl_wrongtip->setText("用户名非法!");
            ui->btn_register->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "0", 1) == 0) //该用户名已被注册
        {
            ui->lbl_wrongtip->setText("该用户名已被注册!");
            ui->btn_register->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "1", 1) == 0) //注册成功
        {
            setDisabled(true);
            m_username = ui->edit_username->text();
            m_connect->vec[TcpConnect::RGT].clear();

            ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
            ui->lbl_wrongtip->setText("注册成功！");

            QTimer::singleShot(500, this, [=]()
                               { close(); });
            return;
        }
        ui->lbl_wrongtip->setText("服务器错误!");
        ui->btn_register->setDisabled(false);
    }
    m_connect->vec[TcpConnect::RGT].clear();

    //启用注册按钮，输入框
    ui->btn_register->setDisabled(false);
    ui->edit_username->setDisabled(false);
    ui->edit_password1->setDisabled(false);
    ui->edit_password2->setDisabled(false);
}
