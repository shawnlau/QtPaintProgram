#include <QPainter>
#include <QSize>
#include <QDebug>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QApplication>
#include <QRectF>
#include "viewarea.h"
#include "mycanvas.h"
#include "brush.h"
MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent)
{
    m_mainImage = new QImage(800,800,QImage::Format_ARGB32);
    m_mainImage->fill(qRgb(255,255,255));
    m_view = new ViewArea(parent,800,800);
    m_brush = new Brush(parent,20);
    m_floatArrayR = new float[m_mainImage->width()*m_mainImage->height()];
    m_floatArrayG = new float[m_mainImage->width()*m_mainImage->height()];
    m_floatArrayB = new float[m_mainImage->width()*m_mainImage->height()];
    loadFloatArrays();
    connect(this,SIGNAL(resize()),m_view,SLOT(changeScreenSize()));
    setMouseTracking(true);

}
void MyCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect iRect = m_view->intersectRect();
    if(iRect.isValid()){
        QRect sRect = m_view->screenRect();
        QImage *temp = new QImage(m_mainImage->copy(iRect));
        if(m_mode == DRAG)
            m_displayImage = new QImage(temp->scaled(sRect.size(),Qt::IgnoreAspectRatio,Qt::FastTransformation));
        else
            m_displayImage = new QImage(temp->scaled(sRect.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        painter.drawImage(sRect.x(),sRect.y(),*m_displayImage);
        delete temp;
        delete m_displayImage;
    }


}
void MyCanvas::keyPressEvent(QKeyEvent *event)
{
    if(!m_keyHandled){
        switch(event->key()){
            case Qt::Key_Plus:
                m_view->zoomIn();
                update();
                break;
            case Qt::Key_Minus:
                m_view->zoomOut();
                update();
                break;
            case Qt::Key_Space:
                m_mode = DRAG;
                QApplication::setOverrideCursor(Qt::OpenHandCursor);
                m_keyHandled = true;
                break;
        }

    }

}

void MyCanvas::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Space:
            m_mode = m_prevMode;
            QApplication::setOverrideCursor(m_previousCursor);
            m_keyHandled = false;

    }
}
void MyCanvas::resizeEvent(QResizeEvent *event)
{
    emit resize();
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton){
        m_prevMouse = m_mouse = event->pos();
        m_prevImouse = m_iMouse = m_view->imgMouse(event->pos());
        m_action[m_mode](this);

    }
}

void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if(posInWindow(event->pos())){

            m_mouse = event->pos();
            m_iMouse = m_view->imgMouse(event->pos());
            if(event->buttons()== Qt::LeftButton){
                m_action[m_mode](this);
                m_prevMouse = m_mouse;
                m_prevImouse = m_iMouse;
            }

    }
}
bool MyCanvas::posInWindow(QPoint p)
{   int x,y;
    if((x = p.x()) >= 0 && x < parentWidget()->width() && (y = p.y())>= 0 && y < parentWidget()->height() )
        return true;
    return false;
}

void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{

}
bool MyCanvas::openImage(const QString &fileName){
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    delete m_mainImage;
    m_mainImage = new QImage(loadedImage);
    delete m_view;
    m_view = new ViewArea(parentWidget(),m_mainImage->width(),m_mainImage->height());
    connect(this,SIGNAL(resize()),m_view,SLOT(changeScreenSize()));
    update();
    return true;

}
QSize MyCanvas::mainImageSize(){
    return m_mainImage->size();
}
QSize MyCanvas::windowSize(){
    return parentWidget()->size();
}

void MyCanvas::zoomToFit()
{
    m_view->zoomToFit();
    update();
}

void MyCanvas::zoom100()
{
    m_view->zoom100();
    update();
}



void MyCanvas::draw()
{
//    qDebug()<<"Draw";
//    float spacing = m_brush->m_spacing * m_brush->m_size;
//    if(spacing < 0.5)
//        spacing = 0.5;



}

void MyCanvas::loadFloatArrays()
{
    int numPix = m_mainImage->width() * m_mainImage->height();
    uchar *b = m_mainImage->bits();
    for(int i = 0; i < numPix;i++){
        m_floatArrayB[i]=*b++;
        m_floatArrayG[i]=*b++;
        m_floatArrayR[i]=*b++;
        b++;
    }
}
void MyCanvas::dragScreen(){
    m_view->move(m_mouse,m_prevMouse);
    update();

}


