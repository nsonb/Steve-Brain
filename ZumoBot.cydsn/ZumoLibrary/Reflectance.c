/**
 * @file    Reflectance.c
 * @brief   Basic methods for operating reflectance sensor. For more details, please refer to Reflectance.h file. 
 * @details included in Zumo shield
*/
#include <project.h>
#include <stdio.h>

#include "Reflectance.h"

static volatile struct sensors_ sensors;
static volatile struct sensors_  digital_sensor_value;
static struct sensors_ threshold = { 10000, 10000, 10000, 10000};

/**
* @brief    Reflectance Sensor Interrupt Handler
* @details  Measuring each sensors' time to recognition of white or black
*/
CY_ISR(sensor_isr_handler)
{
    uint32_t statusR1 = Timer_R1_ReadStatusRegister();
    uint32_t statusR3 = Timer_R3_ReadStatusRegister();
    uint32_t statusL3 = Timer_L3_ReadStatusRegister();
    uint32_t statusL1 = Timer_L1_ReadStatusRegister();

    if(statusR1 & Timer_R1_STATUS_CAPTURE) {
        sensors.r1 = Timer_R1_ReadPeriod() - Timer_R1_ReadCapture();
    }
    else {
        sensors.r1 = Timer_R1_ReadPeriod();
    }
    
    if(statusR3 & Timer_R3_STATUS_CAPTURE) {
        sensors.r3 = Timer_R3_ReadPeriod() - Timer_R3_ReadCapture();
    }
    else {
        sensors.r3 = Timer_R3_ReadPeriod();
    }
    
    if(statusL3 & Timer_L3_STATUS_CAPTURE) {
        sensors.l3 = Timer_L3_ReadPeriod() - Timer_L3_ReadCapture();
    }
    else {
        sensors.l3 = Timer_L3_ReadPeriod();
    }
    
    if(statusL1 & Timer_L1_STATUS_CAPTURE) {
        sensors.l1 = Timer_L1_ReadPeriod() - Timer_L1_ReadCapture();
    }
    else {
        sensors.l1 = Timer_L1_ReadPeriod();
    }
    
    R1_SetDriveMode(PIN_DM_STRONG);
    R1_Write(1);
    R3_SetDriveMode(PIN_DM_STRONG);
    R3_Write(1);
    L3_SetDriveMode(PIN_DM_STRONG);
    L3_Write(1);
    L1_SetDriveMode(PIN_DM_STRONG);
    L1_Write(1);
    CyDelayUs(10);
    R1_SetDriveMode(PIN_DM_DIG_HIZ);
    R3_SetDriveMode(PIN_DM_DIG_HIZ);
    L3_SetDriveMode(PIN_DM_DIG_HIZ);
    L1_SetDriveMode(PIN_DM_DIG_HIZ);

    Timer_R1_ReadStatusRegister();
    Timer_R3_ReadStatusRegister();
    Timer_L3_ReadStatusRegister();
    Timer_L1_ReadStatusRegister();
}


/**
* @brief    Starting Reflectance Sensor
* @details 
*/
void reflectance_start()
{
    sensor_isr_StartEx(sensor_isr_handler);
    Timer_R1_Start();
    Timer_R3_Start();
    Timer_L3_Start();
    Timer_L1_Start();
}


/**
* @brief    Read reflectance sensor values
* @details
*/
void reflectance_read(struct sensors_ *values)
{
    *values = sensors;
}


/**
* @brief    Making Reflectance Sensor's period to digital
* @details
*/
void reflectance_digital(struct sensors_ *digital)
{
    //if the results of reflectance_period function is over threshold, set digital_sensor_value to 0, which means it's black
    if(sensors.l3 > threshold.l3)
        digital->l3 = 0;
    else
        digital->l3 = 1;
    
    if(sensors.l1 > threshold.l1)
        digital->l1 = 0;
    else
        digital->l1 = 1;
    
    if(sensors.r1 > threshold.r1)
        digital->r1 = 0;
    else
        digital->r1 = 1;
    
    if(sensors.r3 > threshold.r3)
        digital->r3 = 0;
    else
        digital->r3 = 1;
        
}

void reflectance_set_threshold(uint16_t l3, uint16_t l1, uint16_t r1, uint16_t r3)
{
    threshold.l3 = l3;
    threshold.l1 = l1;
    threshold.r3 = r3;
    threshold.r1 = r1;
}


