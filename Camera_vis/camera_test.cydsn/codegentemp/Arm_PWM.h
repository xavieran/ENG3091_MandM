/*******************************************************************************
* File Name: Arm_PWM.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Arm_PWM_H)
#define CY_PWM_Arm_PWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Arm_PWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Arm_PWM_Resolution                     (16u)
#define Arm_PWM_UsingFixedFunction             (0u)
#define Arm_PWM_DeadBandMode                   (0u)
#define Arm_PWM_KillModeMinTime                (0u)
#define Arm_PWM_KillMode                       (0u)
#define Arm_PWM_PWMMode                        (0u)
#define Arm_PWM_PWMModeIsCenterAligned         (0u)
#define Arm_PWM_DeadBandUsed                   (0u)
#define Arm_PWM_DeadBand2_4                    (0u)

#if !defined(Arm_PWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define Arm_PWM_UseStatus                  (1u)
#else
    #define Arm_PWM_UseStatus                  (0u)
#endif /* !defined(Arm_PWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Arm_PWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Arm_PWM_UseControl                 (1u)
#else
    #define Arm_PWM_UseControl                 (0u)
#endif /* !defined(Arm_PWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Arm_PWM_UseOneCompareMode              (1u)
#define Arm_PWM_MinimumKillTime                (1u)
#define Arm_PWM_EnableMode                     (0u)

#define Arm_PWM_CompareMode1SW                 (0u)
#define Arm_PWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Arm_PWM__B_PWM__DISABLED 0
#define Arm_PWM__B_PWM__ASYNCHRONOUS 1
#define Arm_PWM__B_PWM__SINGLECYCLE 2
#define Arm_PWM__B_PWM__LATCHED 3
#define Arm_PWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Arm_PWM__B_PWM__DBMDISABLED 0
#define Arm_PWM__B_PWM__DBM_2_4_CLOCKS 1
#define Arm_PWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Arm_PWM__B_PWM__ONE_OUTPUT 0
#define Arm_PWM__B_PWM__TWO_OUTPUTS 1
#define Arm_PWM__B_PWM__DUAL_EDGE 2
#define Arm_PWM__B_PWM__CENTER_ALIGN 3
#define Arm_PWM__B_PWM__DITHER 5
#define Arm_PWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Arm_PWM__B_PWM__LESS_THAN 1
#define Arm_PWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define Arm_PWM__B_PWM__GREATER_THAN 3
#define Arm_PWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Arm_PWM__B_PWM__EQUAL 0
#define Arm_PWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Arm_PWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Arm_PWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Arm_PWM_PWMModeIsCenterAligned) */
        #if (Arm_PWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Arm_PWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_256_CLOCKS || \
            Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Arm_PWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Arm_PWM_KillModeMinTime) */

        /* Backup control register */
        #if(Arm_PWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Arm_PWM_UseControl) */

    #endif /* (!Arm_PWM_UsingFixedFunction) */

}Arm_PWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Arm_PWM_Start(void) ;
void    Arm_PWM_Stop(void) ;

#if (Arm_PWM_UseStatus || Arm_PWM_UsingFixedFunction)
    void  Arm_PWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 Arm_PWM_ReadStatusRegister(void) ;
#endif /* (Arm_PWM_UseStatus || Arm_PWM_UsingFixedFunction) */

#define Arm_PWM_GetInterruptSource() Arm_PWM_ReadStatusRegister()

#if (Arm_PWM_UseControl)
    uint8 Arm_PWM_ReadControlRegister(void) ;
    void  Arm_PWM_WriteControlRegister(uint8 control)
          ;
#endif /* (Arm_PWM_UseControl) */

#if (Arm_PWM_UseOneCompareMode)
   #if (Arm_PWM_CompareMode1SW)
       void    Arm_PWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Arm_PWM_CompareMode1SW) */
#else
    #if (Arm_PWM_CompareMode1SW)
        void    Arm_PWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Arm_PWM_CompareMode1SW) */
    #if (Arm_PWM_CompareMode2SW)
        void    Arm_PWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Arm_PWM_CompareMode2SW) */
