#ifndef DRAWABLEWIDGET_H
#define DRAWABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>
#include <QGraphicsScene>

#include "camera/camera.h"
#include "camera/markermanager.h"

namespace Ui {
class DrawableWidget;
}

class DrawableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawableWidget(QWidget *parent = 0);
    ~DrawableWidget();
    QSize sizeHint() const;

    void initScene();

protected:
//    void paintEvent(QPaintEvent *evt);
    void mouseMoveEvent(QMouseEvent* evt);
    void mouseReleaseEvent(QMouseEvent *evt);

    void showContextMenu(const QPoint &pos);


protected slots:
    void addMarker();
    void addCamera();
signals:
    void currentMousePosition(QPoint pos);
private:
    Ui::DrawableWidget *ui;
    QPixmap pixBg, pixMarker;


    MarkerManager *manager = NULL;

    QGraphicsScene *scene = NULL;
};

#endif // DRAWABLEWIDGET_H
