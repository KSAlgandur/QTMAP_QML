#ifndef QUDPSOCKETCAT_H
#define QUDPSOCKETCAT_H

#include <QtCore/QCoreApplication>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <stdint.h>
#include <QObject>
#include "po_struct.h"
#include <linux/types.h>
#include <coefficients.h>


using namespace brlk;
typedef struct brlk::apu::po::out::Ons ons;
typedef struct brlk::apu::po::out::Sns sns;


class QUdpSocketCat : public QObject
{
    Q_OBJECT
    QUdpSocket * in;
    QUdpSocket * out;
    QTimer *timer;

    int ToDecimal(int octal);

    struct word
    {
        __u8 addr8;
        __u32 data32;
    };
    word w;
    QVector<word> vec_udp;

public:
    explicit QUdpSocketCat(QObject *parent = nullptr);

    ons srt_ons;
    sns str_sns;

    void convers2Arinc(ons &out_str);
    QVector<word> get_udp_data();
    ons send_udp_str(ons &out_str);

protected slots:
    void catData ();


signals:

  void send_udp_vec(QVector<word> w);


};

#endif // QUDPSOCKETCAT_H
