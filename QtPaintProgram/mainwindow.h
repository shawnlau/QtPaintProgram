#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MyCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void open();
    void quit();
    void fullScreen();
private:
    MyCanvas *m_myCanvas;
    QMenu *m_fileMenu;
    QMenu *m_viewMenu;
    QAction *m_openAct;
    QAction *m_exitAct;
    QAction *m_fullScreenAct;
    QAction *m_toFitAct;
    QAction *m_100Act;
    Qt::WindowState m_state = Qt::WindowNoState;
    Qt::WindowState m_prevState = Qt::WindowNoState;
};

#endif // MAINWINDOW_H

