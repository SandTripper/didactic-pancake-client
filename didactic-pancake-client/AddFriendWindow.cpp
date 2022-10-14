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
    m_query_user_name("")
{

    m_connect = TcpConnect::getInstance();


    ui->setupUi(this);

    initControl();
    initTitleBar();

    connect(m_connect, &TcpConnect::SCUpackAdd, this, &AddFriendWindow::checkSearch);
    connect(m_connect, &TcpConnect::ADFpackAdd, this, &AddFriendWindow::checkAddFriend);

    setFixedHeight(NO_SEARCH_RESULT_HEIGHT);

    setBackgroundColor(255, 255, 255);

    m_titleBar->raise();
}

AddFriendWindow::~AddFriendWindow()
{
    delete ui;
}

void AddFriendWindow::initTitleBar()
{
    m_titleBar->setBackgroundColor(255, 255, 255);
    // m_titleBar->setTitleIcon(":/resource/default_avatar.png");
    // m_titleBar->setTitleContent(QStringLiteral("登录"));
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}

void AddFriendWindow::initControl()
{

    QRegExpValidator *pRevalidotor = new QRegExpValidator(QRegExp("[a-zA-Z0-9]{25}"), this);

    QString qss_edit_user_name =
            "QLineEdit{border: 1px solid rgb(25,198,136);}" //默认
            "QLineEdit{padding-left: 5px; }"                //文本距离左边界有5px
            "QLineEdit{border-radius: 3px;}";

    ui->edit_user_name->setStyleSheet(qss_edit_user_name);
    ui->edit_user_name->setMaxLength(16);
    ui->edit_user_name->setValidator(pRevalidotor);


    QString qss_btn_search =
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

    ui->btn_search->setStyleSheet(qss_btn_search);

    QString qss_btn_add_friend =
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

    ui->btn_add_friend ->setStyleSheet(qss_btn_add_friend);
    ui->btn_add_friend ->setVisible(false);

    ui->lbl_user_avatar->setPixmap(QPixmap(":/resource/default_avatar.png"));
    ui->lbl_user_avatar->setScaledContents(true);
    ui->lbl_user_avatar->setCursor(QCursor(Qt::PointingHandCursor));
    ui->lbl_user_avatar->setVisible(false);

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

void AddFriendWindow::checkSearch()
{
    for (const auto &data : m_connect->vec[TcpConnect::SCU])
    {
        if (data.content_len == 0)
            continue;
        if (strncmp(data.content, "-2", 2) == 0)
        {
            ui->lbl_wrongtip->setText("格式错误");
            ui->btn_search->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "0", 1) == 0)
        {
            ui->lbl_wrongtip->setText("该用户名不存在!");

            ui->edit_user_name->clear();
            ui->edit_user_name->setFocus();

            ui->btn_search->setDisabled(false);
            continue;
        }

        //搜索成功
        ui->btn_search->setDisabled(false);
        ui->lbl_user_name->setText(m_query_user_name);
        m_connect->vec[TcpConnect::SCU].clear();
        ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
        ui->lbl_wrongtip->setText("查找成功！");

        ui->lbl_user_name->setVisible(true);
        ui->lbl_user_avatar->setVisible(true);
        ui->btn_add_friend->setVisible(true);
        setFixedHeight(WITH_SEARCH_RESULT_HEIGHT);
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
            ui->btn_search->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "-2", 2) == 0)
        {
            ui->lbl_wrongtip->setText("格式错误");
            ui->btn_search->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "-1", 2) == 0)
        {
            ui->lbl_wrongtip->setText("重复发送好友请求");
            ui->btn_search->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "0", 1) == 0)
        {
            ui->lbl_wrongtip->setText("格式错误");
            ui->btn_search->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "2", 1) == 0)
        {
            ui->lbl_wrongtip->setText("该用户已经是好友");
            ui->btn_search->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            continue;
        }
        if (strncmp(data.content, "3", 1) == 0)
        {
            ui->lbl_wrongtip->setText("该用户已经向你提交了好友申请");
            ui->btn_search->setDisabled(false);
            ui->btn_add_friend->setDisabled(false);
            ui->edit_user_name->setDisabled(false);
            continue;
        }

        //请求已发送
        ui->btn_search->setDisabled(false);
        ui->btn_add_friend->setDisabled(false);
        ui->edit_user_name->setDisabled(false);
        ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(25,198,136)}");
        ui->lbl_wrongtip->setText("好友请求已发送");
        break;
    }
    m_connect->vec[TcpConnect::ADF].clear();
}



void AddFriendWindow::on_btn_search_clicked()
{
    ui->btn_search->setDisabled(true);
    ui->btn_add_friend->setFocus();
    ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(197,34,31)};");
    ui->lbl_wrongtip->setText("");

    if (ui->edit_user_name->text() == "")
    {
        ui->lbl_wrongtip->setText("用户名不得为空");
        ui->edit_user_name->setFocus();
        ui->btn_search->setDisabled(false);
        return;
    }

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
    ui->btn_search->setDisabled(true);
    ui->btn_add_friend->setDisabled(true);
    ui->edit_user_name->setDisabled(true);

    ui->lbl_wrongtip->setStyleSheet("QLabel{color:rgb(197,34,31)};");
    ui->lbl_wrongtip->setText("");


    QString content = ui->lbl_user_name->text() + "\r\n";

    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();

    m_connect->write_data(DataPacket(TcpConnect::ADF, content.length(),ctmp));
}
