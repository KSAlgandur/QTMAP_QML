#include "qudpsocketcat.h"


int QUdpSocketCat::ToDecimal(int octal)
{
    int decimal = 0, remainder, i=0;

    while (octal != 0) {
        remainder = octal % 10;
        octal = octal / 10;
        decimal += remainder * pow(8, i);
        i++;
    }
    return decimal;
}

QUdpSocketCat::QUdpSocketCat(QObject *parent) : QObject{parent}
{
    in = new QUdpSocket(this);
    timer = new QTimer(this);

    connect (in, SIGNAL(readyRead()), this, SLOT(catData()));
    //connect(this,SIGNAL(send_udp_vec),&mov,SLOT())
    connect(timer, &QTimer::timeout, [] (){
        qDebug() << QTime::currentTime().toString()
                       << "Время прослушки канала вышло, данные не пришли ";
         qDebug() << "Рекомендуется сменить режим имитации либо устранить неполадки с адресантом";      
    }); 
}

void QUdpSocketCat::init_connection()
{
    in->bind(QHostAddress::LocalHost,10053);
    qDebug() << QTime::currentTime().toString() << "Start listening to the host";
    timer->start(5000);
}

void QUdpSocketCat::convers2Arinc(ons &out_str)
{
    w.data32 = (static_cast<__u32>(out_str.Latitude/a_c::K1/a_c::rad2deg)) << 8; // Географическая широта
    w.addr8  = ToDecimal(310);
    vec_udp.append(w);


    w.data32 = (static_cast<__u32>(out_str.Longitude/a_c::K1/a_c::rad2deg)) << 8; // Географическая долгота
    w.addr8  = ToDecimal(311);
    vec_udp.append(w);

    w.data32 = (static_cast<__u32>(out_str.AltitudeBar)) << 8;
    w.addr8  = ToDecimal(361);
    vec_udp.append(w);

    w.data32 =(static_cast<__u32>(out_str.AltitudeRatio)) << 8;
    w.addr8  = ToDecimal(236);
    vec_udp.append(w);

    w.data32 = (static_cast<__u32>(out_str.Head/a_c::K5)) << 8;
    w.addr8  = ToDecimal(314);
    vec_udp.append(w);


    w.data32 = (static_cast<__u32>(out_str.NaviStatus))<<8;
    w.addr8  = ToDecimal(270);
    vec_udp.append(w);

    w.data32 = (static_cast<__u32>(out_str .Pitch/a_c::K5 / a_c::rad2deg))<<8;
    w.addr8  = ToDecimal(324);
    vec_udp.append(w);



    w.data32 = (static_cast<__u32>(out_str.Roll/a_c::K5 / a_c::rad2deg))<<8;
    w.addr8  = ToDecimal(367);
    vec_udp.append(w);


    w.data32 = (static_cast<__u32>(out_str.Ve / a_c::K4))<<8;
    w.addr8  = ToDecimal(367);
    vec_udp.append(w);


    w.data32 = (static_cast<__u32>(out_str.Vn / a_c::K4))<<8;  ;
    w.addr8  = ToDecimal(366);
    vec_udp.append(w);



    w.data32 = (static_cast<__u32>(out_str.Vup / a_c::K4))<<8;  ;
    w.addr8  = ToDecimal(365);
    vec_udp.append(w);

    send_udp_vec();
}

QVector<my_type::word> QUdpSocketCat::get_udp_data()
{
    return vec_udp;
}

ons& QUdpSocketCat::send_udp_str(ons &out_str)
{
    return out_str;
}

QVector<my_type::word> QUdpSocketCat::send_udp_vec()
{
    return vec_udp;
}

void QUdpSocketCat::catData()
{
 while(in->hasPendingDatagrams()){
     QByteArray datagram;
     datagram.resize(in->pendingDatagramSize());
     QHostAddress sender;
     quint16 senderPort;

     in->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
     ons *out_str = reinterpret_cast<ons *>(datagram.data());

     qDebug() << QTime::currentTime().toString() << QString("Пакет получен %1:%2")
                 .arg(sender.toString()).arg(senderPort) << '\n';



         convers2Arinc(*out_str);
         send_udp_str(*out_str);

         timer->start(5000);



 }



}
