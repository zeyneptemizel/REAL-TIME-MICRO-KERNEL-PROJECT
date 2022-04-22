        ;
        ; written on 2nd March 2019, by Maben Rabi
        ; needs conformance to the  API header file: kernel_functions_march_2019.h file
        ;
        
        MODULE  ?context_switching_functions_march_2019

        PUBLIC  SwitchContext
        PUBLIC  LoadContext_In_Run
        PUBLIC  LoadContext_In_Terminate
        PUBLIC  switch_to_stack_of_next_task

        PUBLIC  SysTick_Handler
        PUBLIC  SVC_Handler
        PUBLIC  isr_on
        PUBLIC  isr_off
        
        EXTERN  NextTask
        EXTERN  PreviousTask
        EXTERN  TimerInt

        SECTION .text:CODE

        THUMB

address_ICSR             EQU   0xE000ED04    ; address of the NVIC ICSR register
                                             ; if bit 22 is 1, then an interrupt is pending
                                             ; if we write  1 to bit 25 then we clear any pending sys tick interrupt
address_sysTick_reload   EQU   0xE000E014    ; address of the Sys Tick reload value register
address_sysTick_counter  EQU   0xE000E018    ; address of the Sys Tick count down counter register

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SysTick_Handler

        CPSID   I              ; disable all maskable interrupts
        
        TST     LR,  #0x04     ; if LR = 0xFFFFFFF9 then before interrupt, SP was MSP,
                               ;                    which means that IRQ arrived
                               ;                    while main was executing
                               ; if LR = 0xFFFFFFFD then before interrupt, SP was PSP,´
                               ;                    which means that IRQ arrived
                               ;                    while a task was executing
        BEQ     trigger_hardware_unstack  
                               ; jump and exit the ISR if IRQ arrived while main was running
    
        MRS     r2,  psp       ; hardware has already pushed the 8 registers:
                               ; r0, r1, r2, r3, r12, LR(r14), PC(r15), xPSR  (with r0 at top)
        ISB
        LDR     r3,  =NextTask  
        LDR     r0,  [r3]      ; point r0 to RunningTask->SP
        ISB
        STR     r2,  [r0]
        ISB
        ADD     r0,  r0, #4
        STMIA   r0, {r4-r11}   ; store r4 through r11
        ISB
        PUSH    {r3, LR}       ; push on main stack the address of RuningTask, and LR
        
        BL      TimerInt       ; call Kernel C function TimerInt
                               ; among other things, this might update RunningTask
                               ; (and unfortunately) changes LR 
        POP     {r3, LR}
        
        ISB       
        LDR     r0,  [r3]      ; point r0 to RunningTask->SP
        
        LDR     r2,  [r0]
        MSR     psp, r2
        ISB
        ADD     r0,  r0, #4
        LDMIA   r0, {r4-r11}   ; store r4 through r11

