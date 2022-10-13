#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QDebug>
#include <QString>
#include<cmath>
#include<atomic>
#include <linux/types.h>
#include <mutex>

class parser
{
public:
    explicit parser(QString file_name);
    ~parser();
    void parsing();
    void RTM2(QStringList& lst,QString& str);
    void RTM4(QStringList& lst,QString& str);
//    void RTM2_reserve(QStringList lst,QString str);
//    void RTM4_reserve(QStringList lst,QString str);


    std::mutex mutex;

    bool RTM2_is_updaded();
    bool RTM4_is_updaded();
    bool RTM2_reserve_is_updaded();
    bool RTM4_reserve_is_updaded();

    struct word
    {
        __u8 addr8;
        __u32 data32;
    };

    QVector<word>& getData_RTM2();
    QVector<word>& getData_RTM4();
    QVector<word>& getData_RTM2_reserve();
    QVector<word>& getData_RTM4_reserve();

private:

    bool is_reserve_4 = false;
    bool is_reserve_2 = false;
    std::atomic<bool> RTM2_update;
    std::atomic<bool> RTM4_update;
    std::atomic<bool> RTM2_reserve_update;
    std::atomic<bool> RTM4_reserve_update;

    QFile file;
    QString file_name;
    QString addres , data,string;

    QVector<word> vec_RTM2;
    QVector<word> vec_RTM4;
    QVector<word> vec_RTM2_res;
    QVector<word> vec_RTM4_res;

    __u8 addr8 = 0;
    __u32 data32 = 0;

    QVector<__u32> vec ;


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

    bool OpenFile(QString file_name);

};

#endif // PARSER_H
