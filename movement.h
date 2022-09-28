#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>


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


public:

//     double m_x = 55.758636;
//     double m_y = 37.622504;


    explicit Movement(QObject *parent = nullptr);

    Q_INVOKABLE QString getCoord();
    double new_XCoord();
    double new_YCoord();



    void setNew_XCoord(double ipr);
    void setNew_YCoord(double ipr);


signals:

  void new_XCoordChanged(double m_x);
  void new_YCoordChanged(double m_y);

private slots:


void move();




private:
    QTimer *timer;
    double dt = 0.004; // временной шаг
    double v0 = 0.5; // начальная скорость
    double angle = 220.0/180.0*M_PI; // начальное направление скорости
    vector v; // вектор скорости
    vector r; // радиус-вектор

    double m_x = 0;
    double m_y = 0;


};

#endif // MOVEMENT_H
