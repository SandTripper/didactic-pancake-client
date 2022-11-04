#ifndef SUSPENDEDSCROLLBAR_H
#define SUSPENDEDSCROLLBAR_H

#include <QWidget>
#include <QScrollBar>
#include <QListWidget>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QTextEdit>

//悬浮滚动条-例子说明
//鼠标移动到控件上时显示滚动条，鼠标离开控件则隐藏滚动条
//目前只实现垂直滚动条，代码简单
//需要水平滚动条的看懂例子后可自行添加

//继承QScrollBar作为组件，添加到你需要添加的控件当中
class SuspendedScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit SuspendedScrollBar(Qt::Orientation t, QWidget *parent = 0);
    ~SuspendedScrollBar() {}
public slots:
    void slt_valueChange_scrollBar(int);
    void slt_rangeChanged(int min, int max);
};

// QListWidget 悬浮滚动条基类
class SuspendedScrollBar_ListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SuspendedScrollBar_ListWidget(QWidget *parent = 0);
    ~SuspendedScrollBar_ListWidget() {}

private:
    SuspendedScrollBar *m_pVertScrollBar; //悬浮滚动条

public slots:
    void slt_valueChange_widget(int);

protected:
    //显示滚动条
    void showScrollBar();
    void resizeEvent(QResizeEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

// QScrollArea 悬浮滚动条基类
class SuspendedScrollBar_Area : public QScrollArea
{
    Q_OBJECT
public:
    explicit SuspendedScrollBar_Area(QWidget *parent = 0);
    ~SuspendedScrollBar_Area() {}

private:
    SuspendedScrollBar *m_pVertScrollBar; //悬浮滚动条
public slots:
    void slt_valueChange_widget(int);

protected:
    void resizeEvent(QResizeEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

// QTextEdit 悬浮滚动条基类
class SuspendedScrollBar_TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit SuspendedScrollBar_TextEdit(QWidget *parent = 0);
    ~SuspendedScrollBar_TextEdit() {}

public slots:
    void slt_valueChange_widget(int);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    void paintEvent(QPaintEvent *e);

private:
    SuspendedScrollBar *m_pVertScrollBar; //悬浮滚动条
};

#endif // SUSPENDEDSCROLLBAR_H
