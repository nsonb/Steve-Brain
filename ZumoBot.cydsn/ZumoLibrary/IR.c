/**
 * @file IR.c
 * @brief Basic methods for operating IR receiver. For more details, please refer to IR.h file. 
 * @details part number: TSOP-2236
*/
#include "IR.h"


/**
* @brief Waiting until signal goes up
* @details continue looping before IR_receiver value becomes 1
*/
void wait_going_up()
{
    while(!IR_receiver_Read()==1);
}    


/**
* @brief Waiting until signal goes down
* @details continue looping before IR_receiver value becomes 0
*/
void wait_going_down()
{
    while(IR_receiver_Read()==1);
}


/**
* @brief Counting to signal down
* @details Measuring the time until IR_receiver value goes up
* @return int
*   - returns count time
*/
int count_downtime()
{
    int cnt =0;
    while(!IR_receiver_Read()==1)
        cnt++;
    
    return cnt;
}


/**
* @brief    Counting to signal up 
* @details  Measuring the time until IR_receiver value goes down
* @return   int
*   - returns count time
*/
int count_uptime()
{
    int cnt =0;
    while(IR_receiver_Read()==1)
        cnt++;
    
    return cnt;
}


/**
* @brief    Getting remote controller value
* @details  Getting each of the value sent by remote controller
* @return   int
    - returns hex value
*/
int get_IR()
{
    uint8 bit[33]={0};
    unsigned int val=0;
    uint t1, t2, i;
    
    wait_going_down();
    
    for(i = 0; i < 33; i++)     // loop 33times ( 1bit - Start bit, 32bits - Databit)
    {
        t1 = 0;
        t2 = 0;
        
        t1 = count_downtime();
        t2 = count_uptime();
        
        // If up time is longer than down time, value of the bit becomes 1
        if(t2 > t1)
            bit[i]=1;
        else
            bit[i]=0; 
    } 
   
    /* // If you want to see binary value
    int cnt;
    for(cnt=0; cnt<33; cnt++)
        printf("%d ",bit[cnt]);
    printf("\r\n\n");
    */
   
    // compress bits to single int, ignore start bit

    for( i=0; i<32; i++)
        val |= bit[i+1] << i;
    
    return val;
}