#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StatusBar;
}
QT_END_NAMESPACE

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

    ~StatusBar();

    // 设置状态栏背景色;
    void setBackgroundColor(int r, int g, int b);

public:
    //是否是最大化窗口
    bool m_isMaxWindow;

public slots:

protected:
    // 状态栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

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

    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
