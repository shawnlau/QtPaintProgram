#include "mycanvas.h"
#include <QPainter>
#include <QSize>
#include <QDebug>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QApplication>
#include "myrectanglef.h"
#include "viewarea.h"
MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent)
{
    m_mainImage = new QImage(800,800,QImage::Format_ARGB32);
    m_mainImage->fill(qRgb(255,255,255));
    m_view = new ViewArea(parent,800,800);
    connect(this,SIGNAL(resize()),m_view,SLOT(changeScreenSize()));
}
void MyCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    MyRectangleF iRect = m_view->intersectRect();
    if(!iRect.isZero()){
        MyRectangleF sRect = m_view->screenRect();
        QImage *temp = new QImage(m_mainImage->copy((int)iRect.x,(int)iRect.y,(int)iRect.w,(int)iRect.h));
        if(mode == DRAG)
            m_displayImage = new QImage(temp->scaled((int)sRect.w,(int)sRect.h,Qt::IgnoreAspectRatio,Qt::FastTransformation));
        else
            m_displayImage = new QImage(temp->scaled((int)sRect.w,(int)sRect.h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        painter.drawImage((int)sRect.x,(int)sRect.y,*m_displayImage);
    }
    delete m_displayImage;
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
            case Qt::Key_F:
                if(!static_cast<QWidget *>(parent())->isFullScreen())
                    static_cast<QWidget *>(parent())->showFullScreen();
                else
                    static_cast<QWidget *>(parent())->showNormal();
                break;
            case Qt::Key_B:
                QPaintEvent *event = nullptr;
                paintEvent(event);
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
}

void MyCanvas::draw()
{
    qDebug()<<"Draw";
}
void MyCanvas::dragScreen(){
    m_view->move(mouseX,mouseY,prevX,prevY);
    update();

}


