#ifndef CAMERA_H
#define CAMERA_H

#include <QPointF>
#include <QVector>

#include "marker.h"

class Camera : public Marker
{
public:
    Camera(const QString &label = "", float x = 0, float y = 0);
    Camera(const QString &label, const QPointF &pos);

    int type() const;
    QJsonObject toJson() const;
    void addBorder(const QString &label);

private:
    // pixel cordinate
    QPointF pixel;
    QString bgPath;

    // list of border markers
    QVector<QString> listBorders;
};

#endif // CAMERA_H
