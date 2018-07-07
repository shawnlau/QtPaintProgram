#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QImage>
#include <functional>
#include <QPoint>
class ViewArea;
class Brush;

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
    void zoom100();
private:
    static const int DRAG = 0,DRAW = 1;
    ViewArea *m_view;
    Brush *m_brush;
    QImage *m_mainImage;
    QImage *m_displayImage;
    float *m_floatArrayR;
    float *m_floatArrayG;
    float *m_floatArrayB;
    Qt::CursorShape m_cursor = Qt::ArrowCursor;
    Qt::CursorShape m_previousCursor = m_cursor;
    bool m_keyHandled = false;
    QPoint m_prevMouse,m_mouse;
    QPoint m_prevImouse,m_iMouse;
    float m_leftOverDistance;
    bool posInWindow(QPoint p);
    void dragScreen();
    void draw();
    void loadFloatArrays();
    std::function<void(MyCanvas*) > m_action[2]= {&MyCanvas::dragScreen,&MyCanvas::draw};
    int m_mode = DRAW;
    int m_prevMode = DRAW;
};
#endif // MYCANVAS_H
