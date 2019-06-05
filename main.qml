import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id:mainWindow
    visible: true
    width: 480
    height: 873
    property int baseButtonHeight: 40 * dpiToPixelValue
    property int normalFontSize: 15 * dpiToPixelValue
    property int bigFontSize: 20 * dpiToPixelValue
    property int extraFontSize: 24 * dpiToPixelValue
    property int smallFontSize: 12 * dpiToPixelValue
    property color baseColor: "#FE1A2B"
    property color baseSelectingColor: "#007ACC"
    property color baseTextColor: "white"
    property bool isLoggedIn: false
    property bool isAutoLogin: true
    Setting {
        id: settingQML
    }
    Rectangle{
        id:recHeader
        height: baseButtonHeight
        width: parent.width
        anchors.top: parent.top
        visible: mainStackView.visible
        color: baseColor
        Rectangle{
            id:recHeaderIcon
            width: height
            height: parent.height
            anchors.left: parent.left
            color: baseColor
            Image {
                source: mainStackView.depth > 2 ? "qrc:/resource/LeftArrow_White.png" : "qrc:/resource/Home_White.png"
                height: parent.height / 2
                fillMode: Image.PreserveAspectFit
                anchors.left: parent.left
                anchors.leftMargin: 5 * dpiToPixelValue
                y:parent.height / 2 - height / 2
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(mainStackView.depth > 2){
                        mainStackView.pop()
                    }else{
                        mainStackView.pop(null)
                    }
                    if(mainStackView.depth < 2){
                        appTitle = "Sporty"
                    }
                }
            }
        }
        Text {
            id: name
            text: "appTitle"
            anchors.centerIn: parent
            width: parent.width - recHeaderIcon.width
            x:recHeaderIcon.width
            font.pixelSize: extraFontSize
            color: "white"
            font.bold:true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            height: parent.height
            elide: Text.ElideRight
        }
    }
    Rectangle{
        id:recSplash
        anchors.fill: parent
        color: "white"
        Image {
            source: "qrc:/resource/logo.png"
            width: parent.width / 2
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
    }
    StackView {
        id: mainStackView
        width: parent.width
        height: parent.height - recHeader.height// - recFooter.height
        y:recHeader.height
        visible: false
    }

//    Rectangle{
//        id:recFooter
//        height: baseButtonHeight
//        width: parent.width
//        anchors.bottom: parent.bottom
//        visible: mainStackView.visible
//        Rectangle{
//            width: parent.width
//            height: 2
//            anchors.top:parent.top
//            gradient: Gradient {
//                GradientStop {
//                  position: 0.0
//                  color: "#00000000"
//                }
//                GradientStop {
//                  position: 1.0
//                  color: "#FF000000"
//                }
//              }
//        }
//    }
    Timer{
        id: tmSplashTimer
        interval: 1000
        running: false
        repeat: false
        onTriggered: {
            waitingDialog.show("Starting application")
            if(appManager.autoLogin() === false){
                if(appManager.startupApplication() === true){
                    mainStackView.visible = true
                    mainStackView.push("qrc:/ScreenLogin.qml")
                }
            }else{
                mainStackView.visible = true
                mainStackView.push("qrc:/ScreenHome.qml")
                isLoggedIn = true
            }
            isAutoLogin = false;
            recSplash.visible = false
            waitingDialog.close()
        }
    }

    Component.onCompleted: {
        tmSplashTimer.start()
    }
    Rectangle{
        id: bgMessageDialog
        anchors.fill: parent
        visible: waitingDialog.visible || messageDialog.visible
        color: "black"
        opacity: 0.5
        MouseArea{
            enabled: parent.visible
            anchors.fill: parent
            onClicked: {
                console.log("Screen Locked")
            }
        }
    }

    Rectangle{
        id:waitingDialog
        function show(string){
            txtWaitingMessage.text=string
            visible = true
        }

        function close(){
            waitingDialog.visible = false
        }
        anchors.centerIn: parent
        radius: 2
        width: Math.max(txtWaitingMessage.width + 20 * dpiToPixelValue, 100 * dpiToPixelValue)
        color: "white"
        visible: false

        Text {
            id: txtWaitingMessage
            padding: 6
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            x:parent.width / 2 - width / 2
            anchors.top :imgWaitingIndicator.bottom
            font.pixelSize: normalFontSize
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
        Image {
            id: imgWaitingIndicator
            source: "qrc:/resource/spinner.png"
            width: 40 * dpiToPixelValue
            height: width
            fillMode: Image.PreserveAspectFit
            x:parent.width / 2 - width / 2
            anchors.centerIn: parent
        }
        RotationAnimator {
            target: imgWaitingIndicator;
            from: 0;
            to: 360;
            duration: 1000
            running: waitingDialog.visible
            direction: RotationAnimator.Clockwise
            loops: Animation.Infinite
        }
        height: txtWaitingMessage.height + rectLoginMessageRow.height + 20 * dpiToPixelValue + imgWaitingIndicator.height
    }

    Rectangle{
        id: messageDialog
        signal closed

        function show(string){
            txtLoginMessageContent.text=string
            visible = true
        }

        function close(){
            messageDialog.visible = false
            closed()
        }
        anchors.centerIn: parent
        radius: 10 * dpiToPixelValue
        width: parent.width - 20 * dpiToPixelValue
        color: "white"
        visible: false
        Text {
            id: txtLoginMessageContent
            padding: 6
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            x:parent.width / 2 - width / 2
            anchors.top :parent.top
            font.pixelSize: normalFontSize
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            width: parent.width
        }
        Rectangle{
            id:rectLoginMessageRow
            anchors.top:txtLoginMessageContent.bottom
            anchors.topMargin: 5
            color: "lightgray"
            width: parent.width
            height: 1
        }
        Button{
            id:btnOK
            text:"OK"
            font.pixelSize: normalFontSize
            width: parent.width / 2
            height: baseButtonHeight
            padding: 0
            x: parent.width / 2 - width / 2
            anchors.top:rectLoginMessageRow.bottom
            background: Rectangle{
                anchors.fill: parent
                color: "transparent"
            }
            onClicked: {
                messageDialog.close()
            }
        }
        height: txtLoginMessageContent.height + btnOK.height + rectLoginMessageRow.height
    }



}
