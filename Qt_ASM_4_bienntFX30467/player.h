/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <MyTaglib/tag.h>
#include <MyTaglib/fileref.h>
#include <MyTaglib/id3v2tag.h>
#include <MyTaglib/mpegfile.h>
#include <MyTaglib/id3v2frame.h>
#include <MyTaglib/id3v2header.h>
#include <MyTaglib/attachedpictureframe.h>

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QMediaPlayer;
QT_END_NAMESPACE

class PlaylistModel;

using namespace TagLib;

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool shuffle READ shuffle WRITE setshuffle NOTIFY shuffleChanged);
    Q_PROPERTY(bool loop READ loop WRITE setLoop NOTIFY loopChanged)
public:
    explicit Player(QObject *parent = nullptr);
    void addToPlaylist(const QList<QUrl> &urls);
    void setshuffle(bool shuffle);
    bool shuffle() const;
    void setLoop(bool loop);
    bool loop() const;
    int randomIndex();
public slots:
    void open();
    QString getTimeInfo(qint64 currentInfo);
    void playMedia(bool isPlay);
    void setNextMedia();
    void setPreviousMedia();
    void setCurrentIndex(int index);
    void seek(int position);
    void nextShuffleMedia();
    void handleStoppedState(QMediaPlayer::MediaStatus status);

public:
    QString getAlbumArt(QUrl url);
    QMediaPlayer *m_player = nullptr;
    QMediaPlaylist *m_playlist = nullptr;
    PlaylistModel *m_playlistModel = nullptr;

signals:
    void shuffleChanged(bool shuffle);
    void loopChanged(bool loop);

private:
    bool m_shuffle;
    bool m_loop;
};

#endif // PLAYER_H
