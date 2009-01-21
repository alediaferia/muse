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
#ifndef MUSEPLAYLISTITEM_H
#define MUSEPLAYLISTITEM_H

#include <QObject>
#include <QUrl>
#include <QRectF>

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

class MusePlaylistItem : public QObject
{
    Q_OBJECT
public:
    MusePlaylistItem(const QUrl &source);
    ~MusePlaylistItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem &option, QWidget *widget = 0);

    void setRect(const QRectF rect);
    QRectF rect() const;

    QUrl source() const;

private:
    QUrl m_source;
    QRectF m_rect;

    QString sourcePrettyName() const;
};

#endif
