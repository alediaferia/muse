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
#include "musebackground.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QtSvg/QSvgRenderer>

#include <QWidget>
#include <QVBoxLayout>

#include <phonon/videowidget.h>

MuseBackground::MuseBackground(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
//     setZValue(0);
}

MuseBackground::~MuseBackground()
{}

void MuseBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//     Q_UNUSED(widget)
/*
    QSvgRenderer svg(QString(":images/background.svg"));
    svg.render(painter, option->rect);*/

//     painter->fillRect(option->rect, Qt::green);
    QGraphicsWidget::paint(painter, option, widget);

}

void MuseBackground::setVideoWidget(Phonon::VideoWidget *vwidget)
{
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);

    QWidget *helper = new QWidget;
    QVBoxLayout *vblayout = new QVBoxLayout(helper);
    vblayout->addWidget(vwidget);

    proxy->setWidget(helper);
    vwidget->resize(vwidget->sizeHint());
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    layout->addItem(proxy);

    setLayout(layout);
}

#include "musebackground.moc"
