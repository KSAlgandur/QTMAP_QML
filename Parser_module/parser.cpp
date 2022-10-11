#include "parser.h"



parser::parser(QString file_name)
{
    OpenFile(file_name);
    RTM2_update = false;
    RTM4_update = false;
    RTM2_reserve_update = false;
    RTM4_reserve_update = false;
}

parser::~parser()
{
    file.close();
}

void parser::parsing()
{
    if(RTM2_update)
    {
        vec_RTM2.clear();
        RTM2_update = false;
         is_reserve_4 = false;
    }

//    if(RTM2_reserve_update)
//    {
//        vec_RTM2_res.clear();
//        RTM2_reserve_update = false;
//        is_reserve_2 = false;
//    }


    if(RTM4_update)
    {
        vec_RTM4.clear();
        RTM4_update = false;
         is_reserve_4 = false;
    }

//    if(RTM4_reserve_update)
//    {
//        vec_RTM4_res.clear();
//        RTM4_reserve_update = false;
//        is_reserve_4 = false;
//    }




    while(!file.atEnd())
    {

        QString str = file.readLine();
        QStringList lst = str.split(" ");
         for(int i = 0 ;i < lst.size(); i++)
         {
             if(lst.at(i) == "No.11,")
             {
                 is_reserve_2 = false;
                 RTM2(lst,str);
                 break;

             }
             else if(lst.at(i) == "No.12,")
             {
                 is_reserve_4 = false;
                 RTM4(lst,str);
                 break;
             }

//             else if(lst.at(i) == "No.15,")
//             {
//                  is_reserve_2 = true;
//                  RTM2(lst,str);
//                  break;
//             }
//             else if(lst.at(i) == "No.16,")
//             {
//                  is_reserve_4 = true;
//                  RTM4(lst,str);
//                  break;
//             }



         }

         if(RTM2_update || RTM4_update || RTM2_reserve_update || RTM4_reserve_update) // работает для чередующейся последовательности слов в файле
         {
             break;

         }
      }
}

void parser::RTM2(QStringList lst, QString str)
{
    word w;
    QVector<word> &vec = is_reserve_2 ?  vec_RTM2_res : vec_RTM2;

    if(lst.at(4) == "270o," || lst.at(4) != "236o,")
    {

       w.addr8 =  ToDecimal(str.mid(24,3).toInt(nullptr,10));
       w.data32 = str.mid(8,6).toInt(nullptr,16);
       vec.append(w);

    }


    if(vec.isEmpty()== false && vec.at(0).addr8!= 184 )//обратный перевод 184x10 = 270о//
    {
        vec.clear();
        vec.clear();
    }

    if (lst.at(4) == "236o," && vec.size() == 29)
    {
            w.addr8 = str.mid(24,3).toInt(nullptr,8);
            w.data32 = str.mid(8,6).toInt(nullptr,16);
            vec.append(w);

            if(is_reserve_2)
            {

                RTM2_reserve_update = true;
                qDebug() << " RTM2_res_update" << endl;
            }
            else
            {

                RTM2_update = true;
                //qDebug() << " RTM2_update" << endl;
            }
    }

}

void parser::RTM4(QStringList lst, QString str)
{
    word w;
    QVector<word> &vec = is_reserve_4 ?  vec_RTM4_res : vec_RTM4;

    if(lst.at(4) == "317o," || lst.at(9) != "127o,")
    {

        w.addr8 = ToDecimal(str.mid(24,3).toInt());
        w.data32 = str.mid(8,6).toInt(nullptr,16);
        vec.append(w);

    }

    if(vec.isEmpty()== false && vec.at(0).addr8!= 207 )//обратный перевод 207x10 = 317о//
    {
        vec.clear();
        vec.clear();
    }

    else if(lst.at(9) == "127o," && vec.size() == 15)
    {
        w.addr8 = ToDecimal(str.mid(24,3).toInt());
        w.data32 = str.mid(8,3).toInt(nullptr,16);
        vec.append(w);


         if(is_reserve_4)
         {

             RTM4_reserve_update = true;
             //qDebug() << " RTM4_res_update" << endl;
         }
         else
         {

             RTM4_update = true;
            // qDebug() << " RTM4_update" << endl;
         }
    }


}

bool parser::RTM2_is_updaded()
{
    return RTM2_update;
}

bool parser::RTM4_is_updaded()
{
    return RTM4_update;
}

bool parser::RTM2_reserve_is_updaded()
{
    return RTM2_reserve_update;
}

bool parser::RTM4_reserve_is_updaded()
{
    return RTM4_reserve_update;
}

// ================================================================
QVector<parser::word> &parser::getData_RTM2()
{
    return vec_RTM2;
}

QVector<parser::word> &parser::getData_RTM4()
{
    return vec_RTM4;
}

QVector<parser::word> &parser::getData_RTM2_reserve()
{
    return vec_RTM2_res;
}

QVector<parser::word> &parser::getData_RTM4_reserve()
{
    return vec_RTM4_res;
}
// ================================================================

bool parser::OpenFile(QString filename)
{
    file.setFileName(filename);


    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка при открытии файла";
        return false;
    }
    else
    {
        qDebug() << "Файл открыт";
        return true;
    }
}
