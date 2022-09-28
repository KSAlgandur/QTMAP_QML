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

Window {

    property double oldLat: 55.758636
    property double oldLng: 37.622504

    id: win
    visible: true
    width: 1600
    height: 720
    title: "ARINC TEST"

    Movement{
        id: myclass
    }

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



//        MapQuickItem {
//                       id: marker1
//                       anchorPoint.x: image.width/2
//                       anchorPoint.y: image.height

//                       coordinate {
//                           latitude: oldLat
//                           longitude: oldLng
//                       }
//                       sourceItem: Image { id: image; sourceSize.height: 160; sourceSize.width: 150;  source: "qrc:/Images/drone2.png"}
                   //}

        MapQuickItem {
                       id: marker2
                       anchorPoint.x: image.width
                       anchorPoint.y: image.height



                       coordinate {
                           latitude: myclass.new_XCoord
                           longitude: myclass.new_YCoord
                       }
                       sourceItem: Image { id: image2; x: -20;  y:-30 ; sourceSize.height: 80; sourceSize.width: 70;  source: "qrc:/Images/drone2.png"}
                   }




        MapPolyline {
                line.width: 4
                line.color: 'green'
//                 layer.enabled: false
                opacity: 0.5
                path: [
                    { latitude: oldLat, longitude: oldLng},
                    { latitude: myclass.new_XCoord ,longitude: myclass.new_YCoord },

                ]
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

