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
                                                  m_username("")
{

    m_connect = TcpConnect::getInstance();

    connect(m_connect, &TcpConnect::RGTpackAdd, this, &RegisterWindow::checkRegister);

    ui->setupUi(this);

    initControl();
    initTitleBar();

    setBackgroundColor(255, 255, 255);

    m_titleBar->raise();
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
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
    ui->edit_password1->setStyleSheet(qss_edit_password);
    ui->edit_password2->setStyleSheet(qss_edit_password);

    ui->edit_password1->setMaxLength(16);
    ui->edit_password2->setMaxLength(16);

    ui->edit_password1->setValidator(pRevalidotor);
    ui->edit_password2->setValidator(pRevalidotor);

    QString qss_btn_register =
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

    ui->btn_register->setStyleSheet(qss_btn_register);

    QString qss_lbl_wrongtip =
        "QLabel{color:rgb(197,34,31)};"; //默认
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

    ui->btn_register->setDisabled(true);
    ui->edit_password2->setFocus();

    ui->lbl_wrongtip->setText("");
    if (ui->edit_username->text() == "")
    {
        ui->lbl_wrongtip->setText("用户名不得为空");
        ui->edit_username->setFocus();
        ui->btn_register->setDisabled(false);
        return;
    }

    if (ui->edit_password1->text() == "")
    {
        ui->lbl_wrongtip->setText("密码不得为空");
        ui->edit_password1->setFocus();
        ui->btn_register->setDisabled(false);
        return;
    }

    if (ui->edit_password1->text() != ui->edit_password2->text())
    {
        ui->lbl_wrongtip->setText("两次密码不一致");
        ui->edit_password1->setFocus();
        ui->btn_register->setDisabled(false);
        return;
    }

    QString content = ui->edit_username->text() + "\r\n" + ui->edit_password1->text() + "\r\n";

    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();

    m_connect->write_data(DataPacket(TcpConnect::RGT, ctmp, content.length()));
}

void RegisterWindow::checkRegister()
{
    for (const auto &data : m_connect->vec[TcpConnect::RGT])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-1", 2) == 0)
        {
            ui->lbl_wrongtip->setText("用户名非法!");
            ui->btn_register->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "0", 1) == 0)
        {
            ui->lbl_wrongtip->setText("该用户名已被注册!");
            ui->btn_register->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "1", 1) == 0) //注册成功
        {
            m_username = ui->edit_username->text();
            m_connect->vec[TcpConnect::RGT].clear();
            ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
            ui->lbl_wrongtip->setText("注册成功！");
            setDisabled(true);
            QTimer::singleShot(500, this, [=]()
                               { close(); });
            return;
        }
        ui->lbl_wrongtip->setText("服务器错误!");
        ui->btn_register->setDisabled(false);
    }
    m_connect->vec[TcpConnect::RGT].clear();
}
