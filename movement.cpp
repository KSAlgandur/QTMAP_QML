#include "movement.h"

Movement::Movement(QObject *parent) : QObject(parent)/*,m_x(55.758636), m_y(37.622504)*/
{

    // начальное положение тела
    r.x = m_x = 55.758636;
    r.y = m_y = 37.622504;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}

QString Movement::getCoord()
{
    return QString("Full information from Structure %1").arg(m_x);
}

double Movement::new_XCoord()
{
    qDebug() << __FUNCTION__;

    return m_x;
}

double Movement::new_YCoord()
{
    qDebug() << __FUNCTION__;

    return m_y;
}

void Movement::move()
{
    //qDebug() <<"(angle) : " <<angle;


    v.x = v0*cos(angle);
    v.y = v0*sin(angle);

     //qDebug() <<"sin(angle):  " <<sin(angle);

    r.x += v.x*dt;
    r.y += v.y*dt;
//    r.x = 0;
//    r.y = 0;



    setNew_XCoord(r.x);
    setNew_YCoord(r.y);



}

void Movement::setNew_XCoord(double ipr)
{
     qDebug() <<  "new Lat: " << ipr;

     if(m_x == ipr)
         return;

     m_x = ipr;
     emit new_XCoordChanged(m_x);

}

void Movement::setNew_YCoord(double ipr)
{



    if(m_y == ipr)
        return;

    qDebug() << "new Lng: " << ipr;;

    m_y = ipr;
    emit new_YCoordChanged(m_y);


}




