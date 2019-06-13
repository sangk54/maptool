#include <QJsonArray>
#include <QJsonValue>

#include "marker.h"

Marker::Marker(const QString &label, float x, float y)
{
    this->pos = QPointF(x, y);
    this->label = label;
}

Marker::Marker(const QString &label, const QPointF &p)
{
    this->pos = p;
    this->label = label;
}

int Marker::type() const
{
    return ANCHOR;
}

QJsonObject Marker::toJson() const
{
    QJsonObject root;

    QJsonArray array;
    array.append(QJsonValue(label));
    array.append(QJsonValue(pos.x()));
    array.append(QJsonValue(pos.y()));
    root["pos"] = array;

    QJsonArray refArray;
    refArray.append(QJsonValue(refLabel1));
    refArray.append(QJsonValue(refDistance1));
    refArray.append(QJsonValue(refLabel2));
    refArray.append(QJsonValue(refDistance2));
    root["ref"] = refArray;

    return root;
}

void Marker::addBorder(const QString &label)
{
    Q_UNUSED(label)
}

void Marker::setReferenceMarker(const QString &theLabel, float distance, int oneOrTwo)
{
    if (oneOrTwo == 1)
    {
        this->label = theLabel;
        refDistance1 = distance;
    }
    else
    {
        this->label = theLabel;
        refDistance2 = distance;
    }
}

QPointF Marker::getPos() const
{
    return pos;
}

void Marker::setPos(const QPointF &value)
{
    pos = value;
}


float Marker::getRefDistance1() const
{
    return refDistance1;
}

void Marker::setRefDistance1(float value)
{
    refDistance1 = value;
}

float Marker::getRefDistance2() const
{
    return refDistance2;
}

void Marker::setRefDistance2(float value)
{
    refDistance2 = value;
}

QString Marker::getLabel() const
{
    return label;
}

void Marker::setLabel(const QString &value)
{
    label = value;
}

QString Marker::getRefLabel1() const
{
    return refLabel1;
}

void Marker::setRefLabel1(const QString &value)
{
    refLabel1 = value;
}

QString Marker::getRefLabel2() const
{
    return refLabel2;
}

void Marker::setRefLabel2(const QString &value)
{
    refLabel2 = value;
}
