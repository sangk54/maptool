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


    manager = MarkerManager::getInstance();
}

DrawableWidget::~DrawableWidget()
{
    delete ui;
}

QSize DrawableWidget::sizeHint() const
{
    return pixBg.size();
}


void DrawableWidget::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw background
    painter.drawPixmap(0, 0, pixBg);

    // draw markers
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));

    QFont myFont("Arial", 12);
    QFontMetrics fm(myFont);
    painter.setFont(myFont);

    int mw = pixMarker.size().width();
    int mh = pixMarker.size().height();

    int numMarkers = manager->numberOfMarkers();
    for (int i = 0; i < numMarkers; i++)
    {
        Marker *marker = manager->getMarker(i);
        QPointF center = marker->getPos();
        painter.drawPixmap(center.x() - mw/2, center.y() - mh, pixMarker);

        int tw = fm.width(marker->getLabel());
        painter.drawText(center.x() - tw/2, center.y() - mh-5, marker->getLabel());
    }
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

   QAction action1("Add marker", this);
   action1.setData(pos);
   connect(&action1, SIGNAL(triggered()), this, SLOT(addMarker()));
   contextMenu.addAction(&action1);

   QAction action2("Add camera", this);
   action2.setData(pos);
   connect(&action2, SIGNAL(triggered()), this, SLOT(addCamera()));
   contextMenu.addAction(&action2);


   contextMenu.exec(mapToGlobal(pos));
}

void DrawableWidget::addMarker()
{
    QString text = QInputDialog::getText(this, "Add new marker", "Enter label:");
    if (text.isEmpty())
        return;

    QAction *act = (QAction*)sender();
    QPoint pos = act->data().toPoint();

    manager->addMarker(new Marker(text, pos.x(), pos.y()));
    repaint();
}

void DrawableWidget::addCamera()
{
    QString text = QInputDialog::getText(this, "Add new camera", "Enter label:");
    if (text.isEmpty())
        return;

    QAction *act = (QAction*)sender();
    QPoint pos = act->data().toPoint();

    manager->addMarker(new Camera(text, pos.x(), pos.y()));
    repaint();
}

