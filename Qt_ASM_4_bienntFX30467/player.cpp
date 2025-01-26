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

#include "player.h"
#include "playlistmodel.h"
#include <QMediaService>
#include <QMediaMetaData>
#include <QObject>
#include <QFileInfo>
#include <QTime>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <cstdlib>
#include <ctime>

Player::Player(QObject *parent)
    : QObject(parent), m_shuffle(false), m_loop(false)
{
    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(m_playlist);
    m_playlistModel = new PlaylistModel(this);
    // Khi bài hát được chơi xong, signal này sẽ được phát ra. Connect signal này với hàm xử lí handleStoppedState
    // để quyết định bài hát tiếp theo được chơi hoặc lặp lại bài hát đó.
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Player::handleStoppedState);
    open();
    if (!m_playlist->isEmpty()) {
        m_playlist->setCurrentIndex(0);
    }
    m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    // Đặt seed - bộ sinh số ngẫu nhiên theo thời gian thực.
    std::srand(std::time(nullptr));
}

void Player::open()
{
    QDir directory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation)[0]);
    QFileInfoList musics = directory.entryInfoList(QStringList() << "*.mp3",QDir::Files);
    QList<QUrl> urls;
    for (int i = 0; i < musics.length(); i++){
        urls.append(QUrl::fromLocalFile(musics[i].absoluteFilePath()));
    }
    addToPlaylist(urls);
}

void Player::addToPlaylist(const QList<QUrl> &urls)
{
    // Dùng bên window
    QStringList sourceAlbumList;
    for (auto &url: urls) {
        QUrl url1(url.toLocalFile());
        QString filePath = url.path();
        // Loại bỏ dấu / đầu tiên nếu có
        if (filePath.startsWith("/C")) {
            filePath = filePath.mid(2);
        }
        TagLib::FileRef f(filePath.toStdString().c_str());
        sourceAlbumList.append(getAlbumArt(url1));
    }

    for (int i = 0; i < urls.size(); i++) {
        m_playlist->addMedia(urls[i]);
        QString filePath = urls[i].toLocalFile();
        // Loại bỏ dấu / đầu tiên nếu có
        if (filePath.startsWith("/")) {
            filePath = filePath.mid(1);
        }
        FileRef f(filePath.toStdString().c_str());
        Tag *tag = f.tag();
        Song song(QString::fromWCharArray(tag->title().toCWString()),
                QString::fromWCharArray(tag->artist().toCWString()),urls[i].toDisplayString(),sourceAlbumList.at(i));
        m_playlistModel->addSong(song);
    }

    /*/ Dùng bên linux
    for (auto &url: urls) {
        m_playlist->addMedia(url);
        FileRef f(url.path().toStdString().c_str());
        Tag *tag = f.tag();
        Song song(QString::fromWCharArray(tag->title().toCWString()),
                QString::fromWCharArray(tag->artist().toCWString()),url.toDisplayString(),getAlbumArt(url));
        m_playlistModel->addSong(song);
    }*/
}

void Player::setshuffle(bool shuffle)
{
    if (m_shuffle == shuffle)
        return;

    m_shuffle = shuffle;
    emit shuffleChanged(shuffle);
}

bool Player::shuffle() const
{
    return m_shuffle;
}

void Player::setLoop(bool loop)
{
    if (m_loop == loop)
        return;

    m_loop = loop;
    emit loopChanged(loop);
}

bool Player::loop() const
{
    return m_loop;
}

// Hàm trả về index ngẫu nhiên
int Player::randomIndex()
{
    int currentIndex = m_playlist->currentIndex();
    int nextIndex;
    do {
        // Tạo số ngẫu nhiên trong phạm vi 0 đến mediaCount - 1.
        nextIndex = std::rand() % m_playlist->mediaCount();
    // Nếu index ngẫu nhiên trùng với index bài hát hiện tại thì tìm một số ngẫu nhiên khác
    } while (nextIndex == currentIndex);
    qDebug() << "Index Random: " << nextIndex;
    return nextIndex;
}

QString Player::getTimeInfo(qint64 currentInfo)
{
    QString tStr = "00:00";
    currentInfo = currentInfo/1000;
    qint64 durarion = m_player->duration()/1000;
    if (currentInfo || durarion) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
                          currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((durarion / 3600) % 60, (m_player->duration() / 60) % 60,
                        durarion % 60, (m_player->duration() * 1000) % 1000);
        QString format = "mm:ss";
        if (durarion > 3600)
            format = "hh::mm:ss";
        tStr = currentTime.toString(format);
    }
    return tStr;
}

