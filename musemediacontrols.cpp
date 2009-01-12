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
#include "musemediacontrols.h"

#include <QGraphicsItem>
#include <QGraphicsLinearLayout>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QtSvg/QSvgRenderer>

MuseMediaControls::MuseMediaControls(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;

    m_stop = new MuseMediaButton(MuseMediaButton::Stop, this);
    layout->addItem(m_stop);
    connect (m_stop, SIGNAL(clicked(MuseMediaButton::ButtonType)), this, SIGNAL(buttonClicked(MuseMediaButton::ButtonType)));
    m_start = new MuseMediaButton(MuseMediaButton::Start, this);
    layout->addItem(m_start);
    m_start->setZValue(10);
    connect (m_start, SIGNAL(clicked(MuseMediaButton::ButtonType)), this, SIGNAL(buttonClicked(MuseMediaButton::ButtonType)));
    m_pause = new MuseMediaButton(MuseMediaButton::Pause, this);
    layout->addItem(m_pause);
    connect (m_pause, SIGNAL(clicked(MuseMediaButton::ButtonType)), this, SIGNAL(buttonClicked(MuseMediaButton::ButtonType)));

//     setMinimumSize(m_stop->size().width() * 3, m_stop->size().height());

    setLayout(layout);
//     this->layout()->activate();
    setZValue(99999);
}

MuseMediaControls::~MuseMediaControls()
{}

void MuseMediaControls::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QSvgRenderer svg(QString(":images/mediacontrols.svg"));

    svg.render(painter, option->rect);
}

#include "musemediacontrols.moc"
