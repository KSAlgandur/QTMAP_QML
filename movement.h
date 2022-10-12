#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <QThread>

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include <QVariantMap>
#include <iostream>
#include <parser.h>
#include <QString>
#include <pex429.h>
#include <coefficients.h>

struct Navigation{
    Q_GADGET
    Q_PROPERTY(double lat MEMBER m_lat)
    Q_PROPERTY(double lng MEMBER m_lng)
    Q_PROPERTY(double angle MEMBER m_angle) // _ КУРС
    Q_PROPERTY(double v MEMBER m_v) // _СКОРОСТЬ
    Q_PROPERTY(double roll MEMBER m_roll) //_КРЕН
    Q_PROPERTY(double pitch MEMBER m_pitch) //_ ТАНГАЖ
    Q_PROPERTY(double h MEMBER m_h) //_ ТАНГА
    Q_PROPERTY(double test MEMBER m_test) //_ teст

public:
    double m_lat;
    double m_lng;
    double m_angle;
    double m_v;
    double m_roll;
    double m_pitch;
    double m_h;
    double m_test;

};Q_DECLARE_METATYPE(Navigation)



 struct vector {

    //explicit vector(QObject *parent = nullptr);
    double x;
    double y;

};


class Movement : public QObject
{
    Q_OBJECT

    // Отправка структуры
    Q_PROPERTY(QVariantMap mystr READ getMyStruct WRITE setMyStruct NOTIFY myStructChanged)


public:

//     double m_x = 55.758636;
//     double m_y = 37.622504;


    explicit Movement(QObject *parent = nullptr);   




    QVariantMap getMyStruct() const;
    void setMyStruct(QVariantMap myStruct);

    QVariantMap myStructToQVariantMap(Navigation const &myStruct) const;
    Navigation myStructFromQVariantMap(QVariantMap const &vm) const;
    bool myStructEqual(Navigation const &myStruct1, Navigation const &myStruct2);



signals:


  void myStructChanged(QVariantMap nav_data);

   void checkedChanged();




public slots:

    void on_btnGo_clicked();
    void auto_gen_data();
    void not_auto_gen_data();
    void qml_update(QVector<parser::word> vec_RTM);
    bool send_sate(bool state);




private slots:

void move();
void generate_new_angle();


private:
    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;
    double dt = 0.00003; // временной шаг
    double v0 = 0.575; // начальная скорость
    double angle = 220.0/180.0*M_PI; // начальное направление скорости
    vector v; // вектор скорости
    vector r; // радиус-вектор
    Navigation m_nav;
    bool IsRun = false;

    QThread* thread = new QThread;

    parser pars;
    pex429 pex;

    double m_x = 0;
    double m_y = 0;

    double speed_imit = 0;
    bool autoGen = false;



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

    static uint32_t get_data_from_word(uint32_t word, uint32_t first, uint32_t last)
    {

        uint32_t mask1 = 0xffffff;
        uint32_t mask2 = 0xffffff;
        mask1 = mask1 << (last-9);
        mask2 = mask2 >> (32-first);
        uint32_t mask = mask1 & mask2;
        return (word & mask)>>(last-9);
    }
    static float get_value_from_word(uint32_t word, uint32_t first, uint32_t last, bool sign) //first - 29 last - 11 // sign - Диапазон изменения параметра, если '-' - false

{
    if(sign ==false)
        return (float)(get_data_from_word(word, first, last));
    else
    {
        uint32_t sign = (word>>20)&0x1;
        if(sign == 1)
        {
            word = ~word;
            return -(float)(get_data_from_word(word,first,last));
        }
        else return (float)(get_data_from_word(word,first,last));
    }


}


};

#endif // MOVEMENT_H
