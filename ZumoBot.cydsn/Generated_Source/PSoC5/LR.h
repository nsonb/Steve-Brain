/*******************************************************************************
* File Name: LR.h  
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

#if !defined(CY_PINS_LR_H) /* Pins LR_H */
#define CY_PINS_LR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LR_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LR__PORT == 15 && ((LR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LR_Write(uint8 value);
void    LR_SetDriveMode(uint8 mode);
uint8   LR_ReadDataReg(void);
uint8   LR_Read(void);
void    LR_SetInterruptMode(uint16 position, uint16 mode);
uint8   LR_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LR_SetDriveMode() function.
     *  @{
     */
        #define LR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LR_DM_RES_UP          PIN_DM_RES_UP
        #define LR_DM_RES_DWN         PIN_DM_RES_DWN
        #define LR_DM_OD_LO           PIN_DM_OD_LO
        #define LR_DM_OD_HI           PIN_DM_OD_HI
        #define LR_DM_STRONG          PIN_DM_STRONG
        #define LR_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LR_MASK               LR__MASK
#define LR_SHIFT              LR__SHIFT
#define LR_WIDTH              1u

/* Interrupt constants */
#if defined(LR__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LR_SetInterruptMode() function.
     *  @{
     */
        #define LR_INTR_NONE      (uint16)(0x0000u)
        #define LR_INTR_RISING    (uint16)(0x0001u)
        #define LR_INTR_FALLING   (uint16)(0x0002u)
        #define LR_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LR_INTR_MASK      (0x01u) 
#endif /* (LR__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LR_PS                     (* (reg8 *) LR__PS)
/* Data Register */
#define LR_DR                     (* (reg8 *) LR__DR)
/* Port Number */
#define LR_PRT_NUM                (* (reg8 *) LR__PRT) 
/* Connect to Analog Globals */                                                  
#define LR_AG                     (* (reg8 *) LR__AG)                       
/* Analog MUX bux enable */
#define LR_AMUX                   (* (reg8 *) LR__AMUX) 
/* Bidirectional Enable */                                                        
#define LR_BIE                    (* (reg8 *) LR__BIE)
/* Bit-mask for Aliased Register Access */
#define LR_BIT_MASK               (* (reg8 *) LR__BIT_MASK)
/* Bypass Enable */
#define LR_BYP                    (* (reg8 *) LR__BYP)
/* Port wide control signals */                                                   
#define LR_CTL                    (* (reg8 *) LR__CTL)
/* Drive Modes */
#define LR_DM0                    (* (reg8 *) LR__DM0) 
#define LR_DM1                    (* (reg8 *) LR__DM1)
#define LR_DM2                    (* (reg8 *) LR__DM2) 
/* Input Buffer Disable Override */
#define LR_INP_DIS                (* (reg8 *) LR__INP_DIS)
/* LCD Common or Segment Drive */
#define LR_LCD_COM_SEG            (* (reg8 *) LR__LCD_COM_SEG)
/* Enable Segment LCD */
#define LR_LCD_EN                 (* (reg8 *) LR__LCD_EN)
/* Slew Rate Control */
#define LR_SLW                    (* (reg8 *) LR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LR_PRTDSI__CAPS_SEL       (* (reg8 *) LR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LR_PRTDSI__OE_SEL0        (* (reg8 *) LR__PRTDSI__OE_SEL0) 
#define LR_PRTDSI__OE_SEL1        (* (reg8 *) LR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LR_PRTDSI__OUT_SEL0       (* (reg8 *) LR__PRTDSI__OUT_SEL0) 
#define LR_PRTDSI__OUT_SEL1       (* (reg8 *) LR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LR_PRTDSI__SYNC_OUT       (* (reg8 *) LR__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LR__SIO_CFG)
    #define LR_SIO_HYST_EN        (* (reg8 *) LR__SIO_HYST_EN)
    #define LR_SIO_REG_HIFREQ     (* (reg8 *) LR__SIO_REG_HIFREQ)
    #define LR_SIO_CFG            (* (reg8 *) LR__SIO_CFG)
    #define LR_SIO_DIFF           (* (reg8 *) LR__SIO_DIFF)
#endif /* (LR__SIO_CFG) */

/* Interrupt Registers */
#if defined(LR__INTSTAT)
    #define LR_INTSTAT            (* (reg8 *) LR__INTSTAT)
    #define LR_SNAP               (* (reg8 *) LR__SNAP)
    
	#define LR_0_INTTYPE_REG 		(* (reg8 *) LR__0__INTTYPE)
#endif /* (LR__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LR_H */


/* [] END OF FILE */
