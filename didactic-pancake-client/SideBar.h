#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SideBar;
}
QT_END_NAMESPACE

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);

    ~SideBar();

    // 设置侧边栏背景色;
    void setBackgroundColor(int r, int g, int b);

public:
    //是否是最大化窗口
    bool m_isMaxWindow;

public slots:

protected:
    // 侧边栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    void on_btn_change_to_chat_clicked();

    void on_btn_change_to_friend_clicked();

private:
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    // 移动窗口的变量;
    bool m_isPressed;
    QPoint m_startMovePos;

    Ui::SideBar *ui;
};

#endif // SIDEBAR_H
