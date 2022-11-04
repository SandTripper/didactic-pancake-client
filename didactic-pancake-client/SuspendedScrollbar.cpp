#include "SuspendedScrollbar.h"
#include <QScrollBar>
#include <QFile>

SuspendedScrollBar::SuspendedScrollBar(Qt::Orientation t, QWidget *parent) : QScrollBar(parent)
{

    this->setOrientation(t);
    QString style_file = ":/resource/SuspendedScrollbar/scrollbar.qss";
    QFile styleFile(style_file); //路径名
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style(styleFile.readAll());
        this->setStyleSheet(style);
    }

    this->setRange(0, 0);
    this->hide();
}

void SuspendedScrollBar::slt_rangeChanged(int min, int max)
{
    this->setMinimum(min);
    this->setRange(0, max);
    this->setPageStep(0.75 * (this->height() + max));
    if (max <= 0)
        this->hide();
}

void SuspendedScrollBar::slt_valueChange_scrollBar(int value)
{
    this->setValue(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

SuspendedScrollBar_ListWidget::SuspendedScrollBar_ListWidget(QWidget *parent)
    : QListWidget(parent)
{
    this->setVerticalScrollMode(ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical, this);
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), m_pVertScrollBar, SLOT(slt_valueChange_scrollBar(int)));
    connect(m_pVertScrollBar, SIGNAL(valueChanged(int)), this, SLOT(slt_valueChange_widget(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), m_pVertScrollBar, SLOT(slt_rangeChanged(int, int)));
}

void SuspendedScrollBar_ListWidget::slt_valueChange_widget(int value)
{
    this->verticalScrollBar()->setValue(value);
}

void SuspendedScrollBar_ListWidget::showScrollBar()
{
    if (m_pVertScrollBar->maximum() > 0)
        m_pVertScrollBar->show();
}

void SuspendedScrollBar_ListWidget::resizeEvent(QResizeEvent *e)
{
    int iX = this->width() - 8;
    m_pVertScrollBar->setGeometry(iX, 1, 8, this->height() - 2);
    return QListWidget::resizeEvent(e);
}

void SuspendedScrollBar_ListWidget::enterEvent(QEvent *e)
{
    if (m_pVertScrollBar->maximum() > 0)
        m_pVertScrollBar->show();
    return QListWidget::enterEvent(e);
}
void SuspendedScrollBar_ListWidget::leaveEvent(QEvent *e)
{
    m_pVertScrollBar->hide();
    return QListWidget::leaveEvent(e);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
SuspendedScrollBar_Area::SuspendedScrollBar_Area(QWidget *parent)
    : QScrollArea(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical, this);
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), m_pVertScrollBar, SLOT(slt_valueChange_scrollBar(int)));
    connect(m_pVertScrollBar, SIGNAL(valueChanged(int)), this, SLOT(slt_valueChange_widget(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), m_pVertScrollBar, SLOT(slt_rangeChanged(int, int)));
}

void SuspendedScrollBar_Area::slt_valueChange_widget(int value)
{
    this->verticalScrollBar()->setValue(value);
}

void SuspendedScrollBar_Area::resizeEvent(QResizeEvent *e)
{
    int iX = this->width() - 8;
    m_pVertScrollBar->setGeometry(iX, 1, 8, this->height() - 2);
    return QWidget::resizeEvent(e);
}

void SuspendedScrollBar_Area::enterEvent(QEvent *e)
{
    if (m_pVertScrollBar->maximum() > 0)
        m_pVertScrollBar->show();
    return QWidget::enterEvent(e);
}
void SuspendedScrollBar_Area::leaveEvent(QEvent *e)
{
    m_pVertScrollBar->hide();
    return QWidget::leaveEvent(e);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

SuspendedScrollBar_TextEdit::SuspendedScrollBar_TextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical, this);
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), m_pVertScrollBar, SLOT(slt_valueChange_scrollBar(int)));
    connect(m_pVertScrollBar, SIGNAL(valueChanged(int)), this, SLOT(slt_valueChange_widget(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), m_pVertScrollBar, SLOT(slt_rangeChanged(int, int)));
}

void SuspendedScrollBar_TextEdit::slt_valueChange_widget(int value)
{
    this->verticalScrollBar()->setValue(value);
}

void SuspendedScrollBar_TextEdit::resizeEvent(QResizeEvent *e)
{
    int iX = this->width() - 8;
    m_pVertScrollBar->setGeometry(iX, 1, 8, this->height() - 2);
    return QTextEdit::resizeEvent(e);
}

void SuspendedScrollBar_TextEdit::paintEvent(QPaintEvent *e)
{
    if (document()->lineCount() > 1)
    {
        m_pVertScrollBar->show();
    }
    QTextEdit::paintEvent(e);
}
