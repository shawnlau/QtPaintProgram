#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QImage>
#include <functional>
class ViewArea;
class MyCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit MyCanvas(QWidget *parent = nullptr);
    bool openImage(const QString &fileName);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    QSize mainImageSize();
    QSize windowSize();

signals:
    void resize();
public slots:
    void zoomToFit();
private:
    static const int DRAG = 0,DRAW = 1;
    ViewArea *m_view;
//    QWidget *p;
    QImage *m_mainImage;
    QImage *m_displayImage;
    Qt::CursorShape m_cursor = Qt::ArrowCursor;
    Qt::CursorShape m_previousCursor = m_cursor;
    bool m_keyHandled = false;
    int prevX = -1,prevY = -1;
    int mouseX,mouseY;
    void dragScreen();
    void draw();
    std::function<void(MyCanvas*) > action[2]= {&MyCanvas::dragScreen,&MyCanvas::draw};
    int mode = DRAW;
    int prevMode = DRAW;
};
#endif // MYCANVAS_H
