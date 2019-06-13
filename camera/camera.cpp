#include <QJsonArray>

#include "camera.h"



Camera::Camera(const QString &label, float x, float y) : Marker(label, x, y)
{

}

Camera::Camera(const QString &label, const QPointF &pos) : Marker(label, pos)
{

}

int Camera::type() const
{
    return CAMERA;
}

QJsonObject Camera::toJson() const
{
    QJsonObject root = this->Marker::toJson();

    QJsonArray arrayPixel;
    arrayPixel.append(QJsonValue(pixel.x()));
    arrayPixel.append(QJsonValue(pixel.y()));
    root["pixel"] = arrayPixel;
    root["bgPath"] = QJsonValue(bgPath);

    // list of border markers
    QJsonArray arrayMarkers;
    foreach (const QString &slabel, listMarkers)
    {
        arrayMarkers.append(QJsonValue(slabel));
    }
    root["border"] = arrayMarkers;

    return root;
}

void Camera::addBorder(const QString &label)
{
    listBorders.append(label);
}
