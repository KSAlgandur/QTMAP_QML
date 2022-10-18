#include "generator.h"

Generator::Generator(QObject *parent) : QObject(parent)
{


}

Generator::~Generator()
{

}

void Generator::generate()
{

   vec_genRTM2.clear();
   vec_genRTM4.clear();

   word w2;
   word w4;

   rtm2_str.Head           = generate_new_data();
   w2.data32               = rtm2_str.Head;
   w2.addr8                = ToDecimal(255);
   vec_genRTM2.append(w2);

   rtm2_str.Roll           = generate_new_data();
   w2.data32               = rtm2_str.Roll;
   w2.addr8                = ToDecimal(255);
   vec_genRTM2.append(w2);

   rtm2_str.Pitch          = generate_new_data();
   w2.data32               = rtm2_str.Pitch;
   w2.addr8                = ToDecimal(225);
   vec_genRTM2.append(w2);

   rtm2_str.Vn             = generate_new_data();
   w2.data32               = rtm2_str.Vn;
   w2.addr8                = ToDecimal(245);
   vec_genRTM2.append(w2);

   rtm2_str.Ve             = generate_new_data();
   w2.data32               = rtm2_str.Ve;
   w2.addr8                = ToDecimal(215);
   vec_genRTM2.append(w2);

   rtm2_str.Vup            = generate_new_data();
   w2.data32               = rtm2_str.Vup;
   w2.addr8                = ToDecimal(255);
   vec_genRTM2.append(w2);

   rtm2_str.Latitude       = generate_new_data();
   w2.data32               = rtm2_str.Latitude;
   w2.addr8                = ToDecimal(214);
   vec_genRTM2.append(w2);

   rtm2_str.Longitude      = generate_new_data();
   w2.data32               = rtm2_str.Longitude;
   w2.addr8                = ToDecimal(251);
   vec_genRTM2.append(w2);

   rtm2_str.AltitudeBar    = generate_new_data();
   w2.data32               = rtm2_str.AltitudeBar;
   w2.addr8                = ToDecimal(222);
   vec_genRTM2.append(w2);

   rtm2_str.AltitudeRatio  = generate_new_data();
   w2.data32               = rtm2_str.AltitudeRatio;
   w2.addr8                = ToDecimal(227);
   vec_genRTM2.append(w2);

 //=============================================================================


   rtm4_str.Latitude_SNS   = generate_new_data();
   w4.data32               = rtm4_str.Latitude_SNS;
   w4.addr8                = ToDecimal(319);
   vec_genRTM4.append(w4);

   rtm4_str.Longitude_SNS  = generate_new_data();
   w4.data32               = rtm4_str.Longitude_SNS;
   w4.addr8                = ToDecimal(312);
   vec_genRTM4.append(w4);


   rtm4_str.Altitude_SNS   = generate_new_data();
   w4.data32               = rtm4_str.Altitude_SNS;
   w4.addr8                = ToDecimal(316);
   vec_genRTM4.append(w4);


   rtm4_str.Vn             = generate_new_data();
   w4.data32               = rtm4_str.Vn;
   w4.addr8                = ToDecimal(326);
   vec_genRTM4.append(w4);

   rtm4_str.Ve             = generate_new_data();
   w4.data32               = rtm4_str.Ve;
   w4.addr8                = ToDecimal(322);
   vec_genRTM4.append(w4);

   rtm4_str.Vh             = generate_new_data();
   w4.data32               = rtm4_str.Vh;
   w4.addr8                = ToDecimal(311);
   vec_genRTM4.append(w4);

   rtm4_str.Course_SNS     = generate_new_data();
   w4.data32               = rtm4_str.Course_SNS;
   w4.addr8                = ToDecimal(325);
   vec_genRTM4.append(w4);

   rtm4_str.HDOP           = generate_new_data();
   w4.data32               = rtm4_str.HDOP ;
   w4.addr8                = ToDecimal(323);
   vec_genRTM4.append(w4);

   rtm4_str.NaviStatus     = generate_new_data();
   w4.data32               = rtm4_str.NaviStatus ;
   w4.addr8                = ToDecimal(312);
   vec_genRTM4.append(w4);


}

QVector<Generator::word> &Generator::get_gnData_RTM2()
{
    return vec_genRTM2;
}
QVector<Generator::word> &Generator::get_gnData_RTM4()
{
    return vec_genRTM4;
}

 __u32 Generator::generate_new_data()
{
     __u32 new_data;
     new_data = QRandomGenerator::global()->bounded(0,500);
     return new_data;
}
