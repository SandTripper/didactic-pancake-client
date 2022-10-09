#include "LabelPlus.h"

LabelPlus::LabelPlus(QWidget *parent) : QLabel(parent), m_str("")
{
    setText(m_str);
}

LabelPlus::~LabelPlus()
{
}

void LabelPlus::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();
}
