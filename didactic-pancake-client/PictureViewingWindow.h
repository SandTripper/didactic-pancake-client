#ifndef PICTUREVIEWINGWINDOW_H
#define PICTUREVIEWINGWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QEvent>
#include <QObject>

#include "TcpConnect.h"
#include "BaseWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class PictureViewingWindow;
}
QT_END_NAMESPACE

class PictureViewingWindow : public BaseWindow
{
    Q_OBJECT

public:
    //展示界面图片的最大宽度
    static const int MAX_PICTURE_WIDTH = 900;
    //展示界面图片的最大高度
    static const int MAX_PICTURE_HEIGHT = 900;

    explicit PictureViewingWindow(const QString &picturePath, QWidget *parent = nullptr);

    ~PictureViewingWindow();

signals:
    //关闭信号
    void closed();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();

    Ui::PictureViewingWindow *ui;

    int m_pictureWidth;

    int m_pictureHeight;

    QString m_picturePath;
};

#endif // PICTUREVIEWINGWINDOW_H
