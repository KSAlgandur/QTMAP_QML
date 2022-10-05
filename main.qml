/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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

import QtQuick 2.7
import QtQuick.Window 2.2
import QtLocation 5.8
import QtPositioning 5.6
import QtQuick.Controls 2.1
import MyCustomClass 1.0
import QtQuick.Layouts 1.3

Window {

    property double oldLat: 55.758636
    property double oldLng: 37.622504



    Movement{
        id: myclass
    }


    Item
       {
           id:coords
           property real lat_new: 55.758636; //55.775100
           property real lon_new: 37.622504; //37.506523
           property real alt_new: 0;
           property real  head_new: 0;
           property real roll_new: 0;
           property real pitch_new: 0
           property real vtr_new: 0;

       }

    Connections{

        target: Movement2
        onSendToQml:
        {
            coords.lat_new = Movement2.mystr["lat"]
            coords.lon_new = Movement2.mystr["lng"]


        }



    }



    id: win
    visible: true
    width: 1800
    height: 1200
    title: "ARINC TEST"






    Map {
        id: map
        anchors.fill: parent
        activeMapType: map.supportedMapTypes[1]
        zoomLevel: 9
        center: QtPositioning.coordinate(oldLat, oldLng)
        plugin: Plugin {
            name: 'osm';
            PluginParameter {
                name: 'osm.mapping.offline.directory'
                value: ':/offline_tiles/'
            }
        }



        MapQuickItem {
                       id: marker2
                      // visible: false
//                       anchorPoint.x: image.width/2
//                       anchorPoint.y: image.height/2


                       coordinate {
                           latitude:  coords.lat_new//myclass.mystr["lat"]
                           longitude: coords.lon_new //myclass.mystr["lng"]
                       }
                       sourceItem: Image { id: image2; x: -20;  y:-30 ; sourceSize.height: 80; sourceSize.width: 70;  source: "qrc:/Images/drone2.png"}




   }

        MapPolyline {
                id: line
                visible: false
                line.width: 4
                line.color: 'green'
//                 layer.enabled: false
                opacity: 0.5
                path: [
                    { latitude: oldLat, longitude: oldLng},
                    { latitude: myclass.mystr["lat"] ,longitude:myclass.mystr["lng"] },

                ]
            }



        Rectangle{

            id: rect
            visible: true
            color: "grey"
            opacity: 0.7
            width: 600; height: 400
            anchors.bottom: parent.bottom
            radius: 11



            Text {
                id: topText
                text: qsTr("Навигационные данные")
                font.pointSize: 16
                 font.family: "Helvetica"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }



            Column {
                              id: column
                              anchors { fill: parent; margins: 30;}

                              Text { font.pointSize: 12;text: 'Широта: ' + coords.lat_new.toFixed(3)+ " град." }
                              Text { font.pointSize: 12;text: 'Долгота: ' + myclass.mystr["lng"].toFixed(3)+ " град." }
                              Text { font.pointSize: 12;text: 'Азимут: ' + myclass.mystr["angle"].toFixed(0) + " град."}
                              Text { font.pointSize: 12;text: 'Скорость: ' + myclass.mystr["v"].toFixed(3)*100 + " м/c"}

                          }




            Button{
            id: startButton;

            text: "Старт"
            width: 30
            anchors.top: Rectangle.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right


            anchors.margins: 30
            anchors.rightMargin: 100;
            anchors.leftMargin: 100;

            checkable: false
            checked: false


            onClicked: {
               if(startButton.checked == false)
               {

                   myclass.on_btnGo_clicked()
                   startButton.checkable = true

                   marker2.visible = true
                   line.visible = true


                   startButton.text = "Стоп"
                   console.log("Start simulation")
                   startButton.checked == true

               }
               else if(startButton.checked == true)
               {
                   myclass.on_btnGo_clicked()
                   console.log("Stop simulation")
                   startButton.text = "Старт"
                   startButton.checked == false

               }




            }


            }


}




 function setCenter(lat,lng)
 {
     map.pan(oldLat - lat, oldLng - lng)
     oldLat = lat
     oldLng = lng
 }







 function addMarker(lat, lng) {
       var item = marker1.createObject(window, {coordinate: QtPositioning.coordinate(lat, lng)})
       mapView.addMapItem(item)
    }






    }

}

