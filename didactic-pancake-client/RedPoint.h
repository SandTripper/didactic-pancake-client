#ifndef REDPOINT_H
#define REDPOINT_H

#include <QWidget>
#include <QLabel>

class RedPoint : public QLabel
{
    Q_OBJECT

public:
    /*SHOW99WHENBIGGER表示当数字大于99时显示99
    SHOWDOTWHENBIGGER表示当数字大于99时显示...
    */
    enum PointType
    {
        SHOW99WHENBIGGER,
        SHOWDOTWHENBIGGER
    };

public:
    RedPoint(QWidget *parent = nullptr);
    void setPointType(const PointType &pointtype);

    //设置红点大小
    void setSize(int width, int height);

    //设置内容
    void setNum(int num);

private:
    //红点类型
    PointType m_pointType;
};

#endif // REDPOINT_H
