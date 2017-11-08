/**
 * @file    Magnet.c
 * @brief   Basic methods for operating magnetometer. For more details, please refer to Accel_magnet.h file. 
 * @details part number: LSM303D (simultaneously used with accelerometer and included in Zumo shield)
*/
#include "accel_magnet.h"


/**
* @brief    Heading
* @details  
* @param    double X_AXIS : X axis value
* @param    double Y_AXIS : Y axis value
*/
void heading(double X_AXIS, double Y_AXIS)          // defined as the angle between X axis and Y axis measured in a clockwise direction when viewing from the top of the device = -Z
{
    double heading;
    heading = 180 * atan2 (X_AXIS, Y_AXIS) / M_PI;
    
    if(heading < 0)
        heading += 360;
    
    //If you want to print out the value  
    //printf("heading: %7.3f \r\n", heading);
    CyDelay(250);
}
