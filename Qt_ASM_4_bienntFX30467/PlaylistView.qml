import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1

Drawer {
    id: drawerId
    property alias mediaPlaylist: mediaPlaylistId
    interactive: false
    modal: false
    background: Rectangle {
        id: playList_bg
        anchors.fill: parent
        color: "transparent"
    }
    ListView{
        id: mediaPlaylistId
        anchors.fill: parent
        model: playerModel
        clip: true
        spacing: 2
        delegate: MouseArea{
            property variant myData: model
            implicitWidth: playlistItemId.width
            implicitHeight: playlistItemId.height
            Image{
                id: playlistItemId
                width: 482
                height: 138
                source: "qrc:/Image_Low_Dpi/playlist.png"
                opacity: 0.5
            }

            Text{
                id: textPlaylistItemId
                text: tenbaihat
                anchors.fill: parent
                anchors.leftMargin: 50
                verticalAlignment: Text.AlignVCenter
                color: "white"
                font.pointSize: 20
            }

            onClicked: {
                mediaPlaylistId.currentIndex = index
            }

            onPressed: {
                playlistItemId.source = "qrc:/Image_Low_Dpi/hold.png"
            }

            onReleased: {
                playlistItemId.source = "qrc:/Image_Low_Dpi/playlist.png"
            }
            onCanceled: {
                playlistItemId.source = "qrc:/Image_Low_Dpi/playlist.png"
            }
        }
        highlight: Image{
            source: "qrc:/Image_Low_Dpi/playlist_item.png"
            Image{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/Image_Low_Dpi/playing.png"
            }
        }
        ScrollBar.vertical: ScrollBar {
            parent: mediaPlaylistId.parent
            anchors.top: mediaPlaylistId.top
            anchors.left: mediaPlaylistId.right
            anchors.bottom: mediaPlaylistId.bottom
        }
        onCurrentItemChanged: {
            player.playlist.setCurrentIndex(currentIndex)
            player.play()
        }
    }
    Connections{
        target: player.playlist
        onCurrentIndexChanged: {
            mediaPlaylistId.currentIndex = player.playlist.currentIndex
        }
    }
}
