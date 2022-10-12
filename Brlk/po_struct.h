#ifndef PO_STRUCT_H
#define PO_STRUCT_H

#include <cstdint>


namespace brlk {

namespace apu {

namespace po {

const uint16_t PO_AZ_COMMAND = 0xBBDD;
const uint16_t VERSION = 0;

const uint8_t SYNC = 0xAA;

#pragma pack(push, 1)

/*!
 * \brief Заголовок пакета
 */
struct Header
{
    uint8_t sync[2];
    uint8_t len;
    uint8_t id;
    Header() {
        sync[0] = SYNC;
        sync[1] = SYNC;
    }
};

namespace out {

const uint8_t ONS_ID = 0xC0;        ///< Данные от опорной навигационной системы (ОНС)
const uint8_t SNS_ID = 0xED;        ///< Данные от СНС (из БВ в БИНС)
const uint8_t POSITION_ID = 0x4C;   ///< Заданное положение стабилизатора (из БВ в БИНС), технологический альтернативный способ задания углов положения
//const uint8_t ONS_ID = 0xC0;
//const uint8_t ONS_ID = 0xC0;
//const uint8_t ONS_ID = 0xC0;
//const uint8_t ONS_ID = 0xC0;
//const uint8_t ONS_ID = 0xC0;


/*!
 * \brief Данные от опорной навигационной системы (ОНС)
 */
struct Ons
{
    Header header;
    //data
    float Head;             ///< Курс истинный инерциальный.
    float Roll;             ///< Крен инерциальный.
    float Pitch;            ///< Тангаж инерциальный.
    float Vn;               ///< Северная составляющая скорости корректируемая.
    float Ve;               ///< Восточная составляющая скорости корректируемая.
    float Vup;              ///< Вертикальная составляющая скорости бароинерциальная.
    double Latitude;         ///< Географическая ширина корректируемая.
    double Longitude;        ///< Географическая долгота корректируемая.
    float AltitudeBar;        ///< Высота бароинерциальная.
    float AltitudeRatio;        ///< Высота корректируемая.
//    float Vtr;              ///< Скорость путевая корректируемая.
//    float Course;           ///< Угол путевой.
//    float AVx;              ///< Угловая скорость вокруг продольной оси.
//    float AVy;              ///< Угловая скорость вокруг вертикальной оси.
//    float AVz;              ///< Угловая скорость вокруг боковой оси.
//    float Ax;               ///< Продольная составляющая линейного ускорения.
//    float Ay;               ///< Вертикальная составляющая линейного ускорения.
//    float Az;               ///< Боковая составляющая линейного ускорения.
//    float Ag;               ///< Ускорение вертикальное.
    uint32_t timeUTC;       ///< Счетчик секунд, соответсвующий моменту представления параметров из настоящей таблицы
    uint16_t timer;         ///< Счетчик миллисекунд, соответсвующий моменту изменения вышеуказанных параметров
    int NaviStatus;         ///< Состояние навигационных параметров

    uint16_t crc;

    Ons() {
        header.len = sizeof (Ons) - 3;
        header.id = ONS_ID;
    }
};

/*!
 * \brief Данные от СНС crc(из БВ в БИНС)
 */
struct Sns
{
    Header header;

    double Latitude_SNS;            ///< Геодезическая широта.
    double Longitude_SNS;           ///< Геодезическая долгота.
    float Altitude_SNS;             ///< Высота БЛА над эллипсоидом.
    float Vn;                       ///< Составляющая путевой скорости. Положительное направление – вдоль меридиана
    float Ve;                       ///< Составляющая путевой скорости. Положительное направление – вдоль параллели
    float Vh;                       ///< Составляющая путевой скорости. Положительное направление – вверх
    float Course_SNS;               ///< Путевой угол. Положительное направление – по ч.с. до направления линии пути
/*    uint32_t Date;                  ///< Дата. Частота обновления 1 Гц. День указан в 5-ти мл. разрядах, месяц занимает 4 разряда, год указан в 7-ми старших разрядах
    uint32_t PPS;                   ///< Оцифровка меток времени «1с» (Московское зимнее и среднее Гринвич.). Частота обновления 1 Гц. Секунда указана в 6-ти мл. разрядах, минуты – 6 разрядов, час указан в 5–ти старших разрядах
    float dt;*/                       ///< Время текущего обновления параметров относительно МВ «1с». Частота обновления 1 Гц
    uint32_t TimerUTC;              ///< Cчетчик секунд соотвтсвующий ммоменту преждоставления параметров
    uint16_t Timer;                 ///< Cчетчик секунд соотвтсвующий ммоменту преждоставления параметров
    float HDOP;                     ///< Геометрический фактор HDOP (Horizontal Dilution of Precision)
    int16_t NaviStatus;             ///< Состояние навигационных параметров

