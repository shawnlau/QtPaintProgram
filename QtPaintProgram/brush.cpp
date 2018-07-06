#include "brush.h"
#include <QPainter>

Brush::Brush(QWidget *parent) : QWidget(parent)
{

}

Brush::Brush(QWidget *parent, int size)
{
    setBrushSize(size);
}

Brush::Brush(QWidget *parent, int size, QImage head)
{

}

void Brush::setBrushSize(int size)
{
    if(size < 1) size = 1;
    m_size = size;
    if(m_brushHead == nullptr){
        if(m_brush != nullptr)
            delete m_brush;
        m_brush = new QImage(size+1,size+1,QImage::Format_ARGB32);
        m_brush->fill(qRgb(255,255,255));
        qreal rad = 0.5 * size;
        qreal center = 0.5 * (size+1);

        QPainter p(m_brush);
        QBrush b(QColor(0,0,0));
        p.setBrush(b);
        p.drawEllipse(QPointF(center,center),rad,rad);
    }
}
