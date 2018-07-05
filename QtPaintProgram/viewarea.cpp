#include "viewarea.h"
#include "mycanvas.h"
#include <QDebug>
#include <array>
#include "myrectanglef.h"
ViewArea::ViewArea(QWidget *parent, int mw, int mh) : QWidget(parent)
{
    if(parent != nullptr){
        iWidth = mw;
        iHeight = mh;
        m_imageRectF.resizeRect(mw,mh,MyRectangleF::TL);
        m_focalRectF.resizeRect(parentWidget()->width(),parentWidget()->height(),MyRectangleF::TL);
        zIndex = ZOOM1x;
        zoom = zoomLevels[zIndex];
        m_focalRectF.moveRectC(m_imageRectF.centerX,m_imageRectF.centerY);
        findScreenIntersections();
    }
}

MyRectangleF ViewArea::intersectRect()
{
    return m_intersectRectF;
}

MyRectangleF ViewArea::screenRect()
{
    return m_screenRectF;
}
void  ViewArea::center(){
     m_focalRectF.moveRectC(m_imageRectF.centerX,m_imageRectF.centerY);
     findScreenIntersections();
}

void ViewArea::putZoom(int index)
{
    zIndex = index;
    zoom = zoomLevels[zIndex];
    setFocalRect();
    findScreenIntersections();
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

void ViewArea::move(int x, int y, int px, int py)
{
    qreal cx = m_focalRectF.centerX - (x - px)/zoom;
    qreal cy = m_focalRectF.centerY - (y - py)/zoom;
    m_focalRectF.moveRectC(cx,cy);
    findScreenIntersections();
}

void ViewArea::changeScreenSize()
{
    setFocalRect();
    findScreenIntersections();
}

bool ViewArea::findScreenIntersections(){
     qreal offX = 0, offY=0;
     if(m_focalRectF.x < 0) offX = -m_focalRectF.x * zoom;
     if(m_focalRectF.y < 0) offY = -m_focalRectF.y * zoom;
     if(m_imageRectF.findIntersection(&m_intersectRectF,&m_focalRectF)){
          m_screenRectF.x = offX;
          m_screenRectF.y = offY;
          m_screenRectF.w =m_intersectRectF.w * zoom;
          m_screenRectF.h = m_intersectRectF.h * zoom;
          m_screenRectF.x2 = m_screenRectF.x+m_screenRectF.w-1;
          m_screenRectF.y2 = m_screenRectF.y+m_screenRectF.h-1;
          m_screenRectF.centerX = m_screenRectF.x + (m_screenRectF.w-1)/2;
          m_screenRectF.centerY = m_screenRectF.y + (m_screenRectF.h-1)/2;
          return true;
     }
     else{
          m_intersectRectF.zeroRect();
          m_screenRectF.zeroRect();
          return false;
     }

}

void ViewArea::setFocalRect()
{
    qreal cx = m_focalRectF.centerX;
    qreal cy = m_focalRectF.centerY;
    m_focalRectF.x = m_focalRectF.y = 0;
    m_focalRectF.w = parentWidget()->width()/zoom;
    m_focalRectF.h = parentWidget()->height()/zoom;
    m_focalRectF.x2 = m_focalRectF.w-1;
    m_focalRectF.y2 = m_focalRectF.h-1;
    m_focalRectF.centerX = m_focalRectF.x2/2;
    m_focalRectF.centerY = m_focalRectF.y2/2;
    m_focalRectF.moveRectC(cx,cy);
}

