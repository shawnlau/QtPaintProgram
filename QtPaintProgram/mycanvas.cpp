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
    connect(this,SIGNAL(resize()),m_view,SLOT(changeScreenSize()));
}
void MyCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect iRect = m_view->intersectRect();
    if(iRect.isValid()){
        QRect sRect = m_view->screenRect();
        QImage *temp = new QImage(m_mainImage->copy(iRect));
        if(mode == DRAG)
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
                mode = DRAG;
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
            mode = prevMode;
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
        mouseX=prevX = event->pos().x();
        mouseY=prevY = event->pos().y();
        action[mode](this);

    }
}

void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{

    mouseX = event->pos().x();
    mouseY = event->pos().y();
    if( mouseX  >= 0 && mouseX < parentWidget()->width() && mouseY >= 0 && mouseY < parentWidget()->height() ){
        action[mode](this);

    }
    prevX =mouseX;
    prevY = mouseY;
}

void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    prevX = prevY = -1;
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
    qDebug()<<"Draw";
}
void MyCanvas::dragScreen(){
    m_view->move(mouseX,mouseY,prevX,prevY);
    update();

}


