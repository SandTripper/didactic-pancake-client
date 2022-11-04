#include "AutoWrapLabel.h"
#include <QFontMetrics>
#include <QFontMetricsF>

AutoWrapLabel::AutoWrapLabel(QWidget *parent)
    : QLabel(parent)
{
    m_maxWidth = 0;
}

AutoWrapLabel::AutoWrapLabel(const QString &text, QWidget *parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
    : QLabel(text, parent, f)
{
    setText(text);
}

AutoWrapLabel::~AutoWrapLabel()
{
}

void AutoWrapLabel::setText(const QString &qsText)
{
    m_qsText = qsText;
    InitText();
}

void AutoWrapLabel::setTitleText(const QString &qsText)
{
    m_qsText = qsText;
    InitText();
}

void AutoWrapLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    InitText();
}

void AutoWrapLabel::InitText()
{
    QLabel::setText(CalcText(m_qsText));
}

QString AutoWrapLabel::CalcText(const QString &src)
{
    QString res = "";

    QFontMetricsF fm(this->font());
    int nCount = src.count("\n");
    int nowWidth = 0;
    if (nCount == 0)
    {
        for (int j = 0; j < src.size(); ++j)
        {
            if (nowWidth + fm.width(src.at(j)) > this->width())
            {
                res += "\r\n";
                nowWidth = 0;
            }
            res += src.at(j);
            nowWidth += fm.width(src.at(j));
        }
    }
    else
    {
        for (int i = 0; i < (nCount + 1); i++)
        {
            nowWidth = 0;
            QString value = src.split("\n").at(i);
            if (value == "")
                continue;
            for (int j = 0; j < value.size(); ++j)
            {
                if (nowWidth + fm.width(value.at(j)) > this->width())
                {
                    res += "\r\n";
                    nowWidth = 0;
                }
                res += value.at(j);
                nowWidth += fm.width(value.at(j));
            }
            if (i != nCount)
                res += '\n';
        }
    }

    m_raw = res.count("\n") + 1;
    if (m_raw == 1)
    {
        m_maxWidth = fm.width(res);
    }
    else
    {
        QStringList lists = res.split('\n');
        for (int i = 0; i < lists.size(); ++i)
        {
            m_maxWidth = m_maxWidth > fm.width(lists.at(i)) ? m_maxWidth : fm.width(lists.at(i));
        }
    }
    return res;
}

int AutoWrapLabel::getRaw()
{
    return m_raw;
}

int AutoWrapLabel::getMaxWidth()
{
    return m_maxWidth;
}
