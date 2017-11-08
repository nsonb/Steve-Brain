/*******************************************************************************
* File Name: MotorLeft.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MotorLeft_H) /* Pins MotorLeft_H */
#define CY_PINS_MotorLeft_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorLeft_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorLeft__PORT == 15 && ((MotorLeft__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorLeft_Write(uint8 value);
void    MotorLeft_SetDriveMode(uint8 mode);
uint8   MotorLeft_ReadDataReg(void);
uint8   MotorLeft_Read(void);
void    MotorLeft_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorLeft_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorLeft_SetDriveMode() function.
     *  @{
     */
        #define MotorLeft_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorLeft_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorLeft_DM_RES_UP          PIN_DM_RES_UP
        #define MotorLeft_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorLeft_DM_OD_LO           PIN_DM_OD_LO
        #define MotorLeft_DM_OD_HI           PIN_DM_OD_HI
        #define MotorLeft_DM_STRONG          PIN_DM_STRONG
        #define MotorLeft_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorLeft_MASK               MotorLeft__MASK
#define MotorLeft_SHIFT              MotorLeft__SHIFT
#define MotorLeft_WIDTH              1u

/* Interrupt constants */
#if defined(MotorLeft__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorLeft_SetInterruptMode() function.
     *  @{
     */
        #define MotorLeft_INTR_NONE      (uint16)(0x0000u)
        #define MotorLeft_INTR_RISING    (uint16)(0x0001u)
        #define MotorLeft_INTR_FALLING   (uint16)(0x0002u)
        #define MotorLeft_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorLeft_INTR_MASK      (0x01u) 
#endif /* (MotorLeft__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorLeft_PS                     (* (reg8 *) MotorLeft__PS)
/* Data Register */
#define MotorLeft_DR                     (* (reg8 *) MotorLeft__DR)
/* Port Number */
#define MotorLeft_PRT_NUM                (* (reg8 *) MotorLeft__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorLeft_AG                     (* (reg8 *) MotorLeft__AG)                       
/* Analog MUX bux enable */
#define MotorLeft_AMUX                   (* (reg8 *) MotorLeft__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorLeft_BIE                    (* (reg8 *) MotorLeft__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorLeft_BIT_MASK               (* (reg8 *) MotorLeft__BIT_MASK)
/* Bypass Enable */
#define MotorLeft_BYP                    (* (reg8 *) MotorLeft__BYP)
/* Port wide control signals */                                                   
#define MotorLeft_CTL                    (* (reg8 *) MotorLeft__CTL)
/* Drive Modes */
#define MotorLeft_DM0                    (* (reg8 *) MotorLeft__DM0) 
#define MotorLeft_DM1                    (* (reg8 *) MotorLeft__DM1)
#define MotorLeft_DM2                    (* (reg8 *) MotorLeft__DM2) 
/* Input Buffer Disable Override */
#define MotorLeft_INP_DIS                (* (reg8 *) MotorLeft__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorLeft_LCD_COM_SEG            (* (reg8 *) MotorLeft__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorLeft_LCD_EN                 (* (reg8 *) MotorLeft__LCD_EN)
/* Slew Rate Control */
#define MotorLeft_SLW                    (* (reg8 *) MotorLeft__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorLeft_PRTDSI__CAPS_SEL       (* (reg8 *) MotorLeft__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorLeft_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorLeft__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorLeft_PRTDSI__OE_SEL0        (* (reg8 *) MotorLeft__PRTDSI__OE_SEL0) 
#define MotorLeft_PRTDSI__OE_SEL1        (* (reg8 *) MotorLeft__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorLeft_PRTDSI__OUT_SEL0       (* (reg8 *) MotorLeft__PRTDSI__OUT_SEL0) 
#define MotorLeft_PRTDSI__OUT_SEL1       (* (reg8 *) MotorLeft__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorLeft_PRTDSI__SYNC_OUT       (* (reg8 *) MotorLeft__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorLeft__SIO_CFG)
    #define MotorLeft_SIO_HYST_EN        (* (reg8 *) MotorLeft__SIO_HYST_EN)
    #define MotorLeft_SIO_REG_HIFREQ     (* (reg8 *) MotorLeft__SIO_REG_HIFREQ)
    #define MotorLeft_SIO_CFG            (* (reg8 *) MotorLeft__SIO_CFG)
    #define MotorLeft_SIO_DIFF           (* (reg8 *) MotorLeft__SIO_DIFF)
#endif /* (MotorLeft__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorLeft__INTSTAT)
    #define MotorLeft_INTSTAT            (* (reg8 *) MotorLeft__INTSTAT)
    #define MotorLeft_SNAP               (* (reg8 *) MotorLeft__SNAP)
    
	#define MotorLeft_0_INTTYPE_REG 		(* (reg8 *) MotorLeft__0__INTTYPE)
#endif /* (MotorLeft__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorLeft_H */


/* [] END OF FILE */
