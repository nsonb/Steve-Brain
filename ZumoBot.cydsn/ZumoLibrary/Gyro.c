/**
 * @file    Gyro.c
 * @brief   Basic methods for operating gyroscope. For more details, please refer to Gyro.h file. 
 * @details part number: L3GD20H (included in Zumo shield)
*/
#include "gyro.h"


uint16 value_convert_gyro(uint16 raw)
{
    float rate_result;
    float G_GAIN = 0.07;                        // FS = 2000 dps
  
    rate_result = (float)raw * G_GAIN;          // degrees per second for Gyroscope
    
    return rate_result;
}
