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
#ifndef MUSESCENE_H
#define MUSESCENE_H

#include <QGraphicsScene>
#include "musemediabutton.h"
#include <phonon/phononnamespace.h>

class MuseMediaControls;
class MuseVideoWidget;
class QGraphicsSceneDragDropEvent;
class QGraphicsProxyWidget;

namespace Phonon {
    class MediaObject;
    class VideoWidget;
}

class MuseScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MuseScene(QObject *parent);
    ~MuseScene();

private:
    MuseMediaControls *m_controls;
    Phonon::MediaObject *m_mediaObject;
    QGraphicsItem *m_currentMedia;
    MuseVideoWidget *m_videoWidget;

protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

protected slots:
    void controlAnimation(int);
    void showCurrentMedia(const QString &);
    void handleMedia(MuseMediaButton::ButtonType);
    void handleVideoSource(MuseVideoWidget*);
    void slotStateChanged(Phonon::State, Phonon::State);

public slots:
    void positionMediaControls();
    void animateControls();
};

#endif
