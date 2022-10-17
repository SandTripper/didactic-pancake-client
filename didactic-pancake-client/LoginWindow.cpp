#include <QCloseEvent>
#include <QPainter>
#include <QString>
#include <QRegExpValidator>

#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "LabelPlus.h"
#include "RegisterWindow.h"

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) : BaseWindow(parent),
                                            ui(new Ui::LoginWindow),
                                            m_session(""),
                                            m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
    initTitleBar();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::initThis()
{
    connect(m_connect, &TcpConnect::LGNpackAdd, this, &LoginWindow::checkLogin);
    connect(m_connect, &TcpConnect::disconnected, this, &LoginWindow::handleDisconnected);

    //设置背景颜色
    setBackgroundColor(255, 255, 255);
}

void LoginWindow::initTitleBar()
{
    m_titleBar->setBackgroundColor(255, 255, 255);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}

void LoginWindow::initControl()
{
    //注册按钮
    QString qss_lbl_register =
        "QLabel:!hover:!pressed{color:rgb(25,198,136)}" //默认
        "QLabel:hover{color:rgb(20,168,106)}"           //鼠标hover
        "QLabel:pressed{color:rgb(15,138,86)}";         //鼠标点击
    ui->lbl_register->setStyleSheet(qss_lbl_register);

    //用以用户名和密码的格式限制
    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{16}"), this);

    QString qss_edit_username =
        "QLineEdit{border: 1px solid rgb(25,198,136);}" //边框粗细和颜色
        "QLineEdit{padding-left: 5px; }"                //文本和左边界的距离
        "QLineEdit{border-radius: 3px;}";               //圆角半径
    ui->edit_username->setStyleSheet(qss_edit_username);
    ui->edit_username->setMaxLength(16);
    ui->edit_username->setValidator(pRevalidotor);

    QString qss_edit_password =
        "QLineEdit{border: 1px solid rgb(25,198,136);}" //边框粗细和颜色
        "QLineEdit{padding-left: 5px; }"                //文本和左边界的距离
        "QLineEdit{border-radius: 3px;}";               //圆角半径
    ui->edit_password->setStyleSheet(qss_edit_password);
    ui->edit_password->setMaxLength(16);
    ui->edit_password->setValidator(pRevalidotor);

    //登录按钮
    QString qss_btn_login =
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
    ui->btn_login->setStyleSheet(qss_btn_login);

    //记住账号按钮
    QString qss_chk_remember_user =
        "QCheckBox{color:rgb(25,198,136)};"; //文字颜色
    ui->chk_remember_user->setStyleSheet(qss_chk_remember_user);

    //提示框
    QString qss_lbl_wrongtip =
        "QLabel{color:rgb(197,34,31)};"; //文字颜色
    ui->lbl_wrongtip->setStyleSheet(qss_lbl_wrongtip);
}

//模态显示函数
LoginData LoginWindow::exec()
{
    show();
    m_Loop = new QEventLoop(this);
    m_Loop->exec(); //利用事件循环实现模态

    return LoginData{m_session, ui->edit_username->text(), pos().x(), pos().y()};
}

//重写关闭事件
void LoginWindow::closeEvent(QCloseEvent *event)
{
    if (m_Loop != NULL)
    {
        m_Loop->exit();
    }
    event->accept();
}

