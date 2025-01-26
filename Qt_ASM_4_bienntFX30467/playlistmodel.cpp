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

#include "playlistmodel.h"

#include <QFileInfo>
#include <QUrl>
#include <QMediaPlaylist>

Song::Song(const QString &title, const QString &singer, const QString &source, const QString &albumArt)
{
    m_title = title;
    m_singer = singer;
    m_source = source;
    m_albumArt = albumArt;
}

QString Song::title() const
{
    return m_title;
}

QString Song::singer() const
{
    return m_singer;
}

QString Song::source() const
{
    return m_source;
}

QString Song::album_art() const
{
    return m_albumArt;
}


PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent);
    return m_data.size();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    const Song &item = m_data[index.row()];

    switch (role) {
    case TitleRole:
        return item.title();
    case SingerRole:
        return item.singer();
    case SourceRole:
        return item.source();
    case AlbumArtRole:
        return item.album_art();
    default:
        return QVariant();
    }
}

void PlaylistModel::addSong(Song &song)
{
    m_data.append(song);
}

QHash<int, QByteArray> PlaylistModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "tenbaihat";
    roles[SingerRole] = "tencasi";
    roles[SourceRole] = "sourcebaihat";
    roles[AlbumArtRole] = "anhbaihat";
    return roles;
}
