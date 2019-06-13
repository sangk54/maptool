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
    MarkerManager *getInstance();
    bool load(const QString &path);


private:
    MarkerManager(const QString &path);
    ~MarkerManager();

    static MarkerManager *instance;

    QVector<Marker*> listMarkers;
    QMap<QString, Marker*> map;
};

#endif // MARKERMANAGER_H