#endif /* (Arm_PWM_UseOneCompareMode) */

#if (!Arm_PWM_UsingFixedFunction)
    uint16   Arm_PWM_ReadCounter(void) ;
    uint16 Arm_PWM_ReadCapture(void) ;

    #if (Arm_PWM_UseStatus)
            void Arm_PWM_ClearFIFO(void) ;
    #endif /* (Arm_PWM_UseStatus) */

    void    Arm_PWM_WriteCounter(uint16 counter)
            ;
#endif /* (!Arm_PWM_UsingFixedFunction) */

void    Arm_PWM_WritePeriod(uint16 period)
        ;
uint16 Arm_PWM_ReadPeriod(void) ;

#if (Arm_PWM_UseOneCompareMode)
    void    Arm_PWM_WriteCompare(uint16 compare)
            ;
    uint16 Arm_PWM_ReadCompare(void) ;
#else
    void    Arm_PWM_WriteCompare1(uint16 compare)
            ;
    uint16 Arm_PWM_ReadCompare1(void) ;
    void    Arm_PWM_WriteCompare2(uint16 compare)
            ;
    uint16 Arm_PWM_ReadCompare2(void) ;
#endif /* (Arm_PWM_UseOneCompareMode) */


#if (Arm_PWM_DeadBandUsed)
    void    Arm_PWM_WriteDeadTime(uint8 deadtime) ;
    uint8   Arm_PWM_ReadDeadTime(void) ;
#endif /* (Arm_PWM_DeadBandUsed) */

#if ( Arm_PWM_KillModeMinTime)
    void Arm_PWM_WriteKillTime(uint8 killtime) ;
    uint8 Arm_PWM_ReadKillTime(void) ;
#endif /* ( Arm_PWM_KillModeMinTime) */

void Arm_PWM_Init(void) ;
void Arm_PWM_Enable(void) ;
void Arm_PWM_Sleep(void) ;
void Arm_PWM_Wakeup(void) ;
void Arm_PWM_SaveConfig(void) ;
void Arm_PWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Arm_PWM_INIT_PERIOD_VALUE          (799u)
#define Arm_PWM_INIT_COMPARE_VALUE1        (50u)
#define Arm_PWM_INIT_COMPARE_VALUE2        (63u)
#define Arm_PWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Arm_PWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Arm_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Arm_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Arm_PWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Arm_PWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Arm_PWM_CTRL_CMPMODE2_SHIFT)
#define Arm_PWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Arm_PWM_CTRL_CMPMODE1_SHIFT)
#define Arm_PWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Arm_PWM_UsingFixedFunction)
   #define Arm_PWM_PERIOD_LSB              (*(reg16 *) Arm_PWM_PWMHW__PER0)
   #define Arm_PWM_PERIOD_LSB_PTR          ( (reg16 *) Arm_PWM_PWMHW__PER0)
   #define Arm_PWM_COMPARE1_LSB            (*(reg16 *) Arm_PWM_PWMHW__CNT_CMP0)
   #define Arm_PWM_COMPARE1_LSB_PTR        ( (reg16 *) Arm_PWM_PWMHW__CNT_CMP0)
   #define Arm_PWM_COMPARE2_LSB            (0x00u)
   #define Arm_PWM_COMPARE2_LSB_PTR        (0x00u)
   #define Arm_PWM_COUNTER_LSB             (*(reg16 *) Arm_PWM_PWMHW__CNT_CMP0)
   #define Arm_PWM_COUNTER_LSB_PTR         ( (reg16 *) Arm_PWM_PWMHW__CNT_CMP0)
   #define Arm_PWM_CAPTURE_LSB             (*(reg16 *) Arm_PWM_PWMHW__CAP0)
   #define Arm_PWM_CAPTURE_LSB_PTR         ( (reg16 *) Arm_PWM_PWMHW__CAP0)
   #define Arm_PWM_RT1                     (*(reg8 *)  Arm_PWM_PWMHW__RT1)
   #define Arm_PWM_RT1_PTR                 ( (reg8 *)  Arm_PWM_PWMHW__RT1)

