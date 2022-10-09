#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include "BaseTitleBar.h"

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    // 设置背景色;
    void setBackgroundColor(int r, int g, int b);

private:
    void initTitleBar();

private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

protected:
    void paintEvent(QPaintEvent *event);

protected:
    BaseTitleBar *m_titleBar;

private:
    // 背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;
};

#endif // BASEWINDOW_H
