#include <QCloseEvent>
#include <QPainter>
#include <QString>
#include <QRegExpValidator>

#include "AddFriendWindow.h"
#include "ui_AddFriendWindow.h"
#include "LabelPlus.h"
#include "RegisterWindow.h"

using namespace std;

AddFriendWindow::AddFriendWindow(QWidget *parent) : BaseWindow(parent),
    ui(new Ui::AddFriendWindow),
    m_connect(TcpConnect::getInstance()),
    m_query_user_name("")

{
    ui->setupUi(this);

    initThis();
    initControl();
    initTitleBar();
}

AddFriendWindow::~AddFriendWindow()
{
    delete ui;
}

void AddFriendWindow::initThis()
{
    connect(m_connect, &TcpConnect::SCUpackAdd, this, &AddFriendWindow::checkSearch);
    connect(m_connect, &TcpConnect::ADFpackAdd, this, &AddFriendWindow::checkAddFriend);

    //设置高度
    setFixedHeight(NO_SEARCH_RESULT_HEIGHT);
    //设置背景颜色
    setBackgroundColor(255, 255, 255);
}

void AddFriendWindow::initTitleBar()
{
    m_titleBar->setBackgroundColor(255, 255, 255);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}

void AddFriendWindow::initControl()
{
    //用以用户名的格式限制
    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{16}"), this);
    QString qss_edit_user_name =
            "QLineEdit{border: 1px solid rgb(25,198,136);}" //边框粗细和颜色
            "QLineEdit{padding-left: 5px; }"                //文本和左边界的距离
            "QLineEdit{border-radius: 3px;}";               //圆角半径
    ui->edit_user_name->setStyleSheet(qss_edit_user_name);
    ui->edit_user_name->setValidator(pRevalidotor);

    //搜索按钮
    QString qss_btn_search =
            "QPushButton{background-color:rgb(25,198,136);}" //按钮颜色
            "QPushButton{color: rgb(255,255,255); }"        //按钮文字颜色
            "QPushButton{border-radius: 15px;}"             //按钮圆角半径
            "QPushButton:hover{background-color:rgb(20,168,106);}"
            "QPushButton:hover{color: rgb(255,255,255); }"
            "QPushButton:hover{border-radius: 15px;}"
            "QPushButton:pressed{background-color:rgb(15,138,76);}"
            "QPushButton:pressed{color: rgb(255,255,255); }"
            "QPushButton:pressed{border-radius: 15px;}"
            "QPushButton:disabled{background-color:rgb(143,217,152);}"
            "QPushButton:disabled{color: rgb(255,255,255); }"
            "QPushButton:disabled{border-radius: 15px;}";
    ui->btn_search->setStyleSheet(qss_btn_search);

    //添加好友按钮
    QString qss_btn_add_friend =
            "QPushButton{background-color:rgb(25,198,136);}" //按钮颜色
            "QPushButton{color: rgb(255,255,255); }"            //按钮文字颜色
            "QPushButton{border-radius: 15px;}"                 //按钮圆角半径
            "QPushButton:hover{background-color:rgb(20,168,106);}"
            "QPushButton:hover{color: rgb(255,255,255); }"
            "QPushButton:hover{border-radius: 15px;}"
            "QPushButton:pressed{background-color:rgb(15,138,76);}"
            "QPushButton:pressed{color: rgb(255,255,255); }"
            "QPushButton:pressed{border-radius: 15px;}"
            "QPushButton:disabled{background-color:rgb(143,217,152);}"
            "QPushButton:disabled{color: rgb(255,255,255); }"
            "QPushButton:disabled{border-radius: 15px;}";
    ui->btn_add_friend ->setStyleSheet(qss_btn_add_friend);
    ui->btn_add_friend ->setVisible(false);

    //初始化搜索结果头像
    ui->lbl_user_avatar->setPixmap(QPixmap(":/resource/default_avatar.png"));
    ui->lbl_user_avatar->setScaledContents(true);
    ui->lbl_user_avatar->setCursor(QCursor(Qt::PointingHandCursor));
    ui->lbl_user_avatar->setVisible(false);

    //提示框
    QString qss_lbl_wrongtip =
            "QLabel{color:rgb(197,34,31)};"; //默认
    ui->lbl_wrongtip->setStyleSheet(qss_lbl_wrongtip);
}

//模态显示函数
void AddFriendWindow::exec()
{
    show();
    m_Loop = new QEventLoop(this);
    m_Loop->exec(); //利用事件循环实现模态
}

