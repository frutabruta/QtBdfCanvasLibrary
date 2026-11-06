#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "../../bdfdraw.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    BdfDraw bdfDraw;

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    void setZoom(int factor);
    void applyPanelSize(int layoutWidth, int layoutHeight, int factor);
};
#endif // MAINWINDOW_H
