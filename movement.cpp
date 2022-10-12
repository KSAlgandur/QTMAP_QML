#include "movement.h"
boost::thread t;

Movement::Movement(QObject *parent) : QObject(parent),pars("textoout22.txt")
  ,pex("/dev/pex429_0",parent, pars)
{

    // начальное положение тела
    r.x = m_x = 55.8586;//55.758636;
    r.y = m_y = 49.1527;//37.622504;

    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(generate_new_angle()));
     //connect(timer3,SIGNAL(timeout()),&pex,SLOT(update()));

    //timerQML->start(100);
     timer2->start(9000);

     pex.connectToPEX();
     t = boost::thread(&pex429::update,&pex);
     t.detach();



}

void Movement::on_btnGo_clicked()
{
    IsRun = !IsRun;
    if (IsRun) {
        timer->start(10);
//         timer3->start(100);

       qDebug() << "Запуск имитатора " << endl;
        //pex.update();
//       t = boost::thread(&pex429::update,&pex);
//       t.detach();




    }
    else {
        timer->stop();


    }

}

void Movement::auto_gen_data()
{

  //Пока пусто//


}

void Movement::not_auto_gen_data()
{

    if(pars.RTM2_is_updaded())
    {

       qml_update(pars.getData_RTM2());
    }
    if(pars.RTM4_is_updaded())
    {

       qml_update(pars.getData_RTM4());
    }



}

void Movement::qml_update(QVector<parser::word> vec_RTM)
{

    //std:: cout <<" im here";
    for(int i  = 0 ; i < vec_RTM.size(); i ++ ){


        if(ToOctal(vec_RTM[i].addr8) == 310)
        {
            m_nav.m_lat = (double)(get_value_from_word(vec_RTM[i].data32,28,9,true)*a_c::K1)*a_c::rad2deg ; // Георграф широта

        }

        if(ToOctal(vec_RTM[i].addr8) == 311)
        {
            m_nav.m_lng = (double)(get_value_from_word(vec_RTM[i].data32,28,9,true)*a_c::K1)*a_c::rad2deg; // Геог.долгота

        }
        else if(ToOctal(vec_RTM[i].addr8) == 223)
        {

            m_nav.m_h = ((get_value_from_word(vec_RTM[i].data32,29,12,true)) * 0.5); // Высота БЛА над Элипсом

        }
        else if(ToOctal(vec_RTM[i].addr8) == 312)
        {

            m_nav.m_v = get_value_from_word(vec_RTM[i].data32,28,14,true)*a_c::K2;// Путевая скорость

        }


        else if(ToOctal(vec_RTM[i].addr8) == 314)
        {

            m_nav.m_angle = get_value_from_word(vec_RTM[i].data32,28,14,true)* a_c::K5 * a_c::rad2deg ;// Курс

        }

        else if(ToOctal(vec_RTM[i].addr8) == 325)
        {

            m_nav.m_roll = get_value_from_word(vec_RTM[i].data32,28,14,true)* a_c::K5 * a_c::rad2deg ;// Крен

        }

        if(ToOctal(vec_RTM[i].addr8) == 324)
        {
            m_nav.m_pitch = (double)(get_value_from_word(vec_RTM[i].data32,28,14,true)* a_c::K5 * a_c::rad2deg) ; // Тангаж инерциальный

        }




    }


}

bool Movement::send_sate(bool state)
{
    if(state == 0)
    {
       std::cout << "ethernet send off"<<std::endl;
       autoGen = true;
    }
    else{

        std::cout<<"ethernet send on"<<std::endl;
        autoGen = false;
    }

   return autoGen;
}



void Movement::generate_new_angle()
{
    angle =(QRandomGenerator::global()->bounded(0,360))/180.0*M_PI;;

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

    pars.parsing();

  if(autoGen)
    {
       not_auto_gen_data();

  }

  else
  {

      v.x = v0*cos(angle);
      v.y = v0*sin(angle);

      r.x += v.x*dt;
      r.y += v.y*dt;


      m_nav.m_roll  = 0.54 + (rand()%50)/8;
      m_nav.m_pitch = 12.45 + (rand()%100)/12;
      m_nav.m_angle = angle *180/M_PI;
      m_nav.m_lat   = r.x;
      m_nav.m_lng   = r.y;
      m_nav.m_v     = sqrt(pow(v.x,2) + pow(v.y,2));


          float h_counter = 1;
          speed_imit     += 0.0001;
          h_counter       = h_counter * speed_imit * 100;
          m_nav.m_h       = h_counter;


  }

   setMyStruct(myStructToQVariantMap(m_nav));

}


//Взаимодействие с Мета-Структурой

QVariantMap Movement::myStructToQVariantMap(const Navigation &myStruct) const
{
    QVariantMap res;
    res.insert("lat",myStruct.m_lat);
    res.insert("lng",myStruct.m_lng);
    res.insert("angle",myStruct.m_angle);
    res.insert("v",myStruct.m_v);
    res.insert("h",myStruct.m_h);
    res.insert("roll",myStruct.m_roll);
    res.insert("pitch",myStruct.m_pitch);
    res.insert("test",myStruct.m_test);

    return res;
}

Navigation Movement::myStructFromQVariantMap(const QVariantMap &vm) const
{
        Navigation res;
        res.m_angle  = vm.value("angle").toDouble();
        res.m_lat    = vm.value("lat").toDouble();
        res.m_lng    = vm.value("lng").toDouble();
        res.m_v      = vm.value("v").toDouble();
        res.m_h      = vm.value("h").toDouble();
        res.m_pitch  = vm.value("pitch").toDouble();
        res.m_roll   = vm.value("roll").toDouble();
        res.m_test   = vm.value("test").toDouble();

        return res;
}

bool Movement::myStructEqual(const Navigation &myStruct1, const Navigation &myStruct2)
{
       if (myStruct1.m_angle != myStruct2.m_angle) return false;
       //if (myStruct1.m_lat   != myStruct2.m_lat) return false;
       if (myStruct1.m_lng   != myStruct2.m_lng) return false;
       if (myStruct1.m_v     != myStruct2.m_v) return false;

       return true;
}



