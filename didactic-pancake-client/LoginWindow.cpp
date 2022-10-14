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
                                            m_session("")
{

    m_connect = TcpConnect::getInstance();

    connect(m_connect, &TcpConnect::LGNpackAdd, this, &LoginWindow::checkLogin);

    ui->setupUi(this);

    initControl();
    initTitleBar();

    setBackgroundColor(255, 255, 255);

    m_titleBar->raise();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::initTitleBar()
{
    m_titleBar->setBackgroundColor(255, 255, 255);
    // m_titleBar->setTitleIcon(":/resource/pancake.png");
    // m_titleBar->setTitleContent(QStringLiteral("登录"));
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}

void LoginWindow::initControl()
{
    QString qss_lbl_register =
        "QLabel:!hover:!pressed{color:rgb(25,198,136)}" //默认
        "QLabel:hover{color:rgb(20,168,106)}"           //鼠标hover
        "QLabel:pressed{color:rgb(15,138,86)}";         //鼠标点击
    ui->lbl_register->setStyleSheet(qss_lbl_register);

    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{25}"), this);

    QString qss_edit_username =
        "QLineEdit{border: 1px solid rgb(25,198,136);}" //默认
        "QLineEdit{padding-left: 5px; }"                //文本距离左边界有5px
        "QLineEdit{border-radius: 3px;}";

    ui->edit_username->setStyleSheet(qss_edit_username);
    ui->edit_username->setMaxLength(16);
    ui->edit_username->setValidator(pRevalidotor);

    QString qss_edit_password =
        "QLineEdit{border: 1px solid rgb(25,198,136);}" //默认
        "QLineEdit{padding-left: 5px; }"                //文本距离左边界有5px
        "QLineEdit{border-radius: 3px;}";
    ui->edit_password->setStyleSheet(qss_edit_password);
    ui->edit_password->setMaxLength(16);
    ui->edit_password->setValidator(pRevalidotor);

    QString qss_btn_login =
        "QPushButton{background-color:rgb(25,198,136);}" //默认
        "QPushButton{color: rgb(255,255,255); }"
        "QPushButton{border-radius: 15px;}"
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

    QString qss_chk_remember_user =
        "QCheckBox{color:rgb(25,198,136)};"; //默认
    ui->chk_remember_user->setStyleSheet(qss_chk_remember_user);

    QString qss_lbl_wrongtip =
        "QLabel{color:rgb(197,34,31)};"; //默认
    ui->lbl_wrongtip->setStyleSheet(qss_lbl_wrongtip);
}

//模态显示函数
std::string LoginWindow::exec()
{
    show();
    m_Loop = new QEventLoop(this);
    m_Loop->exec(); //利用事件循环实现模态

    return m_session;
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

    ui->btn_login->setDisabled(true);
    ui->chk_remember_user->setFocus();

    ui->lbl_wrongtip->setText("");
    if (ui->edit_username->text() == "")
    {
        ui->lbl_wrongtip->setText("用户名不得为空");
        ui->edit_username->setFocus();
        ui->btn_login->setDisabled(false);
        return;
    }

    if (ui->edit_password->text() == "")
    {
        ui->lbl_wrongtip->setText("密码不得为空");
        ui->edit_password->setFocus();
        ui->btn_login->setDisabled(false);
        return;
    }

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
    reg.setWindowModality(Qt::ApplicationModal);
    QString username = reg.exec();
    if (username != "")
    {
        ui->edit_username->setText(username);
        ui->edit_password->setFocus();
    }
    ui->edit_password->setFocus();
}

void LoginWindow::checkLogin()
{
    for (const auto &data : m_connect->vec[TcpConnect::LGN])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-1", 2) == 0)
        {
            ui->lbl_wrongtip->setText("用户已在线，请勿重复登陆!");
            ui->btn_login->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "0", 1) == 0)
        {
            ui->lbl_wrongtip->setText("账户名或密码错误!");
            if (ui->chk_remember_user->isChecked())
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
            ui->btn_login->setDisabled(false);
            continue;
        }

        //登录成功
        m_session = string(data.content, data.content + data.content_len-2);
        m_connect->vec[TcpConnect::LGN].clear();
        ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
        ui->lbl_wrongtip->setText("登录成功！");
        setDisabled(true);
        QTimer::singleShot(500, this, [=]()
                           { close(); });
        return;
    }
    m_connect->vec[TcpConnect::LGN].clear();
}
