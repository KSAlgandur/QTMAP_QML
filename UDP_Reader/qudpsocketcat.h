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
#include <data_types.h>


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

    QVector<my_type::word> vec_udp;
    my_type::word w;

public:
    explicit QUdpSocketCat(QObject *parent = nullptr);

    ons srt_ons;
    sns str_sns;

    ons *out_str;

    void init_connection();
    void convers2Arinc(ons &out_str);
    QVector<my_type::word> get_udp_data();
    ons& send_udp_str();
    QVector<my_type::word> send_udp_vec();

protected slots:
    void catData ();



};

#endif // QUDPSOCKETCAT_H
