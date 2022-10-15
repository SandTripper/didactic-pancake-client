#ifndef LABELPLUS_H
#define LABELPLUS_H

#include <QLabel>
#include <QWidget>

class LabelPlus : public QLabel
{
    Q_OBJECT
public:
    LabelPlus(QWidget *parent = 0);

    ~LabelPlus();

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *);

private:
    //显示的文本
    QString m_str;
};

#endif // LABELPLUS_H
