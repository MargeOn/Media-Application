import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtMultimedia 5.9

Item {
    //Media Info
    Text{
        id: mediaTitleId
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 15
        anchors.leftMargin: 15
        text: playlistId.mediaPlaylist.currentItem.myData.tenbaihat
        color: "white"
        font.pointSize: 18
        onTextChanged: {
            textChangeAniId.restart()
        }
    }
    Text{
        id: singerTitleId
        anchors.top: mediaTitleId.bottom
        anchors.left: mediaTitleId.left
        text: playlistId.mediaPlaylist.currentItem.myData.tencasi
        color: "white"
        font.pointSize: 18
    }

    NumberAnimation {
        id: textChangeAniId
        targets: [mediaTitleId,singerTitleId]
        property: "opacity"
        from: 0
        to: 1
        duration: 400
        easing.type: Easing.InOutQuad
    }

    Text{
        id: musicCountId
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 15
        text: playlistId.mediaPlaylist.count
        color: "white"
        font.pointSize: 20
    }
    Image{
        id: musicImageId
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: musicCountId.left
        anchors.rightMargin: 10
        source: "qrc:/Image_Low_Dpi/music.png"
    }

    //AlbumArt
    Component{
        id: delegateId
        Item {
            width: 280; height: 280
            scale: PathView.iconScale
            Image {
                id: myIcon
                width: parent.width
                height: parent.height
                y: 15
                anchors.horizontalCenter: parent.horizontalCenter
                source: anhbaihat
            }

            MouseArea {
                anchors.fill: parent
                onClicked:{
                    album_art_viewId.currentIndex = index
                }
            }
        }
    }

    PathView{
        id: album_art_viewId
        anchors.left: parent.left
        anchors.leftMargin: (parent.width - 785)/2
        anchors.top: parent.top
        anchors.topMargin: 200
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        model: playerModel
        delegate: delegateId
        pathItemCount: 3
        path: Path{
            // Starting Point
            startX: 20
            startY: 50
            PathAttribute { name: "iconScale"; value: 0.5 }
            PathLine { x: 390; y: 50 }
            PathAttribute { name: "iconScale"; value: 1.0 }
            PathLine { x: 785; y: 50 }
            PathAttribute { name: "iconScale"; value: 0.5 }
        }
        onCurrentIndexChanged: {
            player.playlist.currentIndex = currentIndex
        }
    }

    Text{
        id: currentTimeId
        anchors.verticalCenter: progressBarId.verticalCenter
        anchors.right: progressBarId.left
        anchors.rightMargin: 15
        text: utility.getTimeInfo(player.position)
        color: "white"
        font.pointSize: 13
    }

    Slider{
        id: progressBarId
        width: 1064 - 482*playlistId.position
        anchors.verticalCenter: totalTimeId.verticalCenter
        anchors.right: totalTimeId.left
        anchors.rightMargin: 15
        from: 0
        to: player.duration
        value: player.position
        background: Rectangle {
            x: progressBarId.leftPadding
            y: progressBarId.topPadding + progressBarId.availableHeight / 2 - height / 2
            implicitWidth: 200
            implicitHeight: 4
            width: progressBarId.availableWidth
            height: implicitHeight
            radius: 2
            color: "gray"
            Rectangle {
                width: progressBarId.visualPosition * parent.width
                height: parent.height
                color: "white"
                radius: 2
            }
        }
        handle: Image {
            anchors.verticalCenter: parent.verticalCenter
            x: progressBarId.leftPadding + progressBarId.visualPosition * (progressBarId.availableWidth - width)
            y: progressBarId.topPadding + progressBarId.availableHeight / 2 - height / 2
            source: "qrc:/Image_Low_Dpi/point.png"
            Image {
                anchors.centerIn: parent
                source: "qrc:/Image_Low_Dpi/center_point.png"
            }
        }
        onMoved: {
            if (player.seekable){
                utility.seek(progressBarId.value)
            }
        }
    }

    Text{
        id: totalTimeId
        anchors.top: parent.top
        anchors.topMargin: 488
        anchors.right: parent.right
        anchors.rightMargin: 93
        text: utility.getTimeInfo(player.duration)
        color: "white"
        font.pointSize: 13
    }

    //Media control
    SwitchButton{
        id: shuffleButtonId
        anchors.top: parent.top
        anchors.topMargin: 568
        anchors.left: currentTimeId.left
        icon_on: "qrc:/Image_Low_Dpi/shuffle-1.png"
        icon_off: "qrc:/Image_Low_Dpi/shuffle.png"
        status: utility.shuffle
        onClicked: {
                utility.shuffle = !utility.shuffle
        }
    }

    ButtonControl{
        id: previousButtonId
        anchors.verticalCenter: shuffleButtonId.verticalCenter
        anchors.right: playButtonId.left
        icon_default: "qrc:/Image_Low_Dpi/prev.png"
        icon_pressed: "qrc:/Image_Low_Dpi/hold-prev.png"
        icon_released: "qrc:/Image_Low_Dpi/prev.png"
        onClicked: {
            if (shuffleButtonId.status) {
                utility.nextShuffleMedia()
            }
            else{
                utility.setPreviousMedia()
            }
        }
    }

    ButtonControl{
        id: playButtonId
        property bool isPlay: true
        anchors.horizontalCenter: progressBarId.horizontalCenter
        anchors.verticalCenter: previousButtonId.verticalCenter
        icon_default: playButtonId.isPlay ? "qrc:/Image_Low_Dpi/pause.png" : "qrc:/Image_Low_Dpi/play.png"
        icon_pressed: playButtonId.isPlay ? "qrc:/Image_Low_Dpi/hold-pause.png" : "qrc:/Image_Low_Dpi/hold-play.png"
        icon_released: playButtonId.isPlay ? "qrc:/Image_Low_Dpi/play.png" : "qrc:/Image_Low_Dpi/pause.png"
        onClicked: {
            if(isPlay){
               isPlay = !isPlay
               utility.playMedia(isPlay)

            }
            else{
                isPlay = !isPlay
                utility.playMedia(isPlay)
            }
        }
        Connections {
            target: player.playlist
            onCurrentIndexChanged:{
                playButtonId.isPlay = true
                playButtonId.source = "qrc:/Image_Low_Dpi/pause.png"
            }
        }
    }

    ButtonControl{
        id: nextButtonId
        anchors.verticalCenter: playButtonId.verticalCenter
        anchors.left: playButtonId.right
        icon_default: "qrc:/Image_Low_Dpi/next.png"
        icon_pressed: "qrc:/Image_Low_Dpi/hold-next.png"
        icon_released: "qrc:/Image_Low_Dpi/next.png"
        onClicked: {
            if (shuffleButtonId.status) {
                utility.nextShuffleMedia()
            }
            else{
                utility.setNextMedia()
            }
        }
    }

    SwitchButton{
        id: repeatButtonId
        anchors.verticalCenter: playButtonId.verticalCenter
        anchors.right: totalTimeId.right
        icon_on: "qrc:/Image_Low_Dpi/repeat1_hold.png"
        icon_off: "qrc:/Image_Low_Dpi/repeat.png"
        status: utility.loop
        onClicked: {
            utility.loop = !utility.loop
        }
    }
    // khi bai hat duoc choi cho den het bai, danh sach phat se cap nhat bai tiep theo. Nhung index cua ListView
    // va PathView chua duoc cap nhat. Ta phai ket noi voi QMediaPlaylist de lam dieu nay
    Connections{
        target: player.playlist
        onCurrentIndexChanged: {
            album_art_viewId.currentIndex = player.playlist.currentIndex
        }
    }
}
