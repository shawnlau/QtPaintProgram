#include "myrectanglef.h"

MyRectangleF::MyRectangleF()
{
    zeroRect();
}

MyRectangleF::MyRectangleF(qreal _x, qreal _y, qreal _w, qreal _h, bool center)
{
    if(!center){
        x = _x;
        y=_y;
        x2 = _x + _w -1;
        y2 = _y + _h - 1;
        w = _w;
        h = _h;
        centerX= (x2 - x)/2 + x;
        centerY= (y2 - y)/2 + y;
    }
    else{
        x = y = 0;
        x2 = _w -1;
        y2 = _h-1;
        w = _w;
        h = _h;
        centerX=  x2 / 2;
        centerY=  y2 / 2;
        moveRectC(_x,_y);

    }
}

void MyRectangleF::moveRectC(qreal cx, qreal cy)
{
    x += cx - centerX;
    x2 += cx - centerX;
    y += cy - centerY;
    y2 += cy - centerY;
    centerX = cx;
    centerY = cy;
}

bool MyRectangleF::findIntersection(MyRectangleF *r, MyRectangleF *b)
{
    if(b->x <= x){
        r->x = x;
        if(b->x2 < x){
            r->zeroRect();
            return false;
        }
        if(b->x2 < x2){
            r->x2 = b->x2;
        }
        else
            r->x2 = x2;
    }
    else if(b->x<= x2){
        r->x = b->x;
        if(b->x2 < x2){
            r->x2 = b->x2;
        }
        else
            r->x2 = x2;
    }
    else{
        r->zeroRect();
        return false;
    }
    if(b->y <= y){
         r->y = y;
         if(b->y2 < y){
             r->zeroRect();
             return false;
         }
         else if(b->y2 < y2)
             r->y2 = b->y2;
         else
             r->y2 = y2;
    }
    else if(b->y <= y2){
         r->y = b->y;
         if(b->y2 < y2)
              r->y2 = b->y2;
         else
              r->y2 = y2;
    }
    else{
         r->zeroRect();
         return false;
    }
    r->w = r->x2 -r->x+1;
    r->h = r->y2 - r->y +1;
    r->centerX = (r->w -1)/2 + r->x;
    r->centerY = (r->h -1)/2 + r->y;
    return true;

}

void MyRectangleF::zeroRect()
{
    x=x2=y=y2=h=w=centerX=centerY=0;
}

void MyRectangleF::resizeRect(qreal w, qreal h, int method){
    if(method == C){
        this->w = w;
        this->h = h;
        float cx = centerX;
        float cy = centerY;
        x = 0;
        x2 = w-1;
        y = 0;
        y2 = h -1;
        centerX = (w-1)/2;
        centerY = (h-1)/2;
        moveRectC(cx,cy);
    }
    else if(method == TL){
        x2 = x + w -1;
        y2 = y + h -1;
        this->w = w;
        this->h = h;
        centerX = (x2 - x)/2;
        centerY = (y2-y)/2;
    }
    else if(method == BL){
        //todo
    }
    else if(method == TR){
        //todo
    }
    else if(method == BR){
        //todo
    }

}
void MyRectangleF::resizeRect(qreal n){
    float cx = centerX;
    float cy = centerY;
    w = w *n;
    h = h * n;
    x = y = 0;
    x2 = x + w-1;
    y2 = y + h-1;
    centerX = (w-1)/2;
    centerY = (h-1)/2;
    moveRectC(cx,cy);

}

bool MyRectangleF::isZero()
{
    if(w ==0 || h == 0)
        return true;
    return false;

}
