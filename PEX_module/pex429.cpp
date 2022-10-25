#include "pex429.h"
#include <chrono>
#include <thread>



pex429::pex429(const char* pex_name,QObject *parent, parser& pars, Generator& gen, QUdpSocketCat& sock):QObject(parent),pars(pars),gen(gen),sock(sock)
{
    testMode = 1;
    this -> pex_name = pex_name;

   SignalHandlerDispatcher::setHandler(this);
}

pex429::~pex429()
{

    Disconnect();

}

//void pex429::update(int type)
//{

//  while (timer_loop == true)
//     {
//      switch (type) {
//      case 1 : {
//          int chanel_num = PEX_data_update();
//          std::this_thread::sleep_for(std::chrono::milliseconds(20));//200
//          ReadDataFromPEX(chanel_num);
//          break;
//           }

//      case 2:{

//            PEX_autoData_update();
//            std::this_thread::sleep_for(std::chrono::milliseconds(50));//200

//            break;
//         }

//      case 3:{

//          PEX_udpData_update();
//          std::this_thread::sleep_for(std::chrono::milliseconds(50));
//      }
//      default: {
//          break;
//      }

//      }
////
////        int chanel_num = PEX_data_update();
////      std::this_thread::sleep_for(std::chrono::milliseconds(1));//200
////        ReadDataFromPEX(chanel_num);
////   }

//  }
//}

int pex429::connectToPEX()
{
   hARINC=open("/dev/pex429_0",0);
   if(hARINC==-1)
   {
       std::cout << "open error " << "\n";
       return -1;
   }

ioctl(hARINC,IOCTL_GET_SER_NUMBER ,Data);
      qDebug() << "=========================================================================\n";
      qDebug() << "                              PEX429-1 serial # = "  << Data[0x1850] <<"\n";

   ioctl(hARINC,IOCTL_RJ ,Data);
   GET_RJ_M(Data,rj);
   qDebug() << "RID =  " <<rj <<"\n";

   numberSI = (rj&0xf00)>>8;
   numberSO = (rj&0xf0)>>4;
   qDebug() <<"SI number =  " << numberSI << "\n";
   qDebug() << "SO number =  " << numberSO << "\n";

//   //3.3.3. Обслуживание прерываний

   action.sa_handler = &SignalHandlerDispatcher::saHandler;
   action.sa_flags = 0;
   sigaction(SIGUSR1, &action, NULL);
   INT_SET(hARINC,Data);

//---------------------------------------------------------------------------------------------------
  //timer_loop = true;
   Init();
//3.3.2.9. Пуск канала/ установка задания в канале .
   for (i1=1; i1<=4; i1++)
   {
       PUSK_SI(hARINC,Data,i1,0,1,1);
   }
   for (i1=2; i1<=4; i1++)
   {
       PUSK_SO(hARINC,Data,i1,0,1,0);
   }
   PUSK_SO(hARINC,Data,1,0,0,0);

return 0;
}
int pex429::PEX_data_update()
{
    pars.parsing();

    if(pars.RTM2_is_updaded())
    {
       sendTo_1_chanel(pars.getData_RTM2(),ch_1);// ------ первый канал
       global_chanel_num = ch_1;
    }
    if(pars.RTM4_is_updaded())
    {
       sendTo_2_chanel(pars.getData_RTM4(),ch_2);// ------ второй канал
       global_chanel_num = ch_2;
    }
    if(pars.RTM2_reserve_is_updaded())
    {
       sendTo_3_chanel(pars.getData_RTM2_reserve(),ch_3);// ------ третий канал
       global_chanel_num = ch_3;
    }
    if(pars.RTM4_reserve_is_updaded())
    {
       sendTo_4_chanel(pars.getData_RTM4_reserve(),ch_4);// ------ четвертый канал
       global_chanel_num = ch_4;
    }

    return global_chanel_num;
}

void pex429::PEX_autoData_update()
{
     gen.generate();

     sendTo_1_chanel(gen.get_gnData_RTM2(),ch_1);
     global_chanel_num = ch_1;
     ReadDataFromPEX(global_chanel_num);

     sendTo_2_chanel(gen.get_gnData_RTM4(),ch_2);
     global_chanel_num = ch_2;
     ReadDataFromPEX(global_chanel_num);

}

size_t pex429::send_to_pex_from_udp(QVector<my_type::word> vec_RTM)
{

    size_t vec_size = vec_RTM.size();
    for(i1 = 1; i1 < vec_RTM.count(); i1++)
    {
        __u32 arr = sendForArray(vec_RTM[i1].addr8,vec_RTM[i1].data32);
        outputParam = arr ;
        WRITE_PRM(hARINC,Data,ch_1,0,i1,outputParam);
    }

   return  vec_size;
}

void pex429::PEX_udpData_update()
{
    ReadDataFromPEX(send_to_pex_from_udp(sock.send_udp_vec()));
}
__u32 pex429::toArincWord(ArincWord &Aw)
{
   __u32 word = 0;
   word = (Aw.addr & 0xFF) | (( Aw.data & 0x1FFFFFFF) << 8) | (Aw.ssm & (0xC0000000 << 29)) | ((Aw.bit32& 0x01) << 31);
    return word;
}

