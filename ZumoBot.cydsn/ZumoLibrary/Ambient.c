/**
 * @file Ambient.c
 * @brief basic methods of operating ambient light sensor. For more details, please refer to Ambient.h file. 
 * @details part number: APDS-9301
*/
#include "Ambient.h"


/**
* @brief    Get lux from raw value
* @details  get lux using values of Channel 0 and Channel 1
* @param    double Channel 0
* @param    double Channel 1
* @return   double return calculated value
*/
double getLux(double CH0, double CH1)
{
    double result = 0;
    double ChannelRatio = (double)CH1/CH0;
    
    if((0<ChannelRatio) && (ChannelRatio <= 0.5))
        result = (0.0304 * CH0) - (0.062 * CH0 * pow(ChannelRatio, 1.4));
    else if((0.5<ChannelRatio)&&(ChannelRatio <= 0.61))
        result = (0.0224 * CH0) - (0.031 * CH1);
    else if((0.61<ChannelRatio)&&(ChannelRatio <= 0.80))
        result = (0.0128 * CH0) - (0.0153 * CH1);
    else if((0.80<ChannelRatio)&&(ChannelRatio <= 1.30))
        result = (0.00146 * CH0) - (0.00112 * CH1);
    else 
        result = 0;

    return result;
}

