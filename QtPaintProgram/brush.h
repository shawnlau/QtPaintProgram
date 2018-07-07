#ifndef BRUSH_H
#define BRUSH_H

#include <QWidget>

class Brush : public QWidget
{
    Q_OBJECT
public:
    explicit Brush(QWidget *parent = nullptr);
    Brush(QWidget *parent, int size);
    Brush(QWidget *parent, int size, QImage head);
    friend class MyCanvas;

signals:

public slots:
private:
    QImage *m_brush = nullptr;
    QImage *m_brushHead = nullptr;
    int m_size;
    float m_spacing;
    float m_trans = 0.5;
    int m_R = 0;
    int m_G = 0;
    int m_B = 0;
    void setBrushSize(int size);
};

#endif // BRUSH_H
