#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QSharedPointer>

#include "camera/camera.h"


class MarkerManager
{
public:
    static MarkerManager *getInstance();

    void destroyManager();
    bool load(const QString &path);
    bool save(const QString &path);

    void addMarker(Marker* marker);

    Marker *findByLabel(const QString &label);
    Marker * getMarker(int index);
    int numberOfMarkers();

private:
    MarkerManager() {}
    ~MarkerManager() {}
    MarkerManager(const MarkerManager &other){Q_UNUSED(other);}
    MarkerManager& operator=(const MarkerManager &other) {Q_UNUSED(other); return *this;}

    static MarkerManager *instance;
    QVector<Marker*> listMarkers;
    QMap<QString, Marker*> map;
};

#endif // MARKERMANAGER_H
