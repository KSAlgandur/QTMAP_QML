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
import QtQuick.Controls.Styles 1.4


Window {

    property double oldLat: 55.8586
    property double oldLng: 49.1527
    property var anArray: []




    Item
       {
           id:coords
           property double lat_new: 55.8586; //55.775100
           property double lon_new: 49.1527; //37.506523
           property double alt_new: 0;
           property double roll_new: 0;
           property double pitch_new: 0
           property double vtr_new: 0;
           property double angle_new: 0
           property real test: 500

       }



    Movement{
        id: myclass
        onMyStructChanged:
        {
            coords.lat_new   = myclass.mystr["lat"]
            coords.lon_new   = myclass.mystr["lng"]
            coords.alt_new   = myclass.mystr["h"]
            coords.roll_new  = myclass.mystr["roll"]
            coords.pitch_new = myclass.mystr["pitch"]
            coords.vtr_new   = myclass.mystr["v"]
            coords.angle_new = myclass.mystr["angle"]
            coords.test      = myclass.mystr["test"]

            //anArray = myclass.mystr["lat"]

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
        zoomLevel: 12
        center: QtPositioning.coordinate( coords.lat_new, coords.lon_new)//coordinate(oldLat, oldLng)
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
                           latitude:  coords.lat_new
                           longitude: coords.lon_new
                       }
                       sourceItem: Image { id: image2; x: -20;  y:-30 ; sourceSize.height: 80; sourceSize.width: 70;  source: "qrc:/Images/drone2.png"}

   }
//        MapCircle {
//                center {



//                    latitude: -27.5
//                    longitude: 153.0
//                }
//                radius: 100.0
//                color: 'green'
//                border.width: 3
//            }


    // addMarker(coords.lat_new,coords.lon_new)





        MapPolyline {
                id: line
                visible: false
                line.width: 4
                line.color: 'green'
//                 layer.enabled: false
                opacity: 0.5
                path: [

                    { latitude: oldLat, longitude: oldLng},
                    { latitude: coords.lat_new ,longitude:coords.lon_new },

                ]


                Path {
                    startX: 0; startY: 100
                    PathLine { relativeX: 100; y: 100 }

                    PathLine { relativeX: 100; y: 100 }
                }

            }







        Rectangle{

            id: rect
            visible: true
            color: "grey"
            opacity: 0.8
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



                              Text { font.pointSize: 12;text: 'Широта: '   + coords.lat_new.toFixed(5)       + " град." }
                              Text { font.pointSize: 12;text: 'Долгота: '  + coords.lon_new.toFixed(5)       + " град." }
                              Text { font.pointSize: 12;text: 'Скорость: ' +(coords.vtr_new).toFixed(3) + " м/c"}
                              Text { font.pointSize: 12;text: 'Высота: '   + coords.alt_new.toFixed(3)       + " м."}
                              Text { font.pointSize: 12;text: 'Курс: '     + coords.angle_new.toFixed(3)     + " град."}
                              Text { font.pointSize: 12;text: 'Крен: '     + coords.roll_new.toFixed(3)      + " град."}
                              Text { font.pointSize: 12;text: 'Тангаж: '   + coords.pitch_new.toFixed(3)     + " град."}


                          }




                    Column{


                        anchors.right:  parent.right;
                        anchors.margins: 50
                        x:0
                        y:50

                        //anchors.right:  parent.right;

                        CheckBox {
                            id: check1
                            font.pixelSize: 15
                            font.family: "Helvetica"
                            checked: true
                            text: qsTr("Автоматическая генерация")
                            onCheckedChanged: {
                                if(checked){
                                    myclass.send_sate(1)
                                    console.log(text)
                                    check2.checked = false
                                    check3.checked = false


                                }
                            }
                        }
                        CheckBox {
                            id: check2
                            font.pixelSize: 15
                            font.family: "Helvetica"
                            text: qsTr("Генерация из файла")
                            checked:false
                            onCheckedChanged: {
                                if(checked){
                                    myclass.send_sate(2)
                                    console.log(text)
                                    check1.checked = false
                                    check3.checked = false
                                }
                            }
                        }


                        CheckBox {
                            id: check3
                            font.pixelSize: 15
                            font.family: "Helvetica"
                            text: qsTr("Приём данных по сокету")
                            checked:false
                                onCheckedChanged: {
                                    if(checked){
                                        myclass.send_sate(3)
                                        console.log(text)
                                        check1.checked = false
                                        check2.checked = false
                                    }

                                }

                           }





                    }






                    function addMarker(lat, lng) {
                         var item = marker1.createObject(window, {coordinate: QtPositioning.coordinate(lat, lng)})
                          mapView.addMapItem(item)
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
                   messages_text.text ="Start"

               }




            }


          }




            Text {
                           text: "служебные сообщения:"
                           font.family: "Helvetica"
                           font.pointSize: 12
                           color: "black"
                           anchors.top:  parent.right;
                           Layout.leftMargin: 7
                           Layout.column: 1
                           Layout.row: 8
                       }


            Rectangle{


                anchors.right:  parent.right;
                anchors.margins: 70
                x:0
                y:170



                            width: 200
                            height: 100
                            Layout.row: 9
                            color: "white"
                            opacity: 0.6
                            radius: 11
                            Text {
                                text: messages_text.elidedText
                                font.family: "Helvetica"
                            }


                                       TextMetrics {
                                           id: messages_text
                                           font.family: "Helvetica"
                                           elide: Text.ElideMiddle
                                           elideWidth: 200
                                           font.pointSize: 20
                                           text: " hello mrls "

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

