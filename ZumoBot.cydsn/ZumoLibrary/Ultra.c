/**
 * @file    Ultra.c
 * @brief   Basic methods for operating ultrasonic sensor. For more details, please refer to Ultra.h file. 
 * @details part number: HC-SR04
*/

#include <project.h>
#include <stdio.h>
#include <Timer.h>

#define NUMBER_OF_TICKS		 2400

#include "Ultra.h"


static volatile float distance = 0;
static volatile float cent = 0;


/**
* @brief    Systick Interrupt Handler
* @details  Counting system ticks to occur trigger
*/
CY_ISR(SYS_ISR)
{
    static int cnt=0;
    cnt++;
  
    if(cnt==1)
       Trig_Write(1);           // Trigger High
    else if(cnt==100)
        Trig_Write(0);           // Trigger Low
    else if(cnt==1100)
        cnt=0;  
}


/**
* @brief    Ultra Sonic Sensor Interrupt Handler
* @details  Measuring reflecting time to decide distance between Zumobot and obstacle
*/
CY_ISR(ultra_isr_handler)
{
    uint16_t time = 0;
    Timer_Stop();
    
    Timer_ReadStatusRegister();
    
    if(!Echo_Read()) {
        time = Timer_ReadCounter();             // Read counter value of Timer
        
        distance = (float)time / 58;            // us / 58 = centimeters
        cent = 5 * (distance - 16) / 4;         // calibration for this Timer(800 kHz)
        
        Timer_WriteCounter(0xFFFF);             // Counter initialization
    }
    else {
         Timer_WriteCounter(0xFFFF);            // Counter initialization
    }
    Timer_Start();
}


/**
* @brief    Starting Ultra Sonic Sensor
* @details  
*/
void Ultra_Start()
{
    CyIntSetSysVector((SysTick_IRQn + 16), SYS_ISR);    // Map systick ISR to SYS_ISR
    SysTick_Config(NUMBER_OF_TICKS);                    // Enable Systick Timer
    ultra_isr_StartEx(ultra_isr_handler);               // Start ultra sonic interrupt
    Timer_Start();                                      // Start Timer
}

float Ultra_GetDistance(void)
{
    return cent;       
}    




