#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFile>

#include "markermanager.h"

MarkerManager * MarkerManager::instance = NULL;

MarkerManager *MarkerManager::getInstance()
{
    if (instance == NULL)
        instance = new MarkerManager();
    return instance;
}

void MarkerManager::destroyManager()
{
    if (instance)
    {
        // free all markers
        qDeleteAll(listMarkers);
        listMarkers.clear();

        // free manager
        delete instance;
        instance = NULL;
    }
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
            // borders
            marker = new Camera(label, x, y);
            QJsonArray arrBorders = objMarker["borders"].toArray();

            for (int k = 0; k < arrBorders.size(); k++)
            {
                marker->addBorder(arrBorders[k].toString());
            }

            // pixel
            QJsonArray arrPixel = objMarker["pixel"].toArray();
            marker->setPixel(arrPixel[0].toDouble(), arrPixel[1].toDouble());

            // background path
            marker->setImagePath(objMarker["bgPath"].toString());
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

    return true;
}

bool MarkerManager::save(const QString &path)
{
    QFile saveFile(path);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject root;

    // list of markers
    QJsonArray array;
    foreach (Marker *marker, listMarkers)
    {
        array.append(marker->toJson());
    }
    root["markers"] = array;

    QJsonDocument saveDoc(root);
    saveFile.write(saveDoc.toJson());

    return true;
}

void MarkerManager::addMarker(Marker *marker)
{
    listMarkers.append(marker);
    map[marker->getLabel()] = marker;
}

Marker *MarkerManager::getMarker(int index)
{
    int num = listMarkers.length();
    if (index < num && index >=0)
        return listMarkers[index];
    else
        return NULL;
}

int MarkerManager::numberOfMarkers()
{
    return listMarkers.length();
}