void LoginWindow::on_btn_login_clicked()
{
    if (!m_connect->m_enable) //如果与服务器的连接不可用
    {
        ui->lbl_wrongtip->setText("无法连接到服务器!");
        return;
    }
    //禁用登录,输入框，单选框，注册按钮
    ui->btn_login->setDisabled(true);
    ui->edit_username->setDisabled(true);
    ui->edit_password->setDisabled(true);
    ui->chk_remember_user->setDisabled(true);
    ui->lbl_register->setDisabled(true);

    ui->lbl_wrongtip->setText("");

    if (ui->edit_username->text() == "")
    {
        ui->lbl_wrongtip->setText("用户名不得为空");
        //启用登录,输入框，单选框，注册按钮
        ui->btn_login->setDisabled(false);
        ui->edit_username->setDisabled(false);
        ui->edit_password->setDisabled(false);
        ui->chk_remember_user->setDisabled(false);
        ui->lbl_register->setDisabled(false);

        ui->edit_username->setFocus();
        return;
    }

    if (ui->edit_password->text() == "")
    {
        ui->lbl_wrongtip->setText("密码不得为空");
        //启用登录,输入框，单选框，注册按钮
        ui->btn_login->setDisabled(false);
        ui->edit_username->setDisabled(false);
        ui->edit_password->setDisabled(false);
        ui->chk_remember_user->setDisabled(false);
        ui->lbl_register->setDisabled(false);

        ui->edit_password->setFocus();
        return;
    }

    //向服务器发送登录信息
    QString content = ui->edit_username->text() + "\r\n" + ui->edit_password->text() + "\r\n";
    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();

    m_connect->write_data(DataPacket(TcpConnect::LGN, content.length(), ctmp));
}

void LoginWindow::on_lbl_register_clicked()
{
    RegisterWindow reg;

    reg.move(pos().x() + 30, pos().y() + 30);
    reg.setWindowModality(Qt::ApplicationModal); //设为模态
    QString username = reg.exec();
    if (username != "") //如果有注册用户
    {
        ui->edit_username->setText(username); //自动将注册的用户名填充的用户名输入栏
        ui->edit_password->clear();           //清除密码框
        ui->edit_password->setFocus();
    }
    else //没有注册用户，保持原来的输入框
    {
        //将焦点定位到正确的地方
        if (ui->edit_username->text() == "")
        {
            ui->edit_username->setFocus();
        }
        else
        {
            ui->edit_password->setFocus();
        }
    }
}

void LoginWindow::checkLogin()
{
    for (const auto &data : m_connect->vec[TcpConnect::LGN])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-1", 2) == 0) //用户在线
        {
            ui->lbl_wrongtip->setText("用户已在线，请勿重复登陆!");

            //启用登录,输入框，单选框，注册按钮
            ui->btn_login->setDisabled(false);
            ui->edit_username->setDisabled(false);
            ui->edit_password->setDisabled(false);
            ui->chk_remember_user->setDisabled(false);
            ui->lbl_register->setDisabled(false);

            continue;
        }
        if (strncmp(data.content, "0", 1) == 0) //用户名或密码错误
        {
            ui->lbl_wrongtip->setText("用户名或密码错误!");

            //启用登录,输入框，单选框，注册按钮
            ui->btn_login->setDisabled(false);
            ui->edit_username->setDisabled(false);
            ui->edit_password->setDisabled(false);
            ui->chk_remember_user->setDisabled(false);
            ui->lbl_register->setDisabled(false);

            if (ui->chk_remember_user->isChecked()) //记住账号
            {
                ui->edit_password->clear();
                ui->edit_password->setFocus();
            }
            else
            {
                ui->edit_username->clear();
                ui->edit_password->clear();
                ui->edit_username->setFocus();
            }
            continue;
        }

        //登录成功
        m_session = QString::fromStdString(string(data.content, data.content + data.content_len - 2));
        m_connect->vec[TcpConnect::LGN].clear();
        ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
        ui->lbl_wrongtip->setText("登录成功！");

        m_connect->m_sessionID = m_session;
        //锁死页面
        setDisabled(true);
        QTimer::singleShot(500, this, [=]()
                           { close(); });
        return;
    }
    m_connect->vec[TcpConnect::LGN].clear();
}

void LoginWindow::handleDisconnected()
{
    //启用登录,输入框，单选框，注册按钮
    ui->btn_login->setDisabled(false);
    ui->edit_username->setDisabled(false);
    ui->edit_password->setDisabled(false);
    ui->chk_remember_user->setDisabled(false);
    ui->lbl_register->setDisabled(false);

    ui->lbl_wrongtip->setText("无法连接到服务器!");
}