#else
   #if (Arm_PWM_Resolution == 8u) /* 8bit - PWM */

       #if(Arm_PWM_PWMModeIsCenterAligned)
           #define Arm_PWM_PERIOD_LSB      (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Arm_PWM_PERIOD_LSB_PTR  ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Arm_PWM_PERIOD_LSB      (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Arm_PWM_PERIOD_LSB_PTR  ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Arm_PWM_PWMModeIsCenterAligned) */

       #define Arm_PWM_COMPARE1_LSB        (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Arm_PWM_COMPARE1_LSB_PTR    ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Arm_PWM_COMPARE2_LSB        (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Arm_PWM_COMPARE2_LSB_PTR    ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Arm_PWM_COUNTERCAP_LSB      (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Arm_PWM_COUNTERCAP_LSB_PTR  ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Arm_PWM_COUNTER_LSB         (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Arm_PWM_COUNTER_LSB_PTR     ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Arm_PWM_CAPTURE_LSB         (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Arm_PWM_CAPTURE_LSB_PTR     ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Arm_PWM_PWMModeIsCenterAligned)
               #define Arm_PWM_PERIOD_LSB      (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Arm_PWM_PERIOD_LSB_PTR  ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Arm_PWM_PERIOD_LSB      (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Arm_PWM_PERIOD_LSB_PTR  ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Arm_PWM_PWMModeIsCenterAligned) */

            #define Arm_PWM_COMPARE1_LSB       (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Arm_PWM_COMPARE1_LSB_PTR   ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Arm_PWM_COMPARE2_LSB       (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Arm_PWM_COMPARE2_LSB_PTR   ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Arm_PWM_COUNTERCAP_LSB     (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Arm_PWM_COUNTERCAP_LSB_PTR ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Arm_PWM_COUNTER_LSB        (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Arm_PWM_COUNTER_LSB_PTR    ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Arm_PWM_CAPTURE_LSB        (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Arm_PWM_CAPTURE_LSB_PTR    ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Arm_PWM_PWMModeIsCenterAligned)
               #define Arm_PWM_PERIOD_LSB      (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Arm_PWM_PERIOD_LSB_PTR  ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Arm_PWM_PERIOD_LSB      (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Arm_PWM_PERIOD_LSB_PTR  ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Arm_PWM_PWMModeIsCenterAligned) */

            #define Arm_PWM_COMPARE1_LSB       (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Arm_PWM_COMPARE1_LSB_PTR   ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Arm_PWM_COMPARE2_LSB       (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Arm_PWM_COMPARE2_LSB_PTR   ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Arm_PWM_COUNTERCAP_LSB     (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Arm_PWM_COUNTERCAP_LSB_PTR ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Arm_PWM_COUNTER_LSB        (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Arm_PWM_COUNTER_LSB_PTR    ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Arm_PWM_CAPTURE_LSB        (*(reg16 *) Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Arm_PWM_CAPTURE_LSB_PTR    ((reg16 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Arm_PWM_AUX_CONTROLDP1          (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Arm_PWM_AUX_CONTROLDP1_PTR      ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Arm_PWM_Resolution == 8) */

   #define Arm_PWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Arm_PWM_AUX_CONTROLDP0          (*(reg8 *)  Arm_PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Arm_PWM_AUX_CONTROLDP0_PTR      ((reg8 *)   Arm_PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Arm_PWM_UsingFixedFunction) */

#if(Arm_PWM_KillModeMinTime )
    #define Arm_PWM_KILLMODEMINTIME        (*(reg8 *)  Arm_PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Arm_PWM_KILLMODEMINTIME_PTR    ((reg8 *)   Arm_PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Arm_PWM_KillModeMinTime ) */

