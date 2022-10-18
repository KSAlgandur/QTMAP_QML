#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include <QVariantMap>
#include <coefficients.h>
#include "po_struct.h"
#include <linux/types.h>

using namespace brlk;
typedef struct brlk::apu::po::out::Ons ons;
typedef struct brlk::apu::po::out::Sns sns;



class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator();
    struct word
    {
        __u8 addr8;
        __u32 data32;
    };

    void generate();
    QVector<word>& get_gnData_RTM2();
    QVector<word>& get_gnData_RTM4();
    __u32 generate_new_data();


private:

    QVector<word> vec_genRTM2;
    QVector<word> vec_genRTM4;

    __u8 addr8 = 0;
    __u32 data32 = 0;



    QTimer *timer;
    QTimer *timer2;

    ons rtm2_str;
    sns rtm4_str;

 int ToDecimal(int octal)
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

 int ToOctal(int decimal)
    {
        int remainder;
            long octal = 0, i = 1;

            while(decimal != 0) {
                remainder = decimal%8;
                decimal = decimal/8;
                octal = octal + (remainder*i);
                i = i*10;
            }
            return octal;
    }

};

#endif // GENERATOR_H
