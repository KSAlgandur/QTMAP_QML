#include "movement.h"

Movement::Movement(QObject *parent) : QObject(parent)/*,m_x(55.758636), m_y(37.622504)*/
{

    // начальное положение тела
    r.x = m_x = 55.758636;
    r.y = m_y = 37.622504;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //timer->start(100);

}

void Movement::on_btnGo_clicked()
{
    IsRun = !IsRun;
    if (IsRun) {
        timer->start(100);
       qDebug() << "Запуск имитатора " << endl;


    }
    else {
        timer->stop();
        qDebug() << "Остановка имитатора " << endl;

    }

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



QVariantMap Movement::getMyStruct() const
{
    return myStructToQVariantMap(m_nav);
}

void Movement::setMyStruct(QVariantMap myStruct)
{

   // qDebug()<<"New coordinate: " << "Lat: " << myStruct["lat"].toString() <<" || "<<" Lng: " << myStruct["lng"].toString();



    emit myStructChanged(myStruct);
}

void Movement::move()
{
    //qDebug() <<"(angle) : " <<angle;


    v.x = v0*cos(angle);
    v.y = v0*sin(angle);

     //qDebug() <<"sin(angle):  " <<sin(angle);

    r.x += v.x*dt;
    r.y += v.y*dt;

    m_nav.m_angle = angle *180/M_PI ;
    m_nav.m_lat =  r.x;
    m_nav.m_lng = r.y;
    m_nav.m_v = sqrt(pow(v.x,2) + pow(v.y,2));

    setMyStruct(myStructToQVariantMap(m_nav));

//    setNew_XCoord(r.x);
//    setNew_YCoord(r.y);



}


//Взаимодействие с Мета-Структурой

QVariantMap Movement::myStructToQVariantMap(const Navigation &myStruct) const
{
    QVariantMap res;
    res.insert("lat",myStruct.m_lat);
    res.insert("lng",myStruct.m_lng);
    res.insert("angle",myStruct.m_angle);
    res.insert("v",myStruct.m_v);
    return res;
}

Navigation Movement::myStructFromQVariantMap(const QVariantMap &vm) const
{
    Navigation res;
        res.m_angle = vm.value("angle").toDouble();
        res.m_lat = vm.value("lat").toDouble();
        res.m_lng = vm.value("lng").toDouble();
        res.m_v = vm.value("v").toDouble();

        return res;
}

bool Movement::myStructEqual(const Navigation &myStruct1, const Navigation &myStruct2)
{
    if (myStruct1.m_angle != myStruct2.m_angle) return false;
       if (myStruct1.m_lat != myStruct2.m_lat) return false;
       if (myStruct1.m_lng != myStruct2.m_lng) return false;
       if (myStruct1.m_v != myStruct2.m_v) return false;
       return true;
}