trigger_hardware_unstack
        CPSIE   I              ; enable all maskable interupts  
        BX      LR             ; exit ISR and trigger hardware unstacking 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SVC_Handler
        CPSID   I
        PUSH    {r0,r1,r2,LR}   ; push onto main stack

        TST     LR,  #0x04         ; if LR = 0xFFFFFFF9 then before interrupt, SP was MSP,
        BEQ     called_from_main   ;                    which means that IRQ arrived
                                   ;                    while main was executing
                                   ; if LR = 0xFFFFFFFD then before interrupt, SP was PSP,´
                                   ;                    which means that IRQ arrived
                                   ;                    while a task was executing        
        MRS     r0, psp         ; peek into process stack
        ISB
        LDR     r1, [r0, #24]   ; retrieve hardware stacked PC
        B       calculate_SVC_number        

called_from_main
        MOV     r0, SP          ; peek into main stack
        LDR     r1, [r0, #40]   ; retrieve hardware stacked PC
        
calculate_SVC_number
        LDRH    r2, [r1, #-2]   ; load half word
        BIC     r2, r2, #0xFF00 ; Extract SVC number
                
        CMP     r2, #0
        BEQ    svc_function_isrOff
        CMP     r2, #1
        BEQ    svc_function_isrOn
        CMP     r2, #2
        BEQ    svc_function_switchContext
        CMP     r2, #3
        BEQ    svc_function_loadContext_for_terminate
        
	CPSIE   I               ; for all other SVC numbers
        POP     {r0,r1,r2,PC}   ; exit ISR and trigger_hardware_unstack 

;;;---------------------
svc_function_isrOff             
;  SVC function 0
        MOV     r0, #0xA0       ; this chip ignores the 4 least significant bits
                                ; and the priority value of Sys Tick has been set to 0xE0
        MSR     BASEPRI,  r0    ; disables sys tick, but SVC interrupt is still enabled
        CPSIE   I
        POP     {r0,r1,r2,PC}   ; exit ISR and trigger_hardware_unstack 

;;;---------------------
svc_function_isrOn              
;  SVC function 1
        MOV     r0, #0
        MSR     BASEPRI,  r0    ; sys tick enabled
        CPSIE   I
        POP     {r0,r1,r2,PC}   ; exit ISR and trigger_hardware_unstack 

;;;----------------------
svc_function_switchContext        
;  SVC function 2
        MRS     r0,  psp        ; r0 contains the process stack pointer 
        ISB                     ; of the task that was running before interrupt
        LDR     r1,  = PreviousTask         
        LDR     r1,  [r1]       ; point r1 to PrevisouTask->SP
        STR     r0,  [r1]
        ADD     r1, r1, #4
        STMIA   r1, {r4-r11}    ; this completes context saving for task running before interrupt
        
        POP     {r0, r1, r2}    ; to (partly) reverse the PUSH at the beginning of SVC handler
                                ; exception return value is now at top of main stack
                                ; and this shall be popped while leaving the ISR
        
        LDR     r1,  =NextTask
        LDR     r1,  [r1]
        LDR     r0,  [r1]       ; retrieve stored process stack pointer
        MSR     psp, r0
        ISB
        
        ADD     r1,  r1, #4     ; make r0 point to RunningTask->R4toR11[0]
        LDMIA   r1, {r4-r11}    ; restore r4 through r11
        ISB
                
        MOV     r0, #0
        MSR     BASEPRI,  r0    ;  enables all maskable interrupts, including sys tick
        ISB
        CPSIE   I
        POP     {PC}            ; exit ISR and trigger_hardware_unstack 
;;;----------------------
svc_function_loadContext_for_terminate        
;  SVC function 3
        POP     {r0, r1, r2}    ; to (partly) reverse the PUSH at the beginning of SVC handler
        
        LDR     r1,  =NextTask
        LDR     r1,  [r1]
        LDR     r0,  [r1]
        MSR     psp, r0
        ISB
        
        ADD     r1,  r1, #4     ; make r0 point to RunningTask->R4toR11[0]
        LDMIA   r1, {r4-r11}    ; restore r4 through r11
        ISB
                
        MOV     r0, #0
        MSR     BASEPRI,  r0    ;  enables all maskable interrupts, including sys tick
        ISB
        CPSIE   I
        POP     {PC}            ; exit ISR and trigger_hardware_unstack 
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SwitchContext

        PUSH    {LR}

        ISB
        SVC     #2              ; call SVC function 3 which loads context
        ISB
        
        POP     {PC}      

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LoadContext_In_Terminate
; use as the last line of the function terminate() and nowhere else !
        
        PUSH    {LR}
        
        ISB
        SVC     #3              ; call SVC function 3 which loads context of NextTask
        ISB
        
        POP     {PC}      

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LoadContext_In_Run 
; use as the last line of the function run() and nowhere else !

        CPSID    I                   ; just in case interrupts were enabled before
        
;     still in priveleged mode

;  -*-start of code section that makes sure that sys tick does not hit on exiting
        LDR      r0, =address_sysTick_reload
        LDR      r1, =address_sysTick_counter
        LDR      r2, [r0]       
        STR      r2, [r1]            ; make sys tick countdown start again from reload value 
        
        LDR      r0,  =address_ICSR
        LDR      r1,  [r0]
        ANDS     r1,  r1, #(1<<22)   ; check value of bit 22 of ICSR
        BEQ      body_LoadContext_FirstTime
        
                                  ; if bit 22 of ICSR is 1, then there must be a pending IRQ
        LDR      r1,  [r0]        ; and this must be a Sys tick IRQ since no other asynchronous interrupt has been enabled
        ORR      r1,  r1, #(1<<25) 
        STR      r1,  [r0]        ;  write 1 at bit 25 in ICSR
                                  ; so that the pending sys tick interrupt is cleared       
;  -*-end of code that makes sure that sys tick does not hit on exiting

body_LoadContext_FirstTime
        MOV      r0, #0
        MSR      BASEPRI,  r0     ;  enables all maskable interrupts, including sys tick
        ISB
        CPSIE    I

        MRS      r0,  CONTROL     ; 
        ORRS     r0,  r0, #3      ; set SP = PSP, 
        MSR      CONTROL, r0      ; and mode =  thread, unpriveleged
        ISB 
        
;   from now on in unpriveleged mode, except while interrupts are served

        LDR      r0,  =NextTask
        LDR      r0,  [r0]
        LDR      SP,  [r0]        ; retrieve stored SP
        ADD      SP,  SP, #32     ; "unstack" the 8 registers put there while creating task
        ISB
        
        ADD      r0,  r0, #36     ; make r0 point to RunningTask->PC
        LDR      LR,  [r0]        ; retrieve RunningTask->PC
        
        LDR      r1,  [r0, #4]    ; retrieve RunningTask->SPSR
        MSR      APSR, r1
        ISB
        
        CMP      LR, #0
        BEQ      trap
        
        BX       LR

trap    B      trap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

switch_to_stack_of_next_task
;   to be used in the terminate function, and nowhere else
        
        LDR      r0,  =NextTask
        LDR      r0,  [r0]      ; point r0 to RunningTask->SP
        LDR      SP,  [r0]      ; switch to stack of the task to be loaded
        ISB
		SUB      SP, SP, #8
		ISB
        
        BX      LR
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

isr_on
        PUSH    {LR};
        SVC     #1
        ISB
        POP     {PC}
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

isr_off
        PUSH    {LR}
        SVC     #0
        ISB
        POP     {PC}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        END