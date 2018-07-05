#ifndef MYRECTANGLEF_H
#define MYRECTANGLEF_H

#include <QObject>

class MyRectangleF
{
public:
    const static int TL = 0,BL = 1,TR=2,BR=3,C = 4;
    qreal x,y,x2,y2,w,h,centerX,centerY;
    MyRectangleF();
    MyRectangleF(qreal _x, qreal _y, qreal _w, qreal _h, bool center);
    void moveRectC(qreal cx, qreal cy);
    bool findIntersection(MyRectangleF *r, MyRectangleF *b);
    void zeroRect();
    void resizeRect(qreal w, qreal h, int method);
    void resizeRect(qreal n);
    bool isZero();

signals:

public slots:

};

#endif // MYRECTANGLEF_H
