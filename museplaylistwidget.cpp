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
#include "museplaylistwidget.h"
#include "museplaylistitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QUrl>

#define ITEM_HEIGHT 32.0

MusePlaylistWidget::MusePlaylistWidget(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    resize(100, 600);
}

MusePlaylistWidget::~MusePlaylistWidget()
{}

void MusePlaylistWidget::addItem(const QUrl &source)
{
    addItem(new MusePlaylistItem(source));
}

void MusePlaylistWidget::addItem(MusePlaylistItem *item)
{
    m_items << item;
    update();
}

void MusePlaylistWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    painter->fillRect(rect(), Qt::red);
    QRectF itemRect = contentsRect();
    itemRect.setHeight(ITEM_HEIGHT);

    QStyleOptionGraphicsItem opt(*option);
    opt.rect = itemRect.toRect();

    painter->setClipRect(contentsRect());

    foreach (MusePlaylistItem *item, m_items) {
        item->paint(painter, opt);
        itemRect.translate(0, ITEM_HEIGHT);
        opt.rect = itemRect.toRect();
    }
}

#include "museplaylistwidget.moc"

