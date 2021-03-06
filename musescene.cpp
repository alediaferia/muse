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
#include "musescene.h"
#include "musemediabutton.h"
#include "musemediacontrols.h"
#include "musemediaengine.h"
#include "musevideowidget.h"
#include "museplaylistwidget.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneResizeEvent>
#include <QGraphicsProxyWidget>
// #include <QLinearGradient>
#include <QTimeLine>
#include <QMimeData>
#include <QUrl>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>

#define PLAYLIST_WIDTH 200.0

MuseScene::MuseScene(QObject *parent) : QGraphicsScene(parent), m_mediaObject(0), m_currentMedia(0), m_videoWidget(0)
{
//     setBackgroundBrush(Qt::lightGray);

    m_controls = new MuseMediaControls();
    addItem(m_controls);

    m_playlist = new MusePlaylistWidget;
    addItem(m_playlist);

    connect (this, SIGNAL(sceneRectChanged(const QRectF &)), this, SLOT(adjustItems(const QRectF &)));

    connect (m_controls, SIGNAL(buttonClicked(MuseMediaButton::ButtonType)), this, SLOT(handleMedia(MuseMediaButton::ButtonType)));
    connect (MuseMediaEngine::instance(), SIGNAL(videoSource(MuseVideoWidget*)), this, SLOT(handleVideoSource(MuseVideoWidget*)));

    m_mediaObject = MuseMediaEngine::instance()->currentMediaObject();
    connect (m_mediaObject, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(slotStateChanged(Phonon::State, Phonon::State)));

}

MuseScene::~MuseScene()
{
    delete m_controls;
    delete m_playlist;
//     delete m_background;
}

void MuseScene::positionMediaControls()
{
    const int mediaControlsWidth = m_controls->size().width();
    const int mediaControlsHeight = m_controls->size().height();
    QRectF rect(0, 0, mediaControlsWidth, mediaControlsHeight);

    rect.moveCenter(sceneRect().center());
    rect.translate(0, sceneRect().center().y() - (rect.height() / 2));

    m_controls->setPos(rect.topLeft());
//     qDebug() << m_controls->pos();
}

void MuseScene::animateControls()
{
    qDebug() << "animating";
    QTimeLine *timer = new QTimeLine(2000);
    timer->setFrameRange(0, 100);
//     connect( timer, SIGNAL(frameChanged(int)), this, SLOT(controlAnimation(int)));

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(this);
    animation->setItem(m_controls);
    animation->setTimeLine(timer);

    for (int i = 0; i < 100; i++) {
        animation->setPosAt(i / 100.0, QPointF(m_controls->pos().x(), (i / 100.0)*(sceneRect().height() - m_controls->size().height())));
    }

    timer->start();
}

void MuseScene::controlAnimation(int i)
{
    qDebug() << i;
}

void MuseScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!event->mimeData()->hasUrls()) {
        return;
    }

    event->accept();
    QList<QUrl> droppedUrls = event->mimeData()->urls();

    // TODO: use MuseMediaEngine
    MuseMediaEngine::instance()->enqueueMedia(droppedUrls);

    foreach (const QUrl &url, droppedUrls) {
        m_playlist->addItem(url);
    }
}

void MuseScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!event->mimeData()->hasUrls()) {
        return;
    }

    event->accept();
}

void MuseScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{  
    event->accept();
}

void MuseScene::showCurrentMedia(const QString &media)
{
    m_currentMedia = addText(media);
}

void MuseScene::handleMedia(MuseMediaButton::ButtonType type)
{
    switch (type) {
        case MuseMediaButton::Start :
            m_mediaObject->play();
            break;
        case MuseMediaButton::Pause :
            m_mediaObject->pause();
            break;
        case MuseMediaButton::Stop :
            m_mediaObject->stop();
            break;
        default : ;
    }
}

void MuseScene::handleVideoSource(MuseVideoWidget *videoWidget)
{
    qDebug() << "video source";
    if (!m_videoWidget) {
        addItem(videoWidget);
        m_videoWidget = videoWidget;
        qDebug() << m_videoWidget->isVisible() << "visible";
    }
}

void MuseScene::slotStateChanged(Phonon::State newState, Phonon::State oldState)
{
    if (m_videoWidget && newState == Phonon::PlayingState) {
    }
}

void MuseScene::adjustItems(const QRectF &rect)
{
    m_playlist->setPos(rect.topLeft());
    m_playlist->resize(PLAYLIST_WIDTH, rect.height());
}

#include "musescene.moc"
