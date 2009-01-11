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
#ifndef MUSEMEDIABUTTON_H
#define MUSEMEDIABUTTON_H

#include <QGraphicsWidget>
class QGraphicsItem;
class QGraphicsSceneResizeEvent; 
class QPainter;
class QStyleOptionGraphicsItem;
class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;
class QGraphicsItemAnimation;
class QWidget;

class MuseMediaButton : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum ButtonType {
                      Eject,
                      Pause,
                      Start,
                      Stop,
                      SkipForward,
                      SkipBackward,
                      SeekForward,
                      SeekBackward
                      };
    MuseMediaButton(ButtonType type, QGraphicsItem *parent = 0);
    ~MuseMediaButton();

    void setButtonType(ButtonType);
    ButtonType buttonType();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    ButtonType m_btype;
    QGraphicsItemAnimation *m_enterAnimation;
    QGraphicsItemAnimation *m_leaveAnimation;

protected:
//     void resizeEvent(QGraphicsSceneResizeEvent *event);
    QString idForType(ButtonType) const;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked(MuseMediaButton::ButtonType);
};

#endif
