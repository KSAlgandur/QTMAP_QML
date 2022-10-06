#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include <QVariantMap>
#include <iostream>


struct Navigation{
    Q_GADGET
    Q_PROPERTY(double lat MEMBER m_lat)
    Q_PROPERTY(double lng MEMBER m_lng)
    Q_PROPERTY(double angle MEMBER m_angle) // _ КУРС
    Q_PROPERTY(double v MEMBER m_v) // _СКОРОСТЬ
    Q_PROPERTY(double roll MEMBER m_roll) //_КРЕН
    Q_PROPERTY(double pitch MEMBER m_pitch) //_ ТАНГАЖ
    Q_PROPERTY(double h MEMBER m_h) //_ ТАНГА

public:
    double m_lat;
    double m_lng;
    double m_angle;
    double m_v;
    double m_roll;
    double m_pitch;
    double m_h;


};Q_DECLARE_METATYPE(Navigation)



 struct vector {

    //explicit vector(QObject *parent = nullptr);
    double x;
    double y;

};


class Movement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double new_XCoord READ new_XCoord WRITE setNew_XCoord NOTIFY new_XCoordChanged)
    Q_PROPERTY(double new_YCoord READ new_YCoord WRITE setNew_YCoord NOTIFY new_XCoordChanged)

    // Отправка структуры
    Q_PROPERTY(QVariantMap mystr READ getMyStruct WRITE setMyStruct NOTIFY myStructChanged)


public:

//     double m_x = 55.758636;
//     double m_y = 37.622504;


    explicit Movement(QObject *parent = nullptr);   

    double new_XCoord();
    double new_YCoord();
    void setNew_XCoord(double ipr);
    void setNew_YCoord(double ipr);


    QVariantMap getMyStruct() const;
    void setMyStruct(QVariantMap myStruct);

    QVariantMap myStructToQVariantMap(Navigation const &myStruct) const;
    Navigation myStructFromQVariantMap(QVariantMap const &vm) const;
    bool myStructEqual(Navigation const &myStruct1, Navigation const &myStruct2);




signals:

  void new_XCoordChanged(double m_x);
  void new_YCoordChanged(double m_y);
  void myStructChanged(QVariantMap nav_data);



public slots:

    void on_btnGo_clicked();

private slots:


void move();
void generate_new_angle();




private:
    QTimer *timer;
    QTimer *timer2;
    double dt = 0.0003; // временной шаг
    double v0 = 0.575; // начальная скорость
    double angle = 220.0/180.0*M_PI; // начальное направление скорости
    vector v; // вектор скорости
    vector r; // радиус-вектор
    Navigation m_nav;
    bool IsRun = false;


    double m_x = 0;
    double m_y = 0;

    double speed_imit = 0;


};

#endif // MOVEMENT_H
