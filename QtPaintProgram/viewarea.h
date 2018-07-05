#ifndef VIEWAREA_H
#define VIEWAREA_H

#include <QObject>
#include <QWidget>
#include "myrectanglef.h"
class MyCanvas;
class ViewArea : public QWidget
{
    Q_OBJECT
public:
    const static int ZOOM1x = 12;
    explicit ViewArea(QWidget *parent = nullptr,int mw =0, int mh = 0);
    MyRectangleF intersectRect();
    MyRectangleF screenRect();
    void zoomIn();
    void zoomOut();
    void zoomToFit();
    void move(int x, int y, int px, int py);
    void center();
    void putZoom(int index);

signals:

public slots:
    void changeScreenSize();
private:
    MyRectangleF m_imageRectF;
    MyRectangleF m_focalRectF;
    MyRectangleF m_intersectRectF;
    MyRectangleF m_screenRectF;
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
//    void setFocalRect();
//    void setScreenRects();
};

#endif // VIEWAREA_H