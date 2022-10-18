#ifndef PEX429_H
#define PEX429_H


#include <QObject>
#include <signal.h>
#include <stdio.h>
#include "pex429LNX.h"
#include "pex429LNXmacro.h"
#include <sys/time.h>
#include <fcntl.h>
#include <QDebug>
#include <linux/types.h>
#include <unistd.h>
#include <QString>
#include "parser.h"
#include <QTimer>
#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include "signalhandlerdispatcher.h"
#include "readparamdispatcher.h"
#include <thread>
#include "po_struct.h"
#include "generator.h"

#define	ULONG	 __u32			//unsigned long int

using namespace brlk;

class pex429 : public QObject
{
     Q_OBJECT
public:
    pex429(const char* pex_name, QObject *patent,parser& pars,Generator& gen);
    ~pex429();



    int connectToPEX();
    void send_vec (QVector<__u32> words);
     __u32 sendForArray (__u8 addr, __u32 word);

     bool timer_loop = false ;

     void sendTo_1_chanel(const QVector<parser::word>& vec_RTM2, int ch_1);
     void sendTo_2_chanel(const QVector<parser::word>& vec_RTM4, int ch_2);
     void sendTo_3_chanel(const QVector<parser::word>& vec_RTM2_res, int ch_3);
     void sendTo_4_chanel(const QVector<parser::word>& vec_RTM4_res, int ch_4);
     void Disconnect();
     void ReadDataFromPEX(int& chanel_num);
     void hINT (int signo);
     void Init();
     void sendTest(std::vector<__u32> words);
     void thread_loop_state();

     int  PEX_data_update();

     void PEX_autoData_update();

public slots:
void update(int& type);



private:
    int global_chanel_num;

    const int ch_1 = 1;
    const int ch_2 = 2;
    const int ch_3 = 3;
    const int ch_4 = 4;
    QTimer tm_pex;
    QTimer tm_read;
    parser& pars;
    Generator& gen;


    ULONG	param[256];
    int 	i1 = 0;
    long int outputParam,receivedParam;
    const char* pex_name;
    int  hARINC;
    short unsigned int Data[32768];
    unsigned short int	buff[16];
    struct sigaction action;
    struct itimerval timer;
    struct timeval start,end;
    int rj, ind1,testType;
    int testMode;

    unsigned int receivedCode;
    long int
        expectedCode
        ,outputCode
        ,numberOfINT1=0
        ,numberOfINT2=0
        ,cycleNumber=0;

    int numberSI=0
        ,numberSO=0;


    struct ArincWord
    {
      __u8  addr;
      __u32 data;
      __u16 ssm;
      __u8 bit32;

    };
    __u32 toArincWord(ArincWord &Aw);

};

#endif // PEX429_H
