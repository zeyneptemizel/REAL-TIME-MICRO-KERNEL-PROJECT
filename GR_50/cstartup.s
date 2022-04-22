/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2008 IAR Systems. All rights reserved.
 *
 * $Revision: 46842 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup


        PUBLIC  __iar_program_start
       EXTERN  __cmain
        EXTERN  __vector_table
        EXTWEAK __iar_init_core
        EXTWEAK __iar_init_vfp

        SECTION .text:CODE:REORDER(1)
        THUMB
__iar_program_start:
        FUNCALL __iar_program_start, __iar_init_core
        BL      __iar_init_core
        FUNCALL __iar_program_start, __iar_init_vfp
        BL      __iar_init_vfp

        FUNCALL __iar_program_start, __cmain
        BL      __cmain

        REQUIRE __vector_table


        END
