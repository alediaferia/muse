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
#include "musemediaengine.h"

#include <phonon/mediasource.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/videowidget.h>

MuseMediaEngine::MuseMediaEngine(QObject *parent) : QObject(parent), m_mediaObject(new Phonon::MediaObject(this)), m_videoWidget(0), m_audioOutput(0)
{
    connect (m_mediaObject, SIGNAL(currentSourceChanged(const Phonon::MediaSource &)),
             this, SLOT(slotSourceChanged(const Phonon::MediaSource &)));
}

MuseMediaEngine::~MuseMediaEngine()
{
    delete m_instance;
    delete m_videoWidget;
}

MuseMediaEngine* MuseMediaEngine::m_instance = 0;
MuseMediaEngine* MuseMediaEngine::instance()
{
    if (!m_instance) {
        m_instance = new MuseMediaEngine;
    }
    return m_instance;
}

void MuseMediaEngine::enqueueMedia(const QList<QUrl> &source)
{
    m_mediaObject->enqueue(source);
}

void MuseMediaEngine::slotSourceChanged(const Phonon::MediaSource &source)
{
    if (source.type() == Phonon::MediaSource::Invalid) {
        return;
    }

    if (m_mediaObject->hasVideo()) {
        if (!m_videoWidget) {
            m_videoWidget = new Phonon::VideoWidget;
            Phonon::createPath(m_mediaObject, m_videoWidget);
        }
        emit videoSource(m_videoWidget);

        delete m_audioOutput;
        m_audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
        Phonon::createPath(m_mediaObject, m_audioOutput);
        emit playingSource(source);
        return;
    }

    delete m_audioOutput;
    m_audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(m_mediaObject, m_audioOutput);
    emit playingSource(source);
}

Phonon::MediaObject* MuseMediaEngine::currentMediaObject()
{
    return m_mediaObject;
}

#include "musemediaengine.moc"
