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
#include <QTimeLine>

class MuseVideoWidget::Private
{
    public:
        Private(MuseVideoWidget *q) : q(q), timeLine(new QTimeLine(500, q)), animation(new QGraphicsItemAnimation(q)) {}

        MuseVideoWidget *q;
        Phonon::VideoWidget *videoWidget;
        QPointF pressPos;
        QPointF movePos;
        QTimeLine *timeLine;
        QGraphicsItemAnimation *animation;
};

MuseVideoWidget::MuseVideoWidget(Phonon::VideoWidget *videoWidget, QGraphicsItem *parent) : QGraphicsProxyWidget(parent), d(new Private(this))
{
    d->videoWidget = videoWidget;
    setWidget(videoWidget);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptedMouseButtons(Qt::LeftButton);

    d->animation->setItem(this);
    d->animation->setTimeLine(d->timeLine);

    qDebug() << flags();
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
}

void MuseVideoWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF target(event->pos());
    const int xDelta = target.x() - d->pressPos.x();
    const int yDelta = target.y() - d->pressPos.y();

    moveBy(xDelta, yDelta);
    d->movePos = target;
}

void MuseVideoWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
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

#include "musevideowidget.moc"