#if(Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_256_CLOCKS)
    #define Arm_PWM_DEADBAND_COUNT         (*(reg8 *)  Arm_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Arm_PWM_DEADBAND_COUNT_PTR     ((reg8 *)   Arm_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Arm_PWM_DEADBAND_LSB_PTR       ((reg8 *)   Arm_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Arm_PWM_DEADBAND_LSB           (*(reg8 *)  Arm_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Arm_PWM_UsingFixedFunction)
        #define Arm_PWM_DEADBAND_COUNT         (*(reg8 *)  Arm_PWM_PWMHW__CFG0)
        #define Arm_PWM_DEADBAND_COUNT_PTR     ((reg8 *)   Arm_PWM_PWMHW__CFG0)
        #define Arm_PWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Arm_PWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Arm_PWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Arm_PWM_DEADBAND_COUNT         (*(reg8 *)  Arm_PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Arm_PWM_DEADBAND_COUNT_PTR     ((reg8 *)   Arm_PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Arm_PWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Arm_PWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Arm_PWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Arm_PWM_UsingFixedFunction) */
#endif /* (Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_256_CLOCKS) */



#if (Arm_PWM_UsingFixedFunction)
    #define Arm_PWM_STATUS                 (*(reg8 *) Arm_PWM_PWMHW__SR0)
    #define Arm_PWM_STATUS_PTR             ((reg8 *) Arm_PWM_PWMHW__SR0)
    #define Arm_PWM_STATUS_MASK            (*(reg8 *) Arm_PWM_PWMHW__SR0)
    #define Arm_PWM_STATUS_MASK_PTR        ((reg8 *) Arm_PWM_PWMHW__SR0)
    #define Arm_PWM_CONTROL                (*(reg8 *) Arm_PWM_PWMHW__CFG0)
    #define Arm_PWM_CONTROL_PTR            ((reg8 *) Arm_PWM_PWMHW__CFG0)
    #define Arm_PWM_CONTROL2               (*(reg8 *) Arm_PWM_PWMHW__CFG1)
    #define Arm_PWM_CONTROL3               (*(reg8 *) Arm_PWM_PWMHW__CFG2)
    #define Arm_PWM_GLOBAL_ENABLE          (*(reg8 *) Arm_PWM_PWMHW__PM_ACT_CFG)
    #define Arm_PWM_GLOBAL_ENABLE_PTR      ( (reg8 *) Arm_PWM_PWMHW__PM_ACT_CFG)
    #define Arm_PWM_GLOBAL_STBY_ENABLE     (*(reg8 *) Arm_PWM_PWMHW__PM_STBY_CFG)
    #define Arm_PWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Arm_PWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Arm_PWM_BLOCK_EN_MASK          (Arm_PWM_PWMHW__PM_ACT_MSK)
    #define Arm_PWM_BLOCK_STBY_EN_MASK     (Arm_PWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Arm_PWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Arm_PWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Arm_PWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Arm_PWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Arm_PWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Arm_PWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Arm_PWM_CTRL_ENABLE            (uint8)((uint8)0x01u << Arm_PWM_CTRL_ENABLE_SHIFT)
    #define Arm_PWM_CTRL_RESET             (uint8)((uint8)0x01u << Arm_PWM_CTRL_RESET_SHIFT)
    #define Arm_PWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Arm_PWM_CTRL_CMPMODE2_SHIFT)
    #define Arm_PWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Arm_PWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Arm_PWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Arm_PWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Arm_PWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Arm_PWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Arm_PWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Arm_PWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Arm_PWM_STATUS_TC_INT_EN_MASK_SHIFT            (Arm_PWM_STATUS_TC_SHIFT - 4u)
    #define Arm_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Arm_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (Arm_PWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Arm_PWM_STATUS_TC              (uint8)((uint8)0x01u << Arm_PWM_STATUS_TC_SHIFT)
    #define Arm_PWM_STATUS_CMP1            (uint8)((uint8)0x01u << Arm_PWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Arm_PWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Arm_PWM_STATUS_TC >> 4u)
    #define Arm_PWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Arm_PWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Arm_PWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Arm_PWM_RT1_MASK              (uint8)((uint8)0x03u << Arm_PWM_RT1_SHIFT)
    #define Arm_PWM_SYNC                  (uint8)((uint8)0x03u << Arm_PWM_RT1_SHIFT)
    #define Arm_PWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Arm_PWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Arm_PWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Arm_PWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Arm_PWM_SYNCDSI_SHIFT)


