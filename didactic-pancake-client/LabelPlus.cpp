#include "LabelPlus.h"

#include <QContextMenuEvent>

LabelPlus::LabelPlus(QWidget *parent) : QLabel(parent),
                                        m_contextMenu(new QMenu()),
                                        m_str("")
{
    setText(m_str);
    initControl();
}

LabelPlus::~LabelPlus()
{
    delete m_contextMenu;
}

QMenu *LabelPlus::getContextMenu()
{
    return m_contextMenu;
}

void LabelPlus::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    return QLabel::mouseReleaseEvent(event);
}

void LabelPlus::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void LabelPlus::initControl()
{
    QString qss_m_contextMenu =
        "QMenu{background-color:rgba(255,255,255,1);}"
        "QMenu{border:1px solid rgb(196,196,196);}"
        "QMenu::item{padding:5px 30px;}"
        //"QMenu::item{color:rgb(0,0,0)};"
        //"QMenu::item{background-color:rgba(255,255,255,1)};"
        //"QMenu::item{font-size:12px;}"
        "QMenu::item:selected{background-color:rgb(226,226,226);}"
        "QMenu::item:selected{color:rgb(0,0,0)};";

    m_contextMenu->setStyleSheet(qss_m_contextMenu);
}
