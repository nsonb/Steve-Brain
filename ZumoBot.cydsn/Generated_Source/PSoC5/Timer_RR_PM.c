/*******************************************************************************
* File Name: Timer_RR_PM.c
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

#include "Timer_RR.h"

static Timer_RR_backupStruct Timer_RR_backup;


/*******************************************************************************
* Function Name: Timer_RR_SaveConfig
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
*  Timer_RR_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_RR_SaveConfig(void) 
{
    #if (!Timer_RR_UsingFixedFunction)
        Timer_RR_backup.TimerUdb = Timer_RR_ReadCounter();
        Timer_RR_backup.InterruptMaskValue = Timer_RR_STATUS_MASK;
        #if (Timer_RR_UsingHWCaptureCounter)
            Timer_RR_backup.TimerCaptureCounter = Timer_RR_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_RR_UDB_CONTROL_REG_REMOVED)
            Timer_RR_backup.TimerControlRegister = Timer_RR_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_RR_RestoreConfig
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
*  Timer_RR_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_RR_RestoreConfig(void) 
{   
    #if (!Timer_RR_UsingFixedFunction)

        Timer_RR_WriteCounter(Timer_RR_backup.TimerUdb);
        Timer_RR_STATUS_MASK =Timer_RR_backup.InterruptMaskValue;
        #if (Timer_RR_UsingHWCaptureCounter)
            Timer_RR_SetCaptureCount(Timer_RR_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_RR_UDB_CONTROL_REG_REMOVED)
            Timer_RR_WriteControlRegister(Timer_RR_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_RR_Sleep
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
*  Timer_RR_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_RR_Sleep(void) 
{
    #if(!Timer_RR_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_RR_CTRL_ENABLE == (Timer_RR_CONTROL & Timer_RR_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_RR_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_RR_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_RR_Stop();
    Timer_RR_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_RR_Wakeup
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
*  Timer_RR_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_RR_Wakeup(void) 
{
    Timer_RR_RestoreConfig();
    #if(!Timer_RR_UDB_CONTROL_REG_REMOVED)
        if(Timer_RR_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_RR_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
