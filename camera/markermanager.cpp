#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QFile>

#include "markermanager.h"

MarkerManager * MarkerManager::instance = NULL;

MarkerManager *MarkerManager::getInstance()
{
    if (instance == NULL)
        instance = new MarkerManager();




    return instance;
}

bool MarkerManager::load(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << path << " is not found";
        return false;
    }
    QString content = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject root = doc.object();

    QJsonArray arrMarkers = root["markers"].toArray();

    for (int i = 0; i < arrMarkers.size(); i++)
    {
        QJsonObject objMarker = arrMarkers[i].toObject();

        // position
        QJsonArray arrPos = objMarker["pos"].toArray();
        QString label = arrPos[0].toString();
        float x = arrPos[1].toDouble();
        float y = arrPos[2].toDouble();

        // list of border markers
        Marker *marker = NULL;
        if (objMarker.contains("borders"))
        {
            // this is a camera
            marker = new Camera(label, x, y);
            QJsonArray arrBorders = objMarker["borders"].toArray();

            for (int k = 0; k < arrBorders.size(); k++)
            {
                marker->addBorder(arrBorders[k].toString());
            }
        }
        else
        {
            // this is a normal marker
            marker = new Marker(label, x, y);
        }

        // reference marker
        QJsonArray arrRef = objMarker["ref"].toArray();
        marker->setReferenceMarker(arrRef[0].toString(), arrRef[1].toDouble(), 1);
        marker->setReferenceMarker(arrRef[2].toString(), arrRef[3].toDouble(), 2);

        listMarkers.append(marker);
        map[label] = marker;
    }


}
