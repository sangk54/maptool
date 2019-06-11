#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "drawablewidget.h"
#include "ui_drawablewidget.h"

DrawableWidget::DrawableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawableWidget)
{
    ui->setupUi(this);


    pixBg = QPixmap::fromImage(QImage(":/images/layout-1.png"));
    pixMarker = QPixmap::fromImage(QImage(":/images/marker.png"));

    this->setMouseTracking(true);
}

DrawableWidget::~DrawableWidget()
{
    saveListAnchor();
    delete ui;
}

QSize DrawableWidget::sizeHint() const
{
    return pixBg.size();
}

void DrawableWidget::loadListAnchor()
{

}

void DrawableWidget::saveListAnchor()
{
    QFile saveFile("anchor.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }

    QJsonObject gameObject;

    QJsonArray array;
    foreach (const Marker& marker, listAnchors)
    {
        QJsonObject mo;
        mo["label"] = marker.getLabel();
        mo["x"] = marker.getX();
        mo["y"] = marker.getY();

        array.append(mo);
    }
    gameObject["markers"] = array;

    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    qDebug() << saveDoc.toJson();
    return ;
}

void DrawableWidget::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);

    // draw background
    painter.drawPixmap(0, 0, pixBg);

    // draw anchors
    int mw = pixMarker.size().width();
    int mh = pixMarker.size().height();
    for (Marker &anchor : listAnchors)
        painter.drawPixmap(anchor.getX() - mw/2, anchor.getY() - mh, pixMarker);
}

void DrawableWidget::mouseMoveEvent(QMouseEvent *evt)
{
    emit currentMousePosition(evt->pos());
}

void DrawableWidget::mouseReleaseEvent(QMouseEvent *evt)
{
    if (evt->button() == Qt::RightButton)
    {
        showContextMenu(evt->pos());
    }
}

void DrawableWidget::showContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("Context menu"), this);

   QAction action1("Add anchor", this);
   action1.setData(pos);
   connect(&action1, SIGNAL(triggered()), this, SLOT(addAnchor()));
   contextMenu.addAction(&action1);

   contextMenu.exec(mapToGlobal(pos));
}

void DrawableWidget::addAnchor()
{
    QString text = QInputDialog::getText(this, "Add new anchor", "Enter label:");
    if (text.isEmpty())
        return;

    QAction *act = (QAction*)sender();
    QPoint pos = act->data().toPoint();

    listAnchors.append(Marker(text, pos.x(), pos.y()));
}

