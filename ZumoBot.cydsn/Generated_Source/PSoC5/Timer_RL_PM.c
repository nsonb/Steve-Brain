/*******************************************************************************
* File Name: Timer_RL_PM.c
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

#include "Timer_RL.h"

static Timer_RL_backupStruct Timer_RL_backup;


/*******************************************************************************
* Function Name: Timer_RL_SaveConfig
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
*  Timer_RL_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_RL_SaveConfig(void) 
{
    #if (!Timer_RL_UsingFixedFunction)
        Timer_RL_backup.TimerUdb = Timer_RL_ReadCounter();
        Timer_RL_backup.InterruptMaskValue = Timer_RL_STATUS_MASK;
        #if (Timer_RL_UsingHWCaptureCounter)
            Timer_RL_backup.TimerCaptureCounter = Timer_RL_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_RL_UDB_CONTROL_REG_REMOVED)
            Timer_RL_backup.TimerControlRegister = Timer_RL_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_RL_RestoreConfig
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
*  Timer_RL_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_RL_RestoreConfig(void) 
{   
    #if (!Timer_RL_UsingFixedFunction)

        Timer_RL_WriteCounter(Timer_RL_backup.TimerUdb);
        Timer_RL_STATUS_MASK =Timer_RL_backup.InterruptMaskValue;
        #if (Timer_RL_UsingHWCaptureCounter)
            Timer_RL_SetCaptureCount(Timer_RL_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_RL_UDB_CONTROL_REG_REMOVED)
            Timer_RL_WriteControlRegister(Timer_RL_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_RL_Sleep
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
*  Timer_RL_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_RL_Sleep(void) 
{
    #if(!Timer_RL_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_RL_CTRL_ENABLE == (Timer_RL_CONTROL & Timer_RL_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_RL_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_RL_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_RL_Stop();
    Timer_RL_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_RL_Wakeup
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
*  Timer_RL_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_RL_Wakeup(void) 
{
    Timer_RL_RestoreConfig();
    #if(!Timer_RL_UDB_CONTROL_REG_REMOVED)
        if(Timer_RL_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_RL_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
