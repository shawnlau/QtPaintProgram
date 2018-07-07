#include "viewarea.h"
#include "mycanvas.h"
#include <QDebug>
#include <array>
ViewArea::ViewArea(QWidget *parent, int mw, int mh) : QWidget(parent)
{
    if(parent != nullptr){
        iWidth = mw;
        iHeight = mh;
        m_imageRectF.setRect(0,0,mw,mh);
        m_focalRectF.setRect(0,0,parentWidget()->width(),parentWidget()->height());
        zIndex = ZOOM1x;
        zoom = zoomLevels[zIndex];
        m_focalRectF.moveCenter(m_imageRectF.center());
        findScreenIntersections();
    }
}

QRect ViewArea::intersectRect()
{
    return m_intersectRectF.toRect();
}

QRect ViewArea::screenRect()
{
    return m_screenRectF.toRect();
}
void  ViewArea::center(){
     m_focalRectF.moveCenter(m_imageRectF.center());
     findScreenIntersections();
}

void ViewArea::putZoom(int index)
{
    zIndex = index;
    zoom = zoomLevels[zIndex];
    setFocalRect();
    findScreenIntersections();
}

QPoint ViewArea::imgMouse(QPoint p)
{
    int x = (int)(m_focalRectF.x() +(qreal)p.x()/zoom +0.5);
    constrainWidth(&x);
    int y = (int)(m_focalRectF.y() +(qreal)p.y()/zoom +0.5);
    constrainHeight(&x);
    return QPoint(x,y);
}

void ViewArea::zoomIn()
{

    zIndex++;
    int levels = sizeof(zoomLevels)/sizeof(zoomLevels[0]);
    if(zIndex>= levels-1  ) zIndex= levels -1;
    zoom = zoomLevels[zIndex];
    setFocalRect();
    findScreenIntersections();
}

void ViewArea::zoomOut()
{
    zIndex--;
    if(zIndex < 0) zIndex = 0;
    zoom = zoomLevels[zIndex];
    setFocalRect();
    findScreenIntersections();
}

void ViewArea::zoomToFit()
{
    zoom = static_cast<qreal>(parentWidget()->width())/iWidth;
    if(iHeight * zoom > static_cast<qreal>(parentWidget()->height()))
         zoom = static_cast<qreal>(parentWidget()->height())/iHeight;
    int levels = sizeof(zoomLevels)/sizeof(zoomLevels[0]);
    for(int i = 0; i < levels-1;i++){
         zIndex = i;
         if(zoomLevels[zIndex+1] > zoom)
              break;
    }
    setFocalRect();
    center();
    findScreenIntersections();

}

void ViewArea::zoom100()
{
    zIndex = ZOOM1x;
    zoom = zoomLevels[zIndex];
    setFocalRect();
    findScreenIntersections();
}

void ViewArea::move(QPoint m, QPoint pm)
{

    QPointF c;
    c.setX(m_focalRectF.center().x() - (m.x()-pm.x())/zoom );
    c.setY(m_focalRectF.center().y() - (m.y()-pm.y())/zoom );
    m_focalRectF.moveCenter(c);
    findScreenIntersections();
}

void ViewArea::changeScreenSize()
{
    setFocalRect();
    findScreenIntersections();
}

bool ViewArea::findScreenIntersections(){
     qreal offX = 0, offY=0;
     if(m_focalRectF.x() < 0) offX = -m_focalRectF.x() * zoom;
     if(m_focalRectF.y() < 0) offY = -m_focalRectF.y() * zoom;
     QRectF temp = m_imageRectF.intersected(m_focalRectF);
     if(temp.isValid()){
        m_intersectRectF.setRect(temp.x(),temp.y(),temp.width(),temp.height());
        m_screenRectF.setRect(offX,offY,m_intersectRectF.width()*zoom,m_intersectRectF.height()*zoom);
        return true;
     }
     else{
        m_intersectRectF.setRect(0,0,0,0);
        m_screenRectF.setRect(0,0,0,0);
        return false;
     }

}

void ViewArea::setFocalRect()
{
    QPointF c = m_focalRectF.center();
    m_focalRectF.setRect(0,0,parentWidget()->width()/zoom,parentWidget()->height()/zoom);
    m_focalRectF.moveCenter(c);
}

void ViewArea::setBrushFocalRec(QSize s)
{
    m_brushFocalRectF.setRect(0,0,s.width()+5,s.height()+5);
}


