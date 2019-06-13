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

    // location in image (pixel)
    QJsonArray arrayPixel;
    arrayPixel.append(QJsonValue(pixel.x()));
    arrayPixel.append(QJsonValue(pixel.y()));
    root["pixel"] = arrayPixel;

    // background image
    root["bgPath"] = QJsonValue(bgPath);

    // list of border markers
    QJsonArray arrayMarkers;
    foreach (const QString &slabel, listBorders)
    {
        arrayMarkers.append(QJsonValue(slabel));
    }
    root["borders"] = arrayMarkers;

    return root;
}

void Camera::addBorder(const QString &label)
{
    listBorders.append(label);
}

void Camera::setPixel(float x, float y)
{
    pixel.setX(x);
    pixel.setY(y);
}

void Camera::setImagePath(const QString &path)
{
    bgPath = path;
}
