/***************************************************************************
 *   Copyright (C) 2009 by Alessandro Diaferia <alediaferia@gmail.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 **************************************************************************/

#include "musevideowidget.h"

#include <QDebug>
#include <phonon/videowidget.h>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemAnimation>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QStyleOptionGraphicsItem>
#include <QTimeLine>
#include <QPalette>
#include <QPainter>
#include <QTransform>

#define MARGIN 16

class MuseVideoWidget::Private
{
public:
    Private(MuseVideoWidget *q) : q(q), 
        timeLine(new QTimeLine(500, q)),
        animation(new QGraphicsItemAnimation(q)),
        edgeFade(0.0), hovering(false), resizing(false)
        {}

    MuseVideoWidget *q;
    Phonon::VideoWidget *videoWidget;
    QPointF pressPos;
    QPointF movePos;
    QTimeLine *timeLine;
    QGraphicsItemAnimation *animation;
    qreal edgeFade;
    bool hovering;
    bool resizing;
    QGraphicsProxyWidget *proxy;
    QList<QRectF> resizeRects;
    int resizeRectId;
};

MuseVideoWidget::MuseVideoWidget(Phonon::VideoWidget *videoWidget, QGraphicsItem *parent) : QGraphicsWidget(parent), d(new Private(this))
{
    d->videoWidget = videoWidget;
//     setWidget(videoWidget);
//     setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    d->timeLine->setFrameRange(0, 100);

    d->animation->setItem(this);
    d->animation->setTimeLine(d->timeLine);

    setContentsMargins(MARGIN, MARGIN, MARGIN, MARGIN);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    d->proxy = new QGraphicsProxyWidget;
    d->proxy->setWidget(d->videoWidget);

    layout->addItem(d->proxy);

    setLayout(layout);
    resize(d->videoWidget->sizeHint());
}

MuseVideoWidget::~MuseVideoWidget()
{
    delete d;
}

Phonon::VideoWidget* MuseVideoWidget::nativeWidget()
{
    return d->videoWidget;
}

void MuseVideoWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    d->pressPos = event->pos();

    if (!d->hovering) {
        return;
    }

    d->resizeRectId = 0;
    foreach (const QRectF rect, d->resizeRects) {
        if (rect.contains(d->pressPos)) {
            d->resizing = true;
            qDebug() << "resize rect" << d->resizeRectId;
            break;
        }
        d->resizeRectId++;
    }
}

void MuseVideoWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF target(event->pos());
    const float xDelta = target.x() - d->pressPos.x();
    const float yDelta = target.y() - d->pressPos.y();

    if (d->resizing) {
        qDebug() << "doing resize";
        doResize(xDelta, yDelta);
        return;
    }

    moveBy(xDelta, yDelta);
    d->movePos = target;
}

void MuseVideoWidget::doResize(const float &xDelta, const float &yDelta)
{
    switch (d->resizeRectId) {
	case 0 : //top left (keep aspect ratio)
            const float newSize = qMax(xDelta, yDelta);
            qDebug() << (float)newSize;
	    resize(size().width() - newSize, size().height() - newSize);
// 	    moveBy(-newSize, -newSize);
	    break;
//             case 1 : //top center
// 
//                 break;
//             case 2 : //top right
// 
//                 break;
//             case 3 : //middle left
// 
//                 break;
    }
}

void MuseVideoWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (d->resizing) {
        d->resizing = false;
        return;
    }

    if (d->timeLine->state() == QTimeLine::Running) {
        d->timeLine->stop();
    }

    const int xDelta = d->movePos.x() - event->pos().x();
    const int yDelta = d->movePos.y() - event->pos().y();

    d->animation->setPosAt(0.0, pos());
    QPoint finalPoint;
    finalPoint.setX(pos().x() + 10*xDelta);
    finalPoint.setY(pos().y() + 10*yDelta);
    d->animation->setPosAt(1.0, finalPoint);

    d->timeLine->start();
}

void MuseVideoWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QGraphicsWidget::paint(painter, option, widget);

//     painter->fillRect(option->rect, Qt::green);
    drawResizeControls(painter, option);
}

void MuseVideoWidget::drawResizeControls(QPainter *painter, const QStyleOptionGraphicsItem *option) const
{
    if (!d->hovering) {
        return;
    }

    painter->setRenderHint(QPainter::Antialiasing);
    QColor color(palette().color(QPalette::Highlight));
    color.setAlpha(127 * d->edgeFade);

    painter->setBrush(color);
    painter->setPen(color);
    QRectF anchor(0, 0, MARGIN, MARGIN);

    d->resizeRects.clear();

    d->resizeRects << calculateResizeRects(option->rect);

    foreach (const QRectF &rect, d->resizeRects) {
        painter->drawRect(rect);
    }

//     // let's draw each edge
//     anchor.moveCenter(mapFromItem(d->proxy, d->videoWidget->rect().topLeft()));
//     d->resizeRects << anchor;
//     painter->drawEllipse(anchor);
// 
//     anchor.moveCenter(mapFromItem(d->proxy, d->videoWidget->rect().topRight()));
//     d->resizeRects << anchor;
//     painter->drawEllipse(anchor);
// 
//     anchor.moveCenter(mapFromItem(d->proxy, d->videoWidget->rect().bottomRight()));
//     d->resizeRects << anchor;
//     painter->drawEllipse(anchor);
// 
//     anchor.moveCenter(mapFromItem(d->proxy, d->videoWidget->rect().bottomLeft()));
//     d->resizeRects << anchor;
//     painter->drawEllipse(anchor);
}

QList<QRectF> MuseVideoWidget::calculateResizeRects(const QRectF &widgetRect) const
{
    QList<QRectF> rects;

    const float wDelta = widgetRect.width() / 3.0;
    const float hDelta = widgetRect.height() / 3.0;

    QRectF topLeftRect(0, 0, wDelta, hDelta);

    // first row
    rects << topLeftRect;
    rects << topLeftRect.translated(wDelta, 0);
    rects << topLeftRect.translated(2*wDelta, 0);

    // second row
    rects << topLeftRect.translated(0, hDelta);
    rects << topLeftRect.translated(wDelta, hDelta);
    rects << topLeftRect.translated(2*wDelta, hDelta);

    // third row
    rects << topLeftRect.translated(0, 2*hDelta);
    rects << topLeftRect.translated(wDelta, 2*hDelta);
    rects << topLeftRect.translated(2*wDelta, 2*hDelta);

    return rects;
}

void MuseVideoWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    d->hovering = false;

//     d->timeLine->stop();
    disconnect (d->timeLine);

    update();
}

void MuseVideoWidget::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!(event->modifiers() & Qt::ControlModifier)) {
        return;
    }

    d->hovering = true;

    connect (d->timeLine, SIGNAL(frameChanged(int)), this, SLOT(slotFading(int)));
    d->animation->clear();

    if (d->timeLine->state() != QTimeLine::Running) {
        d->timeLine->start();
    }
}

void MuseVideoWidget::slotFading(int fade)
{
    d->edgeFade = fade / 100.0;
    update();
}

#include "musevideowidget.moc"
