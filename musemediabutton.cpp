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
#include "musemediabutton.h"

#include <QtSvg/QSvgRenderer>
#include <QGraphicsSceneResizeEvent>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include <QDebug>

MuseMediaButton::MuseMediaButton(ButtonType type, QGraphicsItem *parent) : QGraphicsWidget(parent), m_btype(type)
{
    setAcceptHoverEvents(true);
    setMinimumSize(QSize(64, 64));
    resize (QSize(64, 64));

    setAcceptedMouseButtons(Qt::LeftButton);
}

MuseMediaButton::~MuseMediaButton()
{}

void MuseMediaButton::setButtonType(ButtonType type)
{
    m_btype = type;
}

MuseMediaButton::ButtonType MuseMediaButton::buttonType()
{
    return m_btype;
}

void MuseMediaButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    QSvgRenderer svg(idForType(m_btype));

    svg.render(painter, option->rect);
}

QString MuseMediaButton::idForType(MuseMediaButton::ButtonType type) const
{
    QString id;
    switch (type) {
        case Eject :
            id = ":images/media-eject.svg";
            break;
        case Pause :
            id = ":images/media-playback-pause.svg";
            break;
        case Start :
            id = ":images/media-playback-start.svg";
            break;
        case Stop :
            id = ":images/media-playback-stop.svg";
             break;
        case SeekBackward :
            id = ":images/media-seek-backward.svg";
            break;
        case SeekForward :
            id = ":images/media-seek-forward.svg";
            break;
        case SkipBackward :
            id = ":images/media-skip-backward.svg";
            break;
        case SkipForward :
            id = ":images/media-skip-forward.svg";
            break;
        default : ;
    }

    return id;
}

void MuseMediaButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)

    m_enterAnimation->timeLine()->stop();
    QTimeLine *timer = new QTimeLine(500);
    timer->setFrameRange(0, 100);

    m_leaveAnimation = new QGraphicsItemAnimation(this);
    m_leaveAnimation->setItem(this);
    m_leaveAnimation->setTimeLine(timer);

    m_leaveAnimation->setScaleAt(0.0, 1.1, 1.1);
//     m_leaveAnimation->setTranslationAt(0.0, 0, -30);
    m_leaveAnimation->setScaleAt(1.0, 1, 1);
//     m_leaveAnimation->setTranslationAt(1.0, 0, 0);

    timer->start();
}

void MuseMediaButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)

    QTimeLine *timer = new QTimeLine(500);
    timer->setFrameRange(0, 100);

    m_enterAnimation = new QGraphicsItemAnimation(this);
    m_enterAnimation->setItem(this);
    m_enterAnimation->setTimeLine(timer);

    m_enterAnimation->setScaleAt(0.0, 1, 1);
//     m_enterAnimation->setTranslationAt(0.0, 0, 0);
    m_enterAnimation->setScaleAt(1.0, 1.1, 1.1);
//     m_enterAnimation->setTranslationAt(1.0, 0, -30);

    timer->start();
}

void MuseMediaButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void MuseMediaButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(buttonType());
    QGraphicsWidget::mouseReleaseEvent(event);
}

#include "musemediabutton.moc"
