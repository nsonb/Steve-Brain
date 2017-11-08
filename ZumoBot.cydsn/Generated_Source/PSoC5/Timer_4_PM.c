/*******************************************************************************
* File Name: Timer_4_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_4.h"

static Timer_4_backupStruct Timer_4_backup;


/*******************************************************************************
* Function Name: Timer_4_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_4_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_4_SaveConfig(void) 
{
    #if (!Timer_4_UsingFixedFunction)
        Timer_4_backup.TimerUdb = Timer_4_ReadCounter();
        Timer_4_backup.InterruptMaskValue = Timer_4_STATUS_MASK;
        #if (Timer_4_UsingHWCaptureCounter)
            Timer_4_backup.TimerCaptureCounter = Timer_4_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_4_UDB_CONTROL_REG_REMOVED)
            Timer_4_backup.TimerControlRegister = Timer_4_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_4_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_4_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_4_RestoreConfig(void) 
{   
    #if (!Timer_4_UsingFixedFunction)

        Timer_4_WriteCounter(Timer_4_backup.TimerUdb);
        Timer_4_STATUS_MASK =Timer_4_backup.InterruptMaskValue;
        #if (Timer_4_UsingHWCaptureCounter)
            Timer_4_SetCaptureCount(Timer_4_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_4_UDB_CONTROL_REG_REMOVED)
            Timer_4_WriteControlRegister(Timer_4_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_4_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_4_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_4_Sleep(void) 
{
    #if(!Timer_4_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_4_CTRL_ENABLE == (Timer_4_CONTROL & Timer_4_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_4_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_4_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_4_Stop();
    Timer_4_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_4_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_4_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_4_Wakeup(void) 
{
    Timer_4_RestoreConfig();
    #if(!Timer_4_UDB_CONTROL_REG_REMOVED)
        if(Timer_4_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_4_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
