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
#ifndef MUSEVIEW_H
#define MUSEVIEW_H

#include <QGraphicsView>

class QGraphicsItem;

class MuseView : public QGraphicsView
{
    Q_OBJECT
public:
    MuseView(QWidget *parent = 0);
    ~MuseView();

private:
    QGraphicsItem *m_activeItem;
protected:
//     void drawBackground(QPainter *painter, const QRectF & rect);

//     void mousePressEvent (QMouseEvent *event);
//     void mouseMoveEvent (QMouseEvent *event);
//     void mouseReleaseEvent (QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);
};

#endif