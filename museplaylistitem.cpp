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
#include "museplaylistitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QFileInfo>

MusePlaylistItem::MusePlaylistItem(const QUrl &source) : m_source(source), m_rect(QRectF())
{}

MusePlaylistItem::~MusePlaylistItem()
{}

void MusePlaylistItem::setRect(const QRectF rect)
{
    m_rect = rect;
}

QRectF MusePlaylistItem::rect() const
{
    return m_rect;
}

QUrl MusePlaylistItem::source() const
{
    return m_source;
}

void MusePlaylistItem::paint(QPainter *painter, const QStyleOptionGraphicsItem &option, QWidget *widget)
{
    Q_UNUSED(widget)

    // contents rect initialization
    QRectF contentsRect = option.rect;
    if (!m_rect.isNull()) {
        contentsRect = m_rect;
    } else {
        m_rect = contentsRect;
    }

    painter->fillRect(contentsRect, Qt::green); // just a debug color
    painter->drawText(contentsRect, Qt::AlignVCenter | Qt::AlignLeft, sourcePrettyName());

}

QString MusePlaylistItem::sourcePrettyName() const
{
    QFileInfo source(m_source.toLocalFile());
    if (!source.exists()) {
        return QString();
    }

    // TODO: chose and use a Tag engine for mp3s
    return source.baseName();
}

#include "museplaylistitem.moc"
