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
#ifndef MUSEMEDIAENGINE_H
#define MUSEMEDIAENGINE_H

#include <QObject>
#include <QList>

class QUrl;

namespace Phonon {
    class MediaObject;
    class MediaSource;
    class AudioOutput;
    class VideoWidget;
}

class MuseMediaEngine : public QObject
{
    Q_OBJECT
public:
    static MuseMediaEngine* instance();
    ~MuseMediaEngine();

    void enqueueMedia(const QList<QUrl> &sources);

    /**
     * @returns the current Phonon::MediaObject in use to play media.
     */
    Phonon::MediaObject *currentMediaObject();

private:
    MuseMediaEngine(QObject *parent = 0);

    static MuseMediaEngine *m_instance;
    Phonon::MediaObject *m_mediaObject;
    Phonon::VideoWidget *m_videoWidget;
    Phonon::AudioOutput *m_audioOutput;

protected slots:
    void slotSourceChanged(const Phonon::MediaSource &);

signals:
    /**
     * This signal is emitted only when the current source includes video stream
     * and a Phonon::VideoWidget is needed.
     */
    void videoSource(Phonon::VideoWidget*);

    /**
     * This signal is emitted whenever a new source is getting played.
     */
    void playingSource(const Phonon::MediaSource &);
};

#endif