// Hàm dừng hoặc chơi nhạc
void Player::playMedia(bool isPlay)
{
    if(isPlay){
        m_player->play();
    }
    else{
        m_player->pause();
    }
}

void Player::setNextMedia()
{
    m_playlist->next();
}

void Player::setPreviousMedia()
{
    m_playlist->previous();
}

void Player::setCurrentIndex(int index)
{
    m_playlist->setCurrentIndex(index);
}

void Player::seek(int position)
{
    m_player->setPosition(position);
}

// Hàm thực hiện khi Next Button (hoặc Previous Button) được click (Tức là bài hát hiện tại đang phát có thể chưa chơi hết bài nhưng muốn chuyển sang bài mới). Hàm này sẽ chuyển tiếp bài hát ngẫu nhiên khi Shuffle Button được bật và Next Button (hoặc Previous Button) được nhấn mà không cần xét trạng thái của Repeat Button.
void Player::nextShuffleMedia()
{
    // Gán một index ngẫu nhiên cho biến nextIndex
    int nextIndex = randomIndex();
    // Trình phát nhạc sẽ phát bài hát ngẫu nhiên tiếp theo.
    m_playlist->setCurrentIndex(nextIndex);
    qDebug() << "Next Button: Shuffle. Current: " << m_playlist->currentIndex();
}

// Hàm thực hiện phát bài hát tiếp theo dựa trên trạng thái khi bài hát kết thúc và trạng thái của Shuffle và Repeat Button.
void Player::handleStoppedState(QMediaPlayer::MediaStatus status)
{
    // Nếu bài hát đang phát đã chơi xong.
    if(status == QMediaPlayer::EndOfMedia){
        // Nếu Shuffle Button được bật và Repeat Button tắt
        if(m_shuffle && !m_loop){
            int nextIndex = randomIndex();
            // Trình phát nhạc sẽ phát bài hát ngẫu nhiên tiếp theo.
            m_playlist->setCurrentIndex(nextIndex);
            qDebug() << "End of Media: Shufle. Current: " << m_playlist->currentIndex();
        }
        // Nếu Repeat Button được bật và bất kể Shuffle Button bật hoặc tắt.
        else if(m_loop){
            qDebug() << "End of Media: Loop ";
            // Trình phát nhạc sẽ lặp lại bài hát hiện tại.
            m_playlist->setCurrentIndex(m_playlist->currentIndex());
        }
        else{
            qDebug() << "End of Media. No shuffle and no loop";
        }
    }
}

QString Player::getAlbumArt(QUrl url)
{
    static const char *IdPicture = "APIC" ;
    TagLib::MPEG::File mpegFile(url.path().toStdString().c_str());
    TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
    TagLib::ID3v2::FrameList Frame ;
    TagLib::ID3v2::AttachedPictureFrame *PicFrame ;
    void *SrcImage ;
    unsigned long Size ;

    FILE *jpegFile;
    jpegFile = fopen(QString(url.fileName()+".jpg").toStdString().c_str(),"wb");

    if ( id3v2tag )
    {
        // picture frame
        Frame = id3v2tag->frameListMap()[IdPicture] ;
        if (!Frame.isEmpty() )
        {
            for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it)
            {
                PicFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(*it) ;
                //  if ( PicFrame->type() ==
                //TagLib::ID3v2::AttachedPictureFrame::FrontCover)
                {
                    // extract image (in it’s compressed form)
                    Size = PicFrame->picture().size() ;
                    SrcImage = malloc ( Size ) ;
                    if ( SrcImage )
                    {
                        memcpy ( SrcImage, PicFrame->picture().data(), Size ) ;
                        fwrite(SrcImage,Size,1, jpegFile);
                        fclose(jpegFile);
                        free( SrcImage ) ;
                        // "file:NangTho-HoangDung.mp3.jpg"
                        return QUrl::fromLocalFile(url.fileName()+".jpg").toDisplayString();
                    }

                }
            }
        }
    }
    else
    {
        qDebug() <<"id3v2 not present";
        return "qrc:/Image_Low_Dpi/album_art.png";
    }
    return "qrc:/Image_Low_Dpi/album_art.png";
}

