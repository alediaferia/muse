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
#ifndef MUSEVIDEOWIDGET_H
#define MUSEVIDEOWIDGET_H

#include <QGraphicsWidget>

class QGraphicsSceneMouseEvent;
class QEvent;

namespace Phonon {
    class VideoWidget;
}

class MuseVideoWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    MuseVideoWidget(Phonon::VideoWidget*, QGraphicsItem *parent = 0);
    ~MuseVideoWidget();

    Phonon::VideoWidget* nativeWidget();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    class Private;
    Private *d;

    void drawResizeControls(QPainter *painter, const QStyleOptionGraphicsItem *option) const;
    QList<QRectF> calculateResizeRects(const QRectF &widgetRect) const;
    void doResize(const float &xDelta, const float &yDelta);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

protected slots:
    void slotFading(int);
};

#endif
