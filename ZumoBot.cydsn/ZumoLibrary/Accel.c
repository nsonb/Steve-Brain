/**
 * @file    Accel.c
 * @brief   Basic methods for operating accelerometer. For more details, please refer to Accel_magnet.h file. 
 * @details part number: LSM303D (simultaneously used with magnetometer and included in Zumo shield)
*/
#include "accel_magnet.h"

/**
* @brief    Converting raw value
* @details  Converting raw value
* @param    uint16 X_AXIS : X axis value
* @param    uint16 Y_AXIS : Y axis value
* @param    uint16 Z_AXIS : Z axis value
*/
void value_convert_accel(uint16 X_AXIS, uint16 Y_AXIS, uint16 Z_AXIS)
{
    double AccXangle, AccYangle;
   
    AccXangle = (float) (atan2(Y_AXIS, Z_AXIS)+M_PI) *180 / M_PI;
    AccYangle = (float) (atan2(Z_AXIS, X_AXIS)+M_PI) *180 / M_PI;
    
    (void) AccXangle; // just to get rid of warning about unused variable
    (void) AccYangle; // just to get rid of warning about unused variable
  //If you want to print out the value  
  //printf("%7.3f %7.3f \r\n", AccXangle, AccYangle);
}

