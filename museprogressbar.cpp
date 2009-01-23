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
#include "museprogressbar.h"

#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QLinearGradient>
#include <QColor>
#include <QDebug>

MuseProgressBar::MuseProgressBar(QGraphicsItem *parent) : QGraphicsWidget(parent), m_totalTime(100.0), m_progress(0.1)
{
    setMaximumHeight(10);

    resize(200, 10);
}

MuseProgressBar::~MuseProgressBar()
{}

qint64 MuseProgressBar::totalTime() const
{
    return m_totalTime;
}

qint64 MuseProgressBar::progress() const
{
    return m_progress;
}

void MuseProgressBar::setTotalTime(qint64 total)
{
    qDebug() << "total" << total;
    m_totalTime = total;
    m_progress = 0.1;
    update();
}

void MuseProgressBar::setProgress(qint64 progress)
{
    qDebug() << "progress" << progress;
    m_progress = progress;
    update();
}

void MuseProgressBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    qDebug() << "painting";

    drawBase(painter, option->rect);
    drawProgress(painter, option->rect);
}

void MuseProgressBar::drawBase(QPainter *painter, const QRectF &contentsRect)
{
    painter->save();
    QPointF start(contentsRect.center());
    start.setY(contentsRect.top());

    QPointF final(contentsRect.center());
    final.setY(contentsRect.bottom());

    QLinearGradient gradient(start, final);
    gradient.setColorAt(0.0, QColor(143, 143, 143));
    gradient.setColorAt(0.58, Qt::white);
    gradient.setColorAt(1.0, QColor(189, 189, 189));

    painter->setPen(QColor(0, 121, 255));
    painter->setBrush(gradient);

    painter->drawRect(contentsRect);

    painter->restore();

}

void MuseProgressBar::drawProgress(QPainter *painter, const QRectF &contentsRect)
{
    QRectF progressRect = contentsRect;
    progressRect.setWidth(((float)m_progress / m_totalTime) * contentsRect.width());

    qDebug() << m_progress << m_totalTime << (float)(m_progress / m_totalTime);

    qDebug() << (qint64)progressRect.width();

    QPointF start(contentsRect.center());
    start.setY(contentsRect.top());

    QPointF final(contentsRect.center());
    final.setY(contentsRect.bottom());

    QLinearGradient gradient(start, final);
    gradient.setColorAt(0.0, QColor(0, 145, 255));
    gradient.setColorAt(0.6, QColor(0, 66, 151));
    gradient.setColorAt(0.75, QColor(13, 53, 255));
    gradient.setColorAt(1.0, QColor(26, 236, 255));

    painter->save();

    painter->setPen(QColor(0, 121, 255));
    painter->setBrush(gradient);

    painter->drawRect(progressRect);
    painter->restore();
}

#include "museprogressbar.moc"
