/*******************************************************************************
* File Name: LL.h  
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

#if !defined(CY_PINS_LL_H) /* Pins LL_H */
#define CY_PINS_LL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LL__PORT == 15 && ((LL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LL_Write(uint8 value);
void    LL_SetDriveMode(uint8 mode);
uint8   LL_ReadDataReg(void);
uint8   LL_Read(void);
void    LL_SetInterruptMode(uint16 position, uint16 mode);
uint8   LL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LL_SetDriveMode() function.
     *  @{
     */
        #define LL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LL_DM_RES_UP          PIN_DM_RES_UP
        #define LL_DM_RES_DWN         PIN_DM_RES_DWN
        #define LL_DM_OD_LO           PIN_DM_OD_LO
        #define LL_DM_OD_HI           PIN_DM_OD_HI
        #define LL_DM_STRONG          PIN_DM_STRONG
        #define LL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LL_MASK               LL__MASK
#define LL_SHIFT              LL__SHIFT
#define LL_WIDTH              1u

/* Interrupt constants */
#if defined(LL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LL_SetInterruptMode() function.
     *  @{
     */
        #define LL_INTR_NONE      (uint16)(0x0000u)
        #define LL_INTR_RISING    (uint16)(0x0001u)
        #define LL_INTR_FALLING   (uint16)(0x0002u)
        #define LL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LL_INTR_MASK      (0x01u) 
#endif /* (LL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LL_PS                     (* (reg8 *) LL__PS)
/* Data Register */
#define LL_DR                     (* (reg8 *) LL__DR)
/* Port Number */
#define LL_PRT_NUM                (* (reg8 *) LL__PRT) 
/* Connect to Analog Globals */                                                  
#define LL_AG                     (* (reg8 *) LL__AG)                       
/* Analog MUX bux enable */
#define LL_AMUX                   (* (reg8 *) LL__AMUX) 
/* Bidirectional Enable */                                                        
#define LL_BIE                    (* (reg8 *) LL__BIE)
/* Bit-mask for Aliased Register Access */
#define LL_BIT_MASK               (* (reg8 *) LL__BIT_MASK)
/* Bypass Enable */
#define LL_BYP                    (* (reg8 *) LL__BYP)
/* Port wide control signals */                                                   
#define LL_CTL                    (* (reg8 *) LL__CTL)
/* Drive Modes */
#define LL_DM0                    (* (reg8 *) LL__DM0) 
#define LL_DM1                    (* (reg8 *) LL__DM1)
#define LL_DM2                    (* (reg8 *) LL__DM2) 
/* Input Buffer Disable Override */
#define LL_INP_DIS                (* (reg8 *) LL__INP_DIS)
/* LCD Common or Segment Drive */
#define LL_LCD_COM_SEG            (* (reg8 *) LL__LCD_COM_SEG)
/* Enable Segment LCD */
#define LL_LCD_EN                 (* (reg8 *) LL__LCD_EN)
/* Slew Rate Control */
#define LL_SLW                    (* (reg8 *) LL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LL_PRTDSI__CAPS_SEL       (* (reg8 *) LL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LL_PRTDSI__OE_SEL0        (* (reg8 *) LL__PRTDSI__OE_SEL0) 
#define LL_PRTDSI__OE_SEL1        (* (reg8 *) LL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LL_PRTDSI__OUT_SEL0       (* (reg8 *) LL__PRTDSI__OUT_SEL0) 
#define LL_PRTDSI__OUT_SEL1       (* (reg8 *) LL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LL_PRTDSI__SYNC_OUT       (* (reg8 *) LL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LL__SIO_CFG)
    #define LL_SIO_HYST_EN        (* (reg8 *) LL__SIO_HYST_EN)
    #define LL_SIO_REG_HIFREQ     (* (reg8 *) LL__SIO_REG_HIFREQ)
    #define LL_SIO_CFG            (* (reg8 *) LL__SIO_CFG)
    #define LL_SIO_DIFF           (* (reg8 *) LL__SIO_DIFF)
#endif /* (LL__SIO_CFG) */

/* Interrupt Registers */
#if defined(LL__INTSTAT)
    #define LL_INTSTAT            (* (reg8 *) LL__INTSTAT)
    #define LL_SNAP               (* (reg8 *) LL__SNAP)
    
	#define LL_0_INTTYPE_REG 		(* (reg8 *) LL__0__INTTYPE)
#endif /* (LL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LL_H */


/* [] END OF FILE */
