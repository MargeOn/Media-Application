import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    property alias playlistButtonStatus: playlist_button.status
    signal clickPlaylistButton
    // Header Drawer
    Image {
        id: headerId
        source: "qrc:/Image_Low_Dpi/title.png"
        SwitchButton {
            id: playlist_button
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            icon_off: "qrc:/Image_Low_Dpi/drawer.png"
            icon_on: "qrc:/Image_Low_Dpi/back.png"
            onClicked: {
               clickPlaylistButton()
            }
        }
        Text {
            anchors.left: playlist_button.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            text: qsTr("MAIN_PLAYLIST_TITLE") + translator.emptyString
            color: "white"
            font.pixelSize: 20
        }
        Text {
            id: headerTextId
            anchors.centerIn: parent
            text: qsTr("MAIN_MEDIA_PLAYER_TITLE") + translator.emptyString
            color: "white"
            font.pointSize: 28
        }
        // Cach 1: Dung ComboBox de lua chon ngon ngu
        ComboBox{
            id: comboBoxId
            width: 270
            height: 50
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            model: ListModel {
                     id: model
                     ListElement {text: "English (US)"; source: "qrc:/Image_Low_Dpi/us.png"}
                     ListElement {text: "Vietnamese"; source: "qrc:/Image_Low_Dpi/vn.png" }
                     ListElement {text: "Korean (한국인)"; source: "qrc:/Image_Low_Dpi/kr.png" }
                     ListElement {text: "Japanese (日本語)"; source: "qrc:/Image_Low_Dpi/jp.png" }
                 }
            delegate: ItemDelegate{
                width: comboBoxId.width
                contentItem: Row{
                    spacing: 10
                    Image {
                        id: flag
                        width: 50
                        height: 30
                        source: model.source
                    }
                    Text {
                        anchors.verticalCenter: flag.verticalCenter
                        text: model.text
                        font.pointSize: 14
                    }
                }
            }
            background: Rectangle{
                width: comboBoxId.width
                color: "whitesmoke"
                radius: 5
                Row{
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    Image {
                        id: flagBackground
                        width: 50
                        height: 30
                        source: model.get(comboBoxId.currentIndex).source
                    }
                    Text {
                        anchors.verticalCenter: flagBackground.verticalCenter
                        text: model.get(comboBoxId.currentIndex).text
                        font.pointSize: 15
                    }
                }
            }
            indicator: Image {
                width: 25
                height: 25
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                source: "qrc:/Image_Low_Dpi/arrow.png"
            }
            onActivated: {
                translator.selectLanguage(comboBoxId.currentIndex)
                console.log("index: " + comboBoxId.currentIndex)
            }
        }
        /*
        // Cach 2: Bo tri 4 la co thang hang de lua chon ngon ngu
        Image {
            id: us_flag
            anchors.right: vn_flag.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 30
            source: "qrc:/Image_Low_Dpi/us.png"
            Rectangle{
                id: borderUS
                width: 52
                height: 32
                anchors.verticalCenter: parent.verticalCenter
                border.color: "yellow"
                border.width: 5
                color: "transparent"
                visible: translator.currentLanguage === "us"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    translator.selectLanguage(0)
                }
            }
        }
        Image {
            id: vn_flag
            anchors.right: kr_flag.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 30
            source: "qrc:/Image_Low_Dpi/vn.png"
            Rectangle{
                id: borderVN
                width: 52
                height: 32
                anchors.verticalCenter: parent.verticalCenter
                border.color: "yellow"
                border.width: 5
                color: "transparent"
                visible: translator.currentLanguage === "vn"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    translator.selectLanguage(1)
                }
            }
        }
        Image {
            id: kr_flag
            anchors.right: jp_flag.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 30
            source: "qrc:/Image_Low_Dpi/kr.png"
            Rectangle{
                id: borderKR
                width: 52
                height: 32
                anchors.verticalCenter: parent.verticalCenter
                border.color: "yellow"
                border.width: 5
                color: "transparent"
                visible: translator.currentLanguage === "kr"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    translator.selectLanguage(2)
                }
            }
        }
        Image {
            id: jp_flag
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 30
            source: "qrc:/Image_Low_Dpi/jp.png"
            Rectangle{
                id: borderJP
                width: 52
                height: 32
                anchors.verticalCenter: parent.verticalCenter
                border.color: "yellow"
                border.width: 5
                color: "transparent"
                visible: translator.currentLanguage === "jp"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    translator.selectLanguage(3)
                }
            }
        }
        */
        /*/ Cách 3: Dùng ListView
        ListModel {
            id: modelFlag
            ListElement {language: "us"; source: "qrc:/Image_Low_Dpi/us.png"}
            ListElement {language: "vn"; source: "qrc:/Image_Low_Dpi/vn.png" }
            ListElement {language: "kr"; source: "qrc:/Image_Low_Dpi/kr.png" }
            ListElement {language: "jp"; source: "qrc:/Image_Low_Dpi/jp.png" }
        }
        ListView{
            id: flagsId
            width: 270
            height: 30
            anchors.top: headerId.top
            anchors.topMargin: 35
            anchors.right: headerId.right
            anchors.rightMargin: 20
            orientation: ListView.Horizontal
            clip: true
            spacing: 20
            model: modelFlag
            delegate: Image{
                width: 50
                height: 30
                anchors.verticalCenter: parent.verticalAlignment
                source: model.source
                Rectangle{
                    id: borderJP
                    width: 52
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                    border.color: "yellow"
                    border.width: 5
                    color: "transparent"
                    visible: translator.currentLanguage === model.language
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        translator.selectLanguage(index)
                    }
                }
            }
        }*/
    }
}
