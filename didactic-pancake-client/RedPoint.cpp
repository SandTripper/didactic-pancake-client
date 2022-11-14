#include "RedPoint.h"

#include <QPainter>
#include <QPixmap>
#include <QFontMetricsF>
#include <QDebug>

RedPoint::RedPoint(QWidget *parent) : QLabel(parent),
                                      m_pointType(SHOW99WHENBIGGER)
{
    //本控件不响应鼠标事件
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    //自动压缩图片至本控件大小
    setScaledContents(true);

    setFixedSize(16, 16);
}

void RedPoint::setPointType(const RedPoint::PointType &pointtype)
{
    m_pointType = pointtype;
}

void RedPoint::setSize(int width, int height)
{
    setFixedSize(width, height);
}

void RedPoint::setNum(int num)
{

    if (num == 0)
    {
        this->hide();
        return;
    }
    this->show();

    QString text;

    if (num > 99)
    {
        if (m_pointType == SHOW99WHENBIGGER)
            text = QString::number(99);
        else
            text = "...";
    }
    else
    {
        text = QString::number(num);
    }
    if (num < 10)
    {
        if (this->width() != 16)
        {
            this->setFixedWidth(16);
            int lastx = this->pos().x();
            this->move(lastx + 3, this->pos().y());
        }
        QPixmap pix(16, 16);
        pix.fill(QColor(255, 255, 255, 0));
        QPainter Painter(&pix);
        /* 尽可能消除锯齿边缘 */
        Painter.setRenderHint(QPainter::Antialiasing);
        /* 尽可能消除文本锯齿边缘 */
        Painter.setRenderHint(QPainter::TextAntialiasing);
        //    /* 启用线性插值算法以此来平滑图片 */
        //    Painter.setRenderHint(QPainter::SmoothPixmapTransform);
        Painter.setPen(QColor(255, 255, 255, 0));
        Painter.setBrush(QColor(250, 81, 81));
        Painter.drawEllipse(0, 0, 16, 16);

        QFont font("Microsoft YaHei", 8);
        QFontMetricsF fm(font);
        Painter.setPen(QColor(255, 255, 255));
        Painter.setFont(font);
        Painter.drawText((16 - fm.width(text)) / 2, 12, text);
        setPixmap(pix);
    }
    else
    {
        if (this->width() != 22)
        {
            this->setFixedWidth(22);
            int lastx = this->pos().x();
            this->move(lastx - 3, this->pos().y());
        }
        QPixmap pix(22, 16);
        pix.fill(QColor(255, 255, 255, 0));
        QPainter Painter(&pix);
        /* 尽可能消除锯齿边缘 */
        Painter.setRenderHint(QPainter::Antialiasing);
        /* 尽可能消除文本锯齿边缘 */
        Painter.setRenderHint(QPainter::TextAntialiasing);
        //    /* 启用线性插值算法以此来平滑图片 */
        //    Painter.setRenderHint(QPainter::SmoothPixmapTransform);
        Painter.setPen(QColor(255, 255, 255, 0));
        Painter.setBrush(QColor(250, 81, 81));
        Painter.drawRect(8, 0, 6, 16);
        Painter.drawEllipse(0, 0, 16, 16);
        Painter.drawEllipse(6, 0, 16, 16);

        QFont font("Microsoft YaHei", 8);
        QFontMetricsF fm(font);
        Painter.setPen(QColor(255, 255, 255));
        Painter.setFont(font);
        Painter.drawText((22 - fm.width(text)) / 2, 12, text);
        setPixmap(pix);
    }
}
