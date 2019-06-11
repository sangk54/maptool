#include "anchor.h"


Marker::Marker(const QString label, float x, float y)
{
    this->label = label;
    this->x = x;
    this->y = y;
}

QString Marker::getLabel() const
{
    return label;
}

void Marker::setLabel(const QString &value)
{
    label = value;
}

float Marker::getX() const
{
    return x;
}

void Marker::setX(float value)
{
    x = value;
}

float Marker::getY() const
{
    return y;
}

void Marker::setY(float value)
{
    y = value;
}
