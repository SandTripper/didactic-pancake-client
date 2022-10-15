#ifndef FRIENDREQUSETSITEM_H
#define FRIENDREQUSETSITEM_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "SuspendedScrollbar.h"
#include "TcpConnect.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FriendRequsetsItem;
}
QT_END_NAMESPACE

class FriendRequsetsItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendRequsetsItem(QWidget *parent = nullptr, const QString &username = "", QListWidgetItem *item = nullptr);

    ~FriendRequsetsItem();

signals:
    //将自己从所在的列表删除
    void deleteMe(QListWidgetItem *object);

private slots:
    //点击接受按钮
    void on_btn_accept_clicked();
    //点击拒绝按钮
    void on_btn_reject_clicked();

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

private:
    Ui::FriendRequsetsItem *ui;

    QListWidgetItem *m_item;
    //指向服务器的连接对象
    TcpConnect *m_connect;
};

class FriendRequsetsListWidget : public SuspendedScrollBar_ListWidget
{
    Q_OBJECT
public:
    explicit FriendRequsetsListWidget(QWidget *parent = nullptr);

    ~FriendRequsetsListWidget() {}

    //添加申请者窗口
    void addRequest(const QString &username);

    //删除申请者窗口
    void deleteRequest(QListWidgetItem *object);

private:
    void initThis();
};

#endif // FRIENDREQUSETSITEM_H
