#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene= new QGraphicsScene();
    ui->graphicsView_panel->setScene(scene);

    BdfFont fontNormal;
    BdfFont f0;
    BdfFont f3;
    BdfFont f5;
    BdfFont f8;
    /*
    if (!fontNormal.load(":/fonts/fonty/ZIS_12_bold.bdf"))
    {
        qWarning() << "Failed to load ZIS_12_bold.bdf";
    }*/

    if (!fontNormal.load("fonts/f5.bdf"))
    {
        qWarning() << "Failed to load f5.bdf";
    }

    int layoutHeight=19;
    int layoutWidth=144;

    bdfDraw.textColor="#ff9100";
    bdfDraw.bdfMarginX = 0;
    bdfDraw.bdfMarginY = 0;

    int scaleFactor=4;

    applyPanelSize(layoutWidth, layoutHeight, scaleFactor);

    bdfDraw.clearScene(scene);
    scene->setSceneRect(0,0,layoutWidth,layoutHeight);

    scene->setBackgroundBrush(Qt::black);

    QPen qpen=QPen(Qt::blue);
    //scene->addLine(QLineF(0,10,0,20),qpen);

    bdfDraw.drawTextLeft(scene,0,2,fontNormal,"Lorem Ipsum");
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}


void MainWindow::applyPanelSize(int layoutWidth, int layoutHeight, int factor)
{
    QGraphicsView *view = ui->graphicsView_panel;

    scene->setSceneRect(0, 0, layoutWidth, layoutHeight);

    // No frame, so widget size == viewport size
    view->setFrameShape(QFrame::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Crisp pixels
    view->setRenderHint(QPainter::Antialiasing, false);
    view->setRenderHint(QPainter::SmoothPixmapTransform, false);

    // Absolute factor (scale() is cumulative, so reset first)
    view->resetTransform();
    view->scale(factor, factor);

    view->setFixedSize(layoutWidth * factor, layoutHeight * factor);
}


void MainWindow::setZoom(int factor)
{
    ui->graphicsView_panel->resetTransform();
    ui->graphicsView_panel->scale(factor, factor);
}
