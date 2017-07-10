/************************************************************************/
/*               (C) Fujitsu Semiconductor Europe GmbH (FSEU)           */
/*                                                                      */
/* The following software deliverable is intended for and must only be  */
/* used for reference and in an evaluation laboratory environment.      */
/* It is provided on an as-is basis without charge and is subject to    */
/* alterations.                                                         */
/* It is the user's obligation to fully test the software in its        */
/* environment and to ensure proper functionality, qualification and    */
/* compliance with component specifications.                            */
/*                                                                      */
/* In the event the software deliverable includes the use of open       */
/* source components, the provisions of the governing open source       */
/* license agreement shall apply with respect to such software          */
/* deliverable.                                                         */
/* FSEU does not warrant that the deliverables do not infringe any      */
/* third party intellectual property right (IPR). In the event that     */
/* the deliverables infringe a third party IPR it is the sole           */
/* responsibility of the customer to obtain necessary licenses to       */
/* continue the usage of the deliverable.                               */
/*                                                                      */
/* To the maximum extent permitted by applicable law FSEU disclaims all */
/* warranties, whether express or implied, in particular, but not       */
/* limited to, warranties of merchantability and fitness for a          */
/* particular purpose for which the deliverable is not designated.      */
/*                                                                      */
/* To the maximum extent permitted by applicable law, FSEU's liability  */
/* is restricted to intentional misconduct and gross negligence.        */
/* FSEU is not liable for consequential damages.                        */
/*                                                                      */
/* (V1.5)                                                               */
/************************************************************************/
/** \file mcuconfig.c
 **
 ** initial MCU settings
 **
 ** History:
 **   - 2012-10-02  1.0  MSc  First version for 8FX MB95630 series
 ************************************************************************/
 
#include "mcuconfig_defines.h"

#ifndef __MCUCONFIG_H__
#define __MCUCONFIG_H__



/************************************************************************/
/* Clock Monitor                                                        */
/*                                                                      */
/* Available settings:                                                  */
/* CLOCK_MODE_SUB_RC, CLOCK_MODE_SUB_CRYST, CLOCK_MODE_MAIN_RC          */
/* CLOCK__MODE_MAIN_CRYST                                               */
/************************************************************************/
#define MAIN_CLOCK              CLOCK_MODE_MAIN_RC 

/************************************************************************/
/* Main Clock Division                                                  */
/*                                                                      */
/* Available settings:                                                  */
/* SRC_CLOCK_DIV1, SRC_CLOCK_DIV4, SRC_CLOCK_DIV8, SRC_CLOCK_DIV16      */
/************************************************************************/
#define MAIN_CLOCK_DIV          SRC_CLOCK_DIV1   

/************************************************************************/
/* Main RC Clock                                                        */
/*                                                                      */
/* Available settings:                                                  */
/* MAIN_CLOCK_CR_1MHZ, MAIN_CLOCK_CR_8MHZ, MAIN_CLOCK_CR_10MHZ,         */
/* MAIN_CLOCK_CR_12MHZ, MAIN_CLOCK_CR_16MHZ                             */
/************************************************************************/
#define MAIN_CR_CLOCK           MAIN_CLOCK_CR_4MHZ 

/************************************************************************/
/* Hardware Watchdog                                                    */
/************************************************************************/
#define HARDWARE_WATCHDOG		OFF

/************************************************************************/
/* Stack Size                                                           */
/************************************************************************/
#define STACK_SIZE              64-2
#define STACK_FILL              OFF

/************************************************************************/
/* Force Enable / Disable Additional Oscillators                        */
/************************************************************************/
#define OSC_MAIN_RC             OFF
#define OSC_SUB_RC              OFF
#define OSC_MAIN                OFF
#define OSC_SUB                 OFF
#define OSC_PLL_RC              OFF















/* DO NOT CHANGE THE FOLLOWING CODE */

#if (MAIN_CLOCK == CLOCK_MODE_SUB_CRYST)
    #undef OSC_SUB
    #define OSC_SUB ON
#elif (MAIN_CLOCK == CLOCK_MODE_MAIN_CRYST)
    #undef OSC_MAIN
    #define OSC_MAIN ON
#elif (MAIN_CLOCK == CLOCK_MODE_SUB_RC)
    #undef OSC_SUB_RC
    #define OSC_SUB_RC ON
#elif ((MAIN_CLOCK == CLOCK_MODE_MAIN_RC) || (MAIN_CLOCK == CLOCK_MODE_MAIN_RC_PLL))
    #undef OSC_MAIN_RC
    #define OSC_MAIN_RC ON
    #if (MAIN_CR_CLOCK != MAIN_CLOCK_CR_4MHZ)
        #undef MAIN_CLOCK
        #define MAIN_CLOCK CLOCK_MODE_MAIN_RC_PLL
    #else
        #undef MAIN_CLOCK
        #define MAIN_CLOCK CLOCK_MODE_MAIN_RC    
    #endif
    #if (MAIN_CLOCK == CLOCK_MODE_MAIN_RC_PLL)
        #undef OSC_PLL_RC
        #define OSC_PLL_RC ON
    #endif
#else
    #error No valid clock source was selected
#endif




#endif /* __MCUCONFIG_H__ */


