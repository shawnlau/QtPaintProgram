#include "mainwindow.h"
#include <QtWidgets>
#include "mycanvas.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_myCanvas = new MyCanvas(this);
    setCentralWidget(m_myCanvas);
    m_myCanvas->setFocusPolicy(Qt::StrongFocus);
    m_myCanvas->setFocus();
    m_openAct = new QAction(tr("&Open..."), this);
    m_openAct->setShortcuts(QKeySequence::Open);
    m_exitAct = new QAction(tr("&Exit"),this);
    m_fullScreenAct = new QAction(tr("&Full Screen"),this);
    m_fullScreenAct->setShortcut(QKeySequence::FullScreen);
    m_toFitAct = new QAction(tr("&Zoom to Fit"));
    m_100Act = new QAction(tr("Zoom 100%"),this);
    connect(m_openAct,SIGNAL(triggered(bool)),this,SLOT(open()));
    connect(m_exitAct,SIGNAL(triggered(bool)),this,SLOT(quit()));
    connect(m_fullScreenAct,SIGNAL(triggered(bool)),this,SLOT(fullScreen()));
    connect(m_toFitAct,SIGNAL(triggered(bool)),m_myCanvas,SLOT(zoomToFit()));
    connect(m_100Act,SIGNAL(triggered(bool)),m_myCanvas,SLOT(zoom100()));
    m_fileMenu = new QMenu(tr("&File"), this);
    m_viewMenu = new QMenu(tr("&View"),this);
    m_fileMenu->addAction(m_openAct);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAct);
    m_viewMenu->addAction(m_fullScreenAct);
    m_viewMenu->addAction(m_toFitAct);
    m_viewMenu->addAction(m_100Act);
    menuBar()->addMenu(m_fileMenu);
    menuBar()->addMenu(m_viewMenu);

    resize(400,400);

}
void MainWindow::open(){

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()){
        m_myCanvas->openImage(fileName);
    }
}
void MainWindow::quit(){

    QCoreApplication::quit();
}

void MainWindow::fullScreen()
{
    if(windowState()==Qt::WindowFullScreen){
        m_state = m_prevState;
        setWindowState(m_state);
        m_fullScreenAct->setText(tr("&Full Screen"));
    }
    else if(windowState()==Qt::WindowMaximized){
        m_prevState = Qt::WindowMaximized;
        setWindowState(Qt::WindowFullScreen);
        m_fullScreenAct->setText(tr("&Windowed view"));
    }
    else if(windowState() ==Qt::WindowNoState){
        m_prevState = Qt::WindowNoState;
        setWindowState(Qt::WindowFullScreen);
        m_fullScreenAct->setText(tr("&Windowed view"));
    }

}


