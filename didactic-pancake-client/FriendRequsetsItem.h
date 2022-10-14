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
    explicit FriendRequsetsItem(QWidget *parent = nullptr,const QString&username = "",QListWidgetItem *item = nullptr);
    ~FriendRequsetsItem();

    void setUserName(const QString&username);


signals:
    void deleteMe(QListWidgetItem *object);

public slots:

private slots:
    void on_btn_accept_clicked();

    void on_btn_reject_clicked();

private:
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

private:
    Ui::FriendRequsetsItem *ui;

    QListWidgetItem *m_item;

    TcpConnect* m_connect;
};


class FriendRequsetsListWidget : public SuspendedScrollBar_ListWidget {
    Q_OBJECT
public:
    explicit FriendRequsetsListWidget(QWidget * parent = 0);
    ~FriendRequsetsListWidget(){}

    void addRequest(const QString &username);

    void deleteRequest(QListWidgetItem *object);

};

#endif // FRIENDREQUSETSITEM_H
