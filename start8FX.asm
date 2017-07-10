;==========================================================================
; F2MC-8FX Family SOFTUNE C Compiler sample startup routine,
; ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED 2008
; LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LIMITED
;==========================================================================
;
;  History:
;  - 2011-04-01  1.0  MSc  CR Clock mode settings added
;  - 2012-01-10  1.1  MSc  Config moved to mcuconfig.h, NVR added
;  - 2012-11-29  1.2  MSc  Stack fill operations added
;
;--------------------------------------------------------------------------
;  Sample program for initialization
;--------------------------------------------------------------------------
#include "_f2mc8fx.h"
#include "mcuconfig.h"

		.PROGRAM	start
		.TITLE		start
;--------------------------------------------------------------------------
; variable define declaration
;--------------------------------------------------------------------------		

// see mcuconfig.h

;--------------------------------------------------------------------------
; external declaration of symbols
;--------------------------------------------------------------------------
		.EXPORT		__start
		.IMPORT		_main
		.IMPORT		LMEMTOMEM
		.IMPORT		LMEMCLEAR
		.IMPORT		_RAM_INIT
		.IMPORT		_ROM_INIT
		.IMPORT		_RAM_DIRINIT
		.IMPORT		_ROM_DIRINIT

;--------------------------------------------------------------------------
; definition to stack area
;--------------------------------------------------------------------------
		.SECTION	STACK,    STACK,    ALIGN=1
		.RES.B		STACK_SIZE
STACK_TOP:
		.RES.B		2
		
;--------------------------------------------------------------------------
; definition to start address of data, const and code section
;--------------------------------------------------------------------------
		.SECTION	DIRDATA,  DIR,      ALIGN=1
		.SECTION	DIRINIT,  DIR,      ALIGN=1
		.SECTION	DATA,     DATA,     ALIGN=1
		.SECTION	INIT,     DATA,     ALIGN=1

;--------------------------------------------------------------------------
; code area
;--------------------------------------------------------------------------
		.SECTION	CODE,     CODE,     ALIGN=1
__start:
;--------------------------------------------------------------------------
; clock settings
;--------------------------------------------------------------------------

		MOV	A, _IO_SYCC2
		AND A, #0xF0
		OR  A, #((OSC_SUB    << 3) | \
                 (OSC_MAIN   << 2) | \
                 (OSC_SUB_RC << 1) | \
                 (1          << 0))
        MOV _IO_SYCC2,A
        
        #if (OSC_PLL_RC == ON)
            MOV A, 0
            MOV _IO_PLLC, A
            MOV	A, #((MAIN_CR_CLOCK & 0x0F) << 6)
            MOV _IO_PLLC, A
            OR A,#0x80
            MOV _IO_PLLC, A
        #endif
         
        MOV      _IO_SYCC, #((MAIN_CLOCK     << 2) | \
                             (MAIN_CLOCK_DIV))
        
        #if (OSC_PLL_RC == ON)
wait_pll_osc:
        MOV      A,_IO_PLLC
        AND      A,#0x10
        BNZ      pll_osc_stable
        JMP      wait_pll_osc
pll_osc_stable:
        #endif

        #if (OSC_MAIN == ON)
wait_main_osc:
        MOV      A,_IO_SYCC2
        AND      A,#(1 << 6)
        BNZ      main_osc_stable
        JMP      wait_main_osc
main_osc_stable:
        #endif
                
        #if (OSC_SUB == ON)
wait_sub_osc:
        MOV      A,_IO_SYCC2
        AND      A,#(1 << 7)
        BNZ      sub_osc_stable
        JMP      wait_sub_osc
sub_osc_stable:
        #endif 
               
        #if (OSC_SUB_RC == ON)
wait_subrc_osc:
        MOV      A,_IO_SYCC2
        AND      A,#(1 << 5)
        BNZ      subrc_osc_stable
        JMP      wait_subrc_osc
subrc_osc_stable:
        #endif    
                 
        MOV A, #((OSC_SUB        << 3) | \
                 (OSC_MAIN       << 2) | \
                 (OSC_SUB_RC     << 1) | \
                 (1              << 0)) 
        MOV _IO_SYCC2,A
        
        MOV A, #((OSC_SUB        << 3) | \
                 (OSC_MAIN       << 2) | \
                 (OSC_SUB_RC     << 1) | \
                 (OSC_MAIN_RC    << 0)) 
        MOV _IO_SYCC2,A		
		#if (OSC_MAIN_RC == ON)
wait_mainrc_osc:
        MOV      A,_IO_SYCC2
        AND      A,#(1 << 4)
        BNZ      mainrc_osc_stable
        JMP      wait_mainrc_osc
mainrc_osc_stable:
        #endif
        
;--------------------------------------------------------------------------
; set stack pointer
;--------------------------------------------------------------------------
		MOVW	A, #STACK_TOP
		MOVW	SP, A
;--------------------------------------------------------------------------
; set stack pointer
;--------------------------------------------------------------------------
setstack:
		MOVW	A, #STACK_TOP
		MOVW	SP, A
		
#if (STACK_FILL == ON)
fillstack:
		MOVW     A,SP
		MOVW     A,#(STACK_TOP + STACK_SIZE)
		CMPW     A
		BNC      stackfilled
		
    	MOVW     A,#0x55AA
    	XCHW     A,T
		MOVW     A,SP
		MOVW     @A,T
		
		MOVW     A,SP
		INCW     A
		INCW     A
		MOVW     SP,A
		JMP      fillstack
stackfilled:
		MOVW	A, #STACK_TOP
		MOVW	SP, A
#endif
;--------------------------------------------------------------------------
; set register bank is 0
;--------------------------------------------------------------------------
		MOVW	A, PS
		MOVW	A, #0x07FF
		ANDW	A
		MOVW	PS, A

;--------------------------------------------------------------------------
; set ILM to the lowest level(3)
;--------------------------------------------------------------------------
		MOVW	A, PS
		MOVW	A, #0x0030
		ORW	A
		MOVW	PS, A

;--------------------------------------------------------------------------
; copy initial value *CONST(ROM) section to *INIT(RAM) section
;--------------------------------------------------------------------------
#macro		ICOPY	src_addr, dest_addr, src_section
		MOVW	EP, #\src_addr
		MOVW	A,  #\dest_addr
		MOVW	A,  #SIZEOF (\src_section)
		CALL	LMEMTOMEM
#endm

		ICOPY	_ROM_INIT,	_RAM_INIT,	INIT
		ICOPY	_ROM_DIRINIT,	_RAM_DIRINIT,	DIRINIT

;--------------------------------------------------------------------------
; zero clear of *VAR section
;--------------------------------------------------------------------------
#macro		FILL0	src_section
		MOVW	A, #\src_section
		MOVW	A, #SIZEOF (\src_section)
		CALL	LMEMCLEAR
#endm

		FILL0	DIRDATA
		FILL0	DATA

;--------------------------------------------------------------------------
; call main routine
;--------------------------------------------------------------------------
		CALL	_main
end:	JMP	end

;--------------------------------------------------------------------------
; Hard Watchdog
;--------------------------------------------------------------------------
#if (HARDWARE_WATCHDOG == OFF)
		.SECTION  WDT, CONST, LOCATE=H'FFBE
      	.DATA.W   0xA596
#endif
		
;--------------------------------------------------------------------------
; reset vector
;--------------------------------------------------------------------------
		.SECTION	RESET,    CONST,    LOCATE=0xFFFC
		.DATA.B		0xFF
		.DATA.B		0
		.DATA.H		__start

		.END	__start
