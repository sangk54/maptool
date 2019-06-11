#ifndef ANCHOR_H
#define ANCHOR_H

#include <QString>

class Marker
{
public:
    Marker(const QString label = "", float x = 0, float y = 0);

    QString getLabel() const;
    void setLabel(const QString &value);

    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

private:
    QString label;
    float x;
    float y;
};

#endif // ANCHOR_H
