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
/** \file mcuconfig_defines.h
 **
 ** DO NOT CHANGE THIS FILE
 **
 ** this file contains defines used in mcuconfig.h 
 **
 ** History:
 **   - 2012-01-10  1.0  MSc  First version for 8FX
 ************************************************************************/

#ifndef __MCUCONFIG_DEFINES_H__
#define __MCUCONFIG_DEFINES_H__

#define ON 1
#define OFF 0

/* START - Clock Defines, DO NOT CHANGE */
#define CLOCK_MODE_SUB_CRYST   0
#define CLOCK_MODE_MAIN_CRYST  2
#define CLOCK_MODE_SUB_RC      4 
#define CLOCK_MODE_MAIN_RC     6
#define CLOCK_MODE_MAIN_RC_PLL 7

#define MON_MODE_SUB_RC     0 
#define MON_MODE_SUB_CRYST  1
#define MON_MODE_MAIN_RC    2
#define MON_MODE_MAIN_CRYST 3

#define SRC_CLOCK_DIV1       0
#define SRC_CLOCK_DIV4       1
#define SRC_CLOCK_DIV8       2
#define SRC_CLOCK_DIV16      3

#define MAIN_CLOCK_CR_4MHZ           0x00
#define MAIN_CLOCK_CR_8MHZ           (0x80 | MAIN_CLOCK_PLL_CR_8MHZ)
#define MAIN_CLOCK_CR_10MHZ          (0x80 | MAIN_CLOCK_PLL_CR_10MHZ)
#define MAIN_CLOCK_CR_12MHZ          (0x80 | MAIN_CLOCK_PLL_CR_12MHZ)
#define MAIN_CLOCK_CR_16MHZ          (0x80 | MAIN_CLOCK_PLL_CR_16MHZ)

#define MAIN_CLOCK_PLL_CR_8MHZ      0x0
#define MAIN_CLOCK_PLL_CR_10MHZ     0x1
#define MAIN_CLOCK_PLL_CR_12MHZ     0x2
#define MAIN_CLOCK_PLL_CR_16MHZ     0x4

#endif