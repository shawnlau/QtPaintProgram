#ifndef VIEWAREA_H
#define VIEWAREA_H

#include <QObject>
#include <QWidget>
#include <QRectF>
//#include "myrectanglef.h"
class MyCanvas;
class ViewArea : public QWidget
{
    Q_OBJECT
public:
    const static int ZOOM1x = 12;
    explicit ViewArea(QWidget *parent = nullptr,int mw =0, int mh = 0);
    QRect intersectRect();
    QRect screenRect();
    void zoomIn();
    void zoomOut();
    void zoomToFit();
    void zoom100();
    void move(int x, int y, int px, int py);
    void center();
    void putZoom(int index);


    QPoint imgMouse(QPoint p);

signals:

public slots:
    void changeScreenSize();
private:
    QRectF m_imageRectF;
    QRectF m_focalRectF;
    QRectF m_intersectRectF;
    QRectF m_screenRectF;
    int iWidth;
    int iHeight;
    int imouseX;
    int imouseY;
    qreal offsetX,offsetY;
    qreal zoomLevels[23]={0.015625,0.03125,0.0625,0.125,0.16,0.1875,0.25,0.333,0.40,0.50,0.666,0.75,1.0,1.5,2.0,2.5,3.0,3.5,4.0,5.0,6.0,8.0,10.0};
    qreal zoom;
    int zIndex;
    bool findScreenIntersections();
    void setFocalRect();
    inline void constrainWidth(int *n){
        if(*n < 0) n= 0;
        else if(*n > iWidth) *n= iWidth -1;
    }
    inline void constrainHeight(int *n){
        if(*n < 0) n= 0;
        else if(*n > iHeight) *n= iHeight -1;
    }
//    void setFocalRect();
//    void setScreenRects();
};

#endif // VIEWAREA_H
