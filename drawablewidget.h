#ifndef DRAWABLEWIDGET_H
#define DRAWABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>

#include "camera/camera.h"

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

    void loadListAnchor();
    void saveListAnchor();


protected:
    void paintEvent(QPaintEvent *evt);
    void mouseMoveEvent(QMouseEvent* evt);
    void mouseReleaseEvent(QMouseEvent *evt);

    void showContextMenu(const QPoint &pos);


protected slots:
    void addAnchor();
signals:
    void currentMousePosition(QPoint pos);
private:
    Ui::DrawableWidget *ui;
    QPixmap pixBg, pixMarker;


    QVector<Marker> listAnchors;
};

#endif // DRAWABLEWIDGET_H
