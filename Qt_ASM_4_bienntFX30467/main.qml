import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.8

ApplicationWindow {
    id: root
    visible: true
    width: 1366
    height: 768
    visibility: "FullScreen"
    //minimumWidth: 1366
    //maximumWidth: 1366
    //minimumHeight: 768
    //maximumHeight: 768
    title: qsTr("MAIN_PROJECT") + translator.emptyString

    //Backgroud of Application
    Image {
        id: backgroudId
        anchors.fill: parent
        source: "qrc:/Image_Low_Dpi/background.png"
    }

    // Header
    AppHeader{
        id: appHeaderId
        width: root.width
        height: 100
        playlistButtonStatus: playlistId.visible
        onClickPlaylistButton: {
            if(playlistId.visible){
                playlistId.close()
            }
            else{
                playlistId.open()
            }
        }
    }

    //Playlist
    PlaylistView{
        id: playlistId
        y: appHeaderId.height
        width: 482
        height: root.height - 100
    }

    //Media Info
    MediaInfoControl{
        id: mediaInfoControlId
        property alias album_art: playlistId.mediaPlaylist
        anchors.top: appHeaderId.bottom
        anchors.right: parent.right
        width: 1366 - 482*playlistId.position
        height: 668
    }
}

