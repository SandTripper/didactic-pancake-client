#ifndef SELECTNEWAVATARWINDOW_H
#define SELECTNEWAVATARWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QEvent>
#include <QObject>
#include <string>

#include "TcpConnect.h"
#include "BaseWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SelectNewAvatarWindow;
}
QT_END_NAMESPACE

class SelectNewAvatarWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit SelectNewAvatarWindow(QWidget *parent = nullptr);

    ~SelectNewAvatarWindow();
    //模态显示函数
    void exec();

signals:
    //用户头像更改
    void myAvatarChanged();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:

    void on_btn_select_avatar_file_clicked();

    void on_btn_cancel_clicked();

    void on_btn_yes_clicked();

    //处理头像回复
    void handleSAVpackAdd();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    // 初始化控件;
    void initControl();

    Ui::SelectNewAvatarWindow *ui;

    TcpConnect *m_tcpConnect;

    QEventLoop *m_Loop;

    //文件二进制数组
    QByteArray m_byteArray;

    QPixmap m_avatar_pix;
};

#endif // SELECTNEWAVATARWINDOW_H