    uint16_t crc;

    Sns() {
        header.len = sizeof (Sns) - 3;
        header.id = SNS_ID;
    }
};

/*!
 * \brief Заданное положение стабилизатора
 */
struct Position
{
    Header header;
    float Head;         ///< Курс. Азимутальная плоскость
    float Roll;         ///< Крен. Не используется. Может принимать любое значение
    float Pitch;        ///< Тангаж. Угломестная плоскость

    uint16_t crc;

    Position() {
        header.len = 15;
        header.id = 0x4C;
    }
};

/*!
 * \brief  Изменение коэффициента пользователя
 */
struct WriteParameters
{
    Header header;
    uint16_t crc;

    WriteParameters() {
        header.len = 3;
        header.id = 0x49;
    }
};

/*!
 * \brief Изменение коэффициента пользователя
 */
struct UpdateParameters
{
    Header header;

    uint32_t number;
    float value;

    uint16_t crc;

    UpdateParameters() {
        header.len = 11;
        header.id = 0x81;
    }
};

/*!
 * \brief Запрос коэффициента пользователя
 */
struct GetParameter
{
    Header header;

    uint32_t number;

    uint16_t crc;

    GetParameter() {
        header.len = 7;
        header.id = 0x82;
    }
};

/*!
 * \brief Рестарт БИНС
 */
struct RestartBins
{
    Header header;
    uint16_t crc;

    RestartBins() {
        header.len = 3;
        header.id = 0x88;
    }
};

struct DriveWriteParameter
{
    Header header;

    uint32_t drive;
    uint8_t cmd;
    uint16_t addr;
    uint32_t value;

    uint16_t crc;

    DriveWriteParameter() {
        header.len = 14;
        header.id = 0x32;
    }
};

struct DriveReadParameter
{
    Header header;

    uint32_t drive;
    uint8_t cmd;
    uint16_t addr;

    uint16_t crc;

    DriveReadParameter() {
        header.len = 10;
        header.id = 0x32;
    }
};

}

namespace in {

/*!
 * \brief Коэффициент пользования
 */
struct Parameter
{
    Header header;

    uint32_t number;
    float value;

    uint16_t crc;

    Parameter() {}
};

/*!
 * \brief Пакет угловых скоростей в приборных осях БИНС.
 */
struct Speeds
{
    Header header;

    float Wx;               ///< Угловая скорость Wx
    float Wy;               ///< Угловая скорость Wy
    float Wz;               ///< Угловая скорость Wz

    uint16_t crc;

    Speeds() {}
};

struct WriteDriveAnswer
{
    Header header;

    uint32_t drive;
    uint8_t command : 4;
    uint8_t answer : 4;
    uint16_t address;

    uint16_t crc;

    WriteDriveAnswer() {}
};

struct ReadDriveAnswer
{
    Header header;

    uint32_t drive;
    uint8_t command : 4;
    uint8_t answer : 4;
    uint16_t address;
    union {
        uint32_t uValue;
        int32_t iValue;
        float fValue;
    };

    uint16_t crc;

    ReadDriveAnswer() {}
};

/*!
 * \brief Навигационное решение, текущие углы антенны в ЗСК
 */
struct Navigation
{

    Header header;

    float AngleHead;            ///< Курс истинный БИНС
    float AngleRoll;            ///< Крен БИНС
    float AnglePitch;           ///< Тангаж БИНС
    float VelocityNorth;        ///< Северная составляющая скорости БИНС
    float VelocityEast;         ///< Восточная составляющая скорости БИНС
    float VelocityVert;         ///< Вертикальная составляющая скорости БИНС
    double Latitude;            ///< Широта БИНС
    double Longitude;           ///< Долгота БИНС
    float Altitude;             ///< Высота БИНС
    uint64_t NaviStatus;        ///< Состояние навигационных параметров БИНС
    float EPSgu;                ///< Текущее положение стабилизатора по азимуту в ЗСК
    float EPSvu;                ///< Текущее положение луча антенны по наклону в ЗСК
    uint32_t TimeUTC;           ///< Счётчик секунд навигационного решения
    uint16_t Timer;             ///< Счётчик миллисекунд навигационного решения
    uint32_t pulseUTC_s;        ///< Счётчик секунд входного сигнала синхронизации
    uint16_t pulseUTC_ms;       ///< Счётчик миллисекунд входного сигнала синхронизации

    uint16_t crc;

    Navigation() {}
};

}

#pragma pack(pop)

}

}

}

#endif // PO_STRUCT_H
