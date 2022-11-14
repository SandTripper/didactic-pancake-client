#include "PictureViewingWindow.h"
#include "ui_PictureViewingWindow.h"

PictureViewingWindow::PictureViewingWindow(const QString &picturePath, QWidget *parent) : BaseWindow(parent),
                                                                                          ui(new Ui::PictureViewingWindow),
                                                                                          m_picturePath(picturePath)
{
    ui->setupUi(this);
    initThis();
    initTitleBar();
}

PictureViewingWindow::~PictureViewingWindow()
{
    delete ui;
}

void PictureViewingWindow::initThis()
{
    //设置背景颜色
    setBackgroundColor(255, 255, 255);

    QPixmap pix;
    QFile file(m_picturePath);
    if (file.open(QIODevice::ReadOnly) && pix.loadFromData(file.readAll()))
    {
        m_pictureWidth = pix.width();
        m_pictureHeight = pix.height();
        if (m_pictureWidth >= MAX_PICTURE_WIDTH)
        {
            m_pictureHeight = m_pictureHeight / m_pictureWidth * MAX_PICTURE_WIDTH;
            m_pictureWidth = MAX_PICTURE_WIDTH;
        }
        if (m_pictureHeight >= MAX_PICTURE_HEIGHT)
        {
            m_pictureWidth = m_pictureWidth / m_pictureHeight * MAX_PICTURE_HEIGHT;
            m_pictureHeight = MAX_PICTURE_HEIGHT;
        }
        ui->lbl_picture->setFixedSize(m_pictureWidth, m_pictureHeight);
        ui->lbl_picture->setPixmap(pix);
        ui->lbl_picture->setScaledContents(true);
        this->setFixedSize(m_pictureWidth + 8, m_pictureHeight + 8 + 25);
        ui->lbl_picture->move(4, 29);
    }
    else
    {
        this->setFixedSize(500, 420);
        ui->lbl_picture->setText("图片无法展示");
        ui->lbl_picture->setFixedSize(100, 100);
        ui->lbl_picture->move(200, 160);
    }

    file.close();
}

void PictureViewingWindow::initTitleBar()
{

    connect(m_titleBar, &BaseTitleBar::signalButtonCloseClicked, this, &PictureViewingWindow::closed);

    m_titleBar->setBackgroundColor(255, 255, 255);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(25);
}
