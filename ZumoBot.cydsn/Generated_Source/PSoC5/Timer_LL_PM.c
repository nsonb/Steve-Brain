/*******************************************************************************
* File Name: Timer_LL_PM.c
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

#include "Timer_LL.h"

static Timer_LL_backupStruct Timer_LL_backup;


/*******************************************************************************
* Function Name: Timer_LL_SaveConfig
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
*  Timer_LL_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_LL_SaveConfig(void) 
{
    #if (!Timer_LL_UsingFixedFunction)
        Timer_LL_backup.TimerUdb = Timer_LL_ReadCounter();
        Timer_LL_backup.InterruptMaskValue = Timer_LL_STATUS_MASK;
        #if (Timer_LL_UsingHWCaptureCounter)
            Timer_LL_backup.TimerCaptureCounter = Timer_LL_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_LL_UDB_CONTROL_REG_REMOVED)
            Timer_LL_backup.TimerControlRegister = Timer_LL_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_LL_RestoreConfig
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
*  Timer_LL_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_LL_RestoreConfig(void) 
{   
    #if (!Timer_LL_UsingFixedFunction)

        Timer_LL_WriteCounter(Timer_LL_backup.TimerUdb);
        Timer_LL_STATUS_MASK =Timer_LL_backup.InterruptMaskValue;
        #if (Timer_LL_UsingHWCaptureCounter)
            Timer_LL_SetCaptureCount(Timer_LL_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_LL_UDB_CONTROL_REG_REMOVED)
            Timer_LL_WriteControlRegister(Timer_LL_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_LL_Sleep
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
*  Timer_LL_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_LL_Sleep(void) 
{
    #if(!Timer_LL_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_LL_CTRL_ENABLE == (Timer_LL_CONTROL & Timer_LL_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_LL_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_LL_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_LL_Stop();
    Timer_LL_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_LL_Wakeup
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
*  Timer_LL_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_LL_Wakeup(void) 
{
    Timer_LL_RestoreConfig();
    #if(!Timer_LL_UDB_CONTROL_REG_REMOVED)
        if(Timer_LL_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_LL_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
