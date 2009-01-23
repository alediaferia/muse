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
#ifndef MUSEPROGRESSBAR_H
#define MUSEPROGRESSBAR_H

#include <QGraphicsWidget>

class MuseProgressBar : public QGraphicsWidget
{
    Q_OBJECT
public:
    MuseProgressBar(QGraphicsItem *parent = 0);
    ~MuseProgressBar();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    qint64 totalTime() const;
    qint64 progress() const;

private:
    qint64 m_totalTime;
    qint64 m_progress;

    void drawBase(QPainter *painter, const QRectF &contentsRect);
    void drawProgress(QPainter *painter, const QRectF &contentsRect);

public slots:
    void setTotalTime(qint64 time);
    void setProgress(qint64 current);
};

#endif
