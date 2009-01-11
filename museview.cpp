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
#include "museview.h"
#include "musescene.h"

#include <QtSvg/QSvgRenderer>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

MuseView::MuseView(QWidget *parent) : QGraphicsView(parent), m_activeItem(0)
{
    setScene(new MuseScene(this));
//     setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    QTimer::singleShot(0, static_cast<MuseScene*>(scene()),SLOT(animateControls()));
}

MuseView::~MuseView()
{}

void MuseView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    scene()->setSceneRect(rect());
    static_cast<MuseScene*>(scene())->positionMediaControls();
}

// void MuseView::drawBackground(QPainter *painter, const QRectF & rect)
// {
//     qDebug() << "drawBackground" << rect;
//     QSvgRenderer svg(QString(":/images/museview.svg"));
//     svg.render(painter, "background", rect);
// }

// void MuseView::mousePressEvent(QMouseEvent *event)
// {
//     m_activeItem = itemAt(event->pos());
//     QGraphicsView::mousePressEvent(event);
// }
// 
// void MuseView::mouseMoveEvent (QMouseEvent *event)
// {
//     QGraphicsView::mouseMoveEvent(event);
//     if (m_activeItem) {
//         m_activeItem->setPos(mapToScene(event->pos()));
//     }
// }
// 
// void MuseView::mouseReleaseEvent (QMouseEvent *event)
// {
//     m_activeItem = 0;
//     QGraphicsView::mouseReleaseEvent(event);
// }

#include "museview.moc"
