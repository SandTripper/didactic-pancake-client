#ifndef LABELPLUS_H
#define LABELPLUS_H

#include <QLabel>
#include <QWidget>
#include <QMenu>

class LabelPlus : public QLabel
{
    Q_OBJECT
public:
    LabelPlus(QWidget *parent = 0);

    ~LabelPlus();

    //获取右键菜单对象
    QMenu *getContextMenu();

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event);

    //重写右键菜单事件
    void contextMenuEvent(QContextMenuEvent *event);

private:
    //初始化控件
    void initControl();
    //右键菜单
    QMenu *m_contextMenu;

private:
    //显示的文本
    QString m_str;
};

#endif // LABELPLUS_H