__u32 pex429::sendForArray(__u8 addr, __u32 word)
{
    ArincWord arinc_word = {0,0,0,0};

    arinc_word.addr = addr;
    arinc_word.data = word;
    arinc_word.ssm = 0;
    arinc_word.bit32 = 1;

    __u32 arinc_out = toArincWord(arinc_word);

    return arinc_out;
}

 template <typename T>
 void pex429::sendTo_1_chanel(const QVector<T>& vec_RTM2,int ch_1)
{
    for(i1 = 1; i1 < vec_RTM2.count(); i1++)
    {
        __u32 arr = sendForArray(vec_RTM2[i1].addr8,vec_RTM2[i1].data32);
        outputParam = arr ;
        WRITE_PRM(hARINC,Data,ch_1,0,i1,outputParam);
    }
}
template <typename T>
void pex429::sendTo_2_chanel(const QVector<T>& vec_RTM4,int ch_2)
{

    for(i1 = 1; i1 < vec_RTM4.count(); i1++)
    {
        __u32 arr = sendForArray(vec_RTM4[i1].addr8,vec_RTM4[i1].data32);
        outputParam = arr ;
        WRITE_PRM(hARINC,Data,ch_2,0,i1,outputParam);
    }
//    qDebug() << "sendTo_2_chanel";

}

void pex429::sendTo_3_chanel(const QVector<parser::word> &vec_RTM2_res, int ch_3)
{
    for(i1 = 1; i1 < vec_RTM2_res.count(); i1++)
    {
        __u32 arr = sendForArray(vec_RTM2_res[i1].addr8,vec_RTM2_res[i1].data32);
        outputParam = arr ;
        WRITE_PRM(hARINC,Data,ch_3,0,i1,outputParam);

    }

}
void pex429::sendTo_4_chanel(const QVector<parser::word> &vec_RTM4_res, int ch_4)
{
    for(i1 = 1; i1 < vec_RTM4_res.count(); i1++)
    {
        __u32 arr = sendForArray(vec_RTM4_res[i1].addr8,vec_RTM4_res[i1].data32);
        outputParam = arr ;
        WRITE_PRM(hARINC,Data,ch_4,0,i1,outputParam);

    }

}

void pex429::Disconnect()
{
     timer_loop = false;
    //3.3.2.10. Останов канала .
    for( int i=1; i<=numberSO;i++)
        STOP_SO(hARINC,Data,i);

    for(int i=1; i<=numberSI;i++)
        STOP_SI(hARINC,Data,i);


    //t.interrupt();
    ARINC_STOP(hARINC,Data);
    close(hARINC);


}

void pex429::ReadDataFromPEX(int& chanel_num)
{
    int  chanel =  chanel_num;
    int size = 0 ;
    std::string chanel_name;
    if (chanel == 1)
    {
        size = 30;
        chanel_name = "RTM_2";
    }
    else if(chanel == 2)
    {
        size = 16;
        chanel_name = "RTM_4";
    }
    else if(chanel == 3)
    {
        size = 30;
        chanel_name = "RTM_2_reserve ";

    }
    else if(chanel == 4)
    {
        size = 16;
        chanel_name = "RTM_4_reserve ";

    }
    //3.3.2.12. Чтение параметра входного канала ПК.

  for(i1 = 0;i1 < size; i1++)
  {
      READ_PRM_SS(hARINC,Data,chanel,0,i1,receivedCode);

      std::cout  << chanel_name << "  parameter " << i1 << " :" << "received = " << receivedCode << "\n";
   }

}

void pex429::ReadDataFromPEX(size_t size)
{
    //3.3.2.12. Чтение параметра входного канала ПК.

  for(size_t i1 = 0;i1 < size; i1++)
  {
      READ_PRM_SS(hARINC,Data,1,0,i1,receivedCode);

      std::cout  << "RTM_2(UDP)" << "  parameter " << i1 << " :" << "received = " << receivedCode << "\n";
   }
}

void pex429::hINT(int signo)
{
    short unsigned int w,ii[16];
    READ_RFI_INT(hARINC,Data,w) ;

    if(w&0x1000)
    {
        do
        {
            READ_RI(hARINC,Data,ii[15],ii[14],ii[13],ii[12]
                ,ii[11],ii[10],ii[9],ii[8],ii[7],ii[6]
                ,ii[5],ii[4],ii[3],ii[2],ii[1],ii[0]);
            numberOfINT2+=ii[8];
         }while (ii[8]!=0);
    }

    if(w&0xf00)	numberOfINT1++;
    WRITE_RI(hARINC,Data);
    //std::cout << "=====Прерывание=====" << std::endl;   /////////////////////////////////////////////////////////////////////////////////////////////////////////
    return ;
}

void pex429::Init()
{
    //Подготовка кода регистра режимов в буфере обмена.
    testMode = ((testMode&1)<<3)+0x80;
    SET_RM(Data,testMode);
    //Подготовка кода регистра режимов в буфере обмена.
    SET_RF_SO_N(Data,2,2,2,2,2,2,2,2);
    SET_RF_SI_N(Data,2,2,2,2,2,2,2,2);
    //3.3.2.4. Инициализация адаптера.
    INIT_ARINC(hARINC,Data);
//    //3.3.2.7. Задание последовательности выдачи параметров
//    //выходным каналом (файловый режим).
    int i__ = 0;
    for (i1=1; i1<=4; i1++)
    {
        SET_SO_TAB_Z(Data,i1,0,i__);
        SET_SO_DAN_RC_F(hARINC,Data,i1,0,0,1,256);
    }
//    //3.3.2.8. Задание последовательности приема параметров входным каналом.
    for (i1=1; i1<=4; i1++)
    {
        SET_SI_TAB_Z(Data,i1,0,i__);
        SET_SI_TAB(hARINC,Data,i1,0);
    }

}

void pex429::sendTest(std::vector<__u32> words)
{
    for (size_t i = 1; i < words.size();i++)
    {
        outputCode= words[i];
        WRITE_PRM(hARINC,Data,1,0,i,outputCode);
    }
}

void pex429::thread_loop_state()
{
    timer_loop =! timer_loop;

}

