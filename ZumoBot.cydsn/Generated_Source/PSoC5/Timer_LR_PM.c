/*******************************************************************************
* File Name: Timer_LR_PM.c
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

#include "Timer_LR.h"

static Timer_LR_backupStruct Timer_LR_backup;


/*******************************************************************************
* Function Name: Timer_LR_SaveConfig
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
*  Timer_LR_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_LR_SaveConfig(void) 
{
    #if (!Timer_LR_UsingFixedFunction)
        Timer_LR_backup.TimerUdb = Timer_LR_ReadCounter();
        Timer_LR_backup.InterruptMaskValue = Timer_LR_STATUS_MASK;
        #if (Timer_LR_UsingHWCaptureCounter)
            Timer_LR_backup.TimerCaptureCounter = Timer_LR_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_LR_UDB_CONTROL_REG_REMOVED)
            Timer_LR_backup.TimerControlRegister = Timer_LR_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_LR_RestoreConfig
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
*  Timer_LR_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_LR_RestoreConfig(void) 
{   
    #if (!Timer_LR_UsingFixedFunction)

        Timer_LR_WriteCounter(Timer_LR_backup.TimerUdb);
        Timer_LR_STATUS_MASK =Timer_LR_backup.InterruptMaskValue;
        #if (Timer_LR_UsingHWCaptureCounter)
            Timer_LR_SetCaptureCount(Timer_LR_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_LR_UDB_CONTROL_REG_REMOVED)
            Timer_LR_WriteControlRegister(Timer_LR_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_LR_Sleep
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
*  Timer_LR_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_LR_Sleep(void) 
{
    #if(!Timer_LR_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_LR_CTRL_ENABLE == (Timer_LR_CONTROL & Timer_LR_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_LR_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_LR_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_LR_Stop();
    Timer_LR_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_LR_Wakeup
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
*  Timer_LR_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_LR_Wakeup(void) 
{
    Timer_LR_RestoreConfig();
    #if(!Timer_LR_UDB_CONTROL_REG_REMOVED)
        if(Timer_LR_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_LR_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
