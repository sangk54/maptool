#ifndef MARKER_H
#define MARKER_H

#include <QGraphicsItem>
#include <QPointF>
#include <QString>

#include <QJsonObject>

class Marker : public QGraphicsItem
{
public:
    enum {ANCHOR, CAMERA};
    Marker(const QString &label = "", float x = 0, float y = 0);
    Marker(const QString &label, const QPointF &p);
    virtual ~Marker() {}

    virtual int type() const;
    virtual QJsonObject toJson() const;
    virtual void addBorder(const QString &label);
    virtual void setPixel(float x, float y);
    virtual void setImagePath(const QString &path);

    void setReferenceMarker(const QString &theLabel, float distance, int oneOrTwo);

    QPointF getPos() const;
    void setPos(const QPointF &value);

    float getRefDistance1() const;
    void setRefDistance1(float value);

    float getRefDistance2() const;
    void setRefDistance2(float value);

    QString getLabel() const;
    void setLabel(const QString &value);

    QString getRefLabel1() const;
    void setRefLabel1(const QString &value);

    QString getRefLabel2() const;
    void setRefLabel2(const QString &value);

protected:
    QPointF pos;
    QString label;

    // two reference marker id
    QString refLabel1, refLabel2;
    float refDistance1 = 0, refDistance2 = 0;
};

#endif // MARKER_H