#else
    #define Arm_PWM_STATUS                (*(reg8 *)   Arm_PWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Arm_PWM_STATUS_PTR            ((reg8 *)    Arm_PWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Arm_PWM_STATUS_MASK           (*(reg8 *)   Arm_PWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Arm_PWM_STATUS_MASK_PTR       ((reg8 *)    Arm_PWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Arm_PWM_STATUS_AUX_CTRL       (*(reg8 *)   Arm_PWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Arm_PWM_CONTROL               (*(reg8 *)   Arm_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Arm_PWM_CONTROL_PTR           ((reg8 *)    Arm_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Arm_PWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define Arm_PWM_CTRL_RESET_SHIFT       (0x06u)
    #define Arm_PWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Arm_PWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Arm_PWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Arm_PWM_CTRL_ENABLE            (uint8)((uint8)0x01u << Arm_PWM_CTRL_ENABLE_SHIFT)
    #define Arm_PWM_CTRL_RESET             (uint8)((uint8)0x01u << Arm_PWM_CTRL_RESET_SHIFT)
    #define Arm_PWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Arm_PWM_CTRL_CMPMODE2_SHIFT)
    #define Arm_PWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Arm_PWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Arm_PWM_STATUS_KILL_SHIFT          (0x05u)
    #define Arm_PWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Arm_PWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Arm_PWM_STATUS_TC_SHIFT            (0x02u)
    #define Arm_PWM_STATUS_CMP2_SHIFT          (0x01u)
    #define Arm_PWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Arm_PWM_STATUS_KILL_INT_EN_MASK_SHIFT          (Arm_PWM_STATUS_KILL_SHIFT)
    #define Arm_PWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Arm_PWM_STATUS_FIFONEMPTY_SHIFT)
    #define Arm_PWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Arm_PWM_STATUS_FIFOFULL_SHIFT)
    #define Arm_PWM_STATUS_TC_INT_EN_MASK_SHIFT            (Arm_PWM_STATUS_TC_SHIFT)
    #define Arm_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (Arm_PWM_STATUS_CMP2_SHIFT)
    #define Arm_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (Arm_PWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Arm_PWM_STATUS_KILL            (uint8)((uint8)0x00u << Arm_PWM_STATUS_KILL_SHIFT )
    #define Arm_PWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Arm_PWM_STATUS_FIFOFULL_SHIFT)
    #define Arm_PWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Arm_PWM_STATUS_FIFONEMPTY_SHIFT)
    #define Arm_PWM_STATUS_TC              (uint8)((uint8)0x01u << Arm_PWM_STATUS_TC_SHIFT)
    #define Arm_PWM_STATUS_CMP2            (uint8)((uint8)0x01u << Arm_PWM_STATUS_CMP2_SHIFT)
    #define Arm_PWM_STATUS_CMP1            (uint8)((uint8)0x01u << Arm_PWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Arm_PWM_STATUS_KILL_INT_EN_MASK            (Arm_PWM_STATUS_KILL)
    #define Arm_PWM_STATUS_FIFOFULL_INT_EN_MASK        (Arm_PWM_STATUS_FIFOFULL)
    #define Arm_PWM_STATUS_FIFONEMPTY_INT_EN_MASK      (Arm_PWM_STATUS_FIFONEMPTY)
    #define Arm_PWM_STATUS_TC_INT_EN_MASK              (Arm_PWM_STATUS_TC)
    #define Arm_PWM_STATUS_CMP2_INT_EN_MASK            (Arm_PWM_STATUS_CMP2)
    #define Arm_PWM_STATUS_CMP1_INT_EN_MASK            (Arm_PWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Arm_PWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Arm_PWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Arm_PWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Arm_PWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Arm_PWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Arm_PWM_UsingFixedFunction */

#endif  /* CY_PWM_Arm_PWM_H */


/* [] END OF FILE */