//重写关闭事件
void AddFriendWindow::closeEvent(QCloseEvent *event)
{
    if (m_Loop != NULL)
    {
        m_Loop->exit();
    }
    event->accept();
}

void AddFriendWindow::on_btn_search_clicked()
{
    //禁用搜索按钮和搜索框
    ui->btn_search->setDisabled(true);
    ui->edit_user_name->setDisabled(true);

    ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(197,34,31)};");
    ui->lbl_wrongtip->setText("");

    if (ui->edit_user_name->text() == "")//用户名为空
    {
        ui->lbl_wrongtip->setText("用户名不得为空");
        //启用搜索按钮和搜索框
        ui->btn_search->setDisabled(false);
        ui->edit_user_name->setDisabled(false);

        ui->edit_user_name->setFocus();
        return;
    }

    //发送搜索用户请求给服务器
    m_query_user_name = ui->edit_user_name->text();
    QString content = ui->edit_user_name->text() + "\r\n";
    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();
    m_connect->write_data(DataPacket(TcpConnect::SCU, content.length(), ctmp));
}

void AddFriendWindow::on_btn_add_friend_clicked()
{
    //禁用搜索按钮和搜索框和添加好友按钮
    ui->btn_search->setDisabled(true);
    ui->edit_user_name->setDisabled(true);
    ui->btn_add_friend->setDisabled(true);

    ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(197,34,31)};");
    ui->lbl_wrongtip->setText("");

     //发送添加好友请求给服务器
    QString content = ui->lbl_user_name->text() + "\r\n";
    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();
    m_connect->write_data(DataPacket(TcpConnect::ADF, content.length(),ctmp));
}

void AddFriendWindow::checkSearch()
{
    for (const auto &data : m_connect->vec[TcpConnect::SCU])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-2", 2) == 0)//格式错误
        {
            ui->lbl_wrongtip->setText("格式错误");

            //启用搜索按钮和搜索框
            ui->btn_search->setDisabled(false);
            ui->edit_user_name->setDisabled(false);

            continue;
        }
        if (strncmp(data.content, "0", 1) == 0)//该用户名不存在
        {
            ui->lbl_wrongtip->setText("该用户名不存在");

            //启用搜索按钮和搜索框
            ui->btn_search->setDisabled(false);
            ui->edit_user_name->setDisabled(false);

            ui->edit_user_name->clear();
            ui->edit_user_name->setFocus();

            continue;
        }

        //搜索成功
        //启用搜索按钮和搜索框
        ui->btn_search->setDisabled(false);
        ui->edit_user_name->setDisabled(false);

        ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
        ui->lbl_wrongtip->setText("查找成功");

        //显示搜索到的用户
        ui->lbl_user_name->setText(m_query_user_name);
        ui->lbl_user_name->setVisible(true);
        ui->lbl_user_avatar->setVisible(true);
        ui->btn_add_friend->setVisible(true);
        setFixedHeight(WITH_SEARCH_RESULT_HEIGHT);

        m_connect->vec[TcpConnect::SCU].clear();
        return;
    }
    m_connect->vec[TcpConnect::SCU].clear();
}

void AddFriendWindow::checkAddFriend()
{
    for (const auto &data : m_connect->vec[TcpConnect::ADF])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-3", 2) == 0)
        {
            ui->lbl_wrongtip->setText("不能添加自己为好友");

            //启用搜索按钮和搜索框和添加好友按钮
            ui->btn_search->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "-2", 2) == 0)
        {
            ui->lbl_wrongtip->setText("格式错误");

            //启用搜索按钮和搜索框和添加好友按钮
            ui->btn_search->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "-1", 2) == 0)
        {
            ui->lbl_wrongtip->setText("重复发送好友请求");
            continue;
        }
        if (strncmp(data.content, "0", 1) == 0)
        {
            ui->lbl_wrongtip->setText("格式错误");
            continue;
        }
        if (strncmp(data.content, "2", 1) == 0)
        {
            ui->lbl_wrongtip->setText("该用户已经是好友");
            continue;
        }
        if (strncmp(data.content, "3", 1) == 0)
        {
            ui->lbl_wrongtip->setText("该用户已经向你提交了好友申请");
            continue;
        }

        //请求已发送
        ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
        ui->lbl_wrongtip->setText("好友请求已发送");
        break;
    }
    m_connect->vec[TcpConnect::ADF].clear();

    //启用搜索按钮和搜索框和添加好友按钮
    ui->btn_search->setDisabled(false);
    ui->edit_user_name->setDisabled(false);
    ui->btn_add_friend->setDisabled(false);
}






