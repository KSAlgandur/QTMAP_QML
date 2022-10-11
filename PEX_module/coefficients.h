#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H
#include <qmath.h>

namespace a_c
{
 constexpr float K1  = 9.53674316e-07; // 310 311
 constexpr float K2  = 0.051;          // 312 360 315
 constexpr float K3  = 0.01562;        // 335 327 330 326
 constexpr float K4  = 0.0032;         // 366 367 365
 constexpr float K5  = 3.05175781e-05; // 314 317 320 324 325 324 325 334 226
 constexpr float K6  = 0.00391;        // 331 333 332 364
 constexpr float rad2deg = 180;
 constexpr float halfPI = M_PI_2;
}



#endif // COEFFICIENTS_H
