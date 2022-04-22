 /**
 * \file
 *
 * \brief This file contains the interface for default exception handlers.
 *
 * Copyright (c) 2011 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/* Function prototype for exception table items (interrupt handler). */
typedef void (*IntFunc) (void);

/* Default empty handler */
void Dummy_Handler(void);

extern void NMI_Handler( void );
extern void HardFault_Handler( void );
extern  void MemManage_Handler( void );
extern  void BusFault_Handler( void );
extern  void UsageFault_Handler( void );
extern  void SVC_Handler( void );
extern  void DebugMon_Handler( void );
extern  void PendSV_Handler( void );
extern  void SysTick_Handler( void );
void IrqHandlerNotUsed(void);

// System Controller
extern void SYS_Handler(void);
// SUPPLY CONTROLLER
extern  void SUPC_Handler(void);
// RESET CONTROLLER
extern  void RSTC_Handler(void);
// REAL TIME CLOCK
extern  void RTC_Handler(void);
// REAL TIME TIMER
extern  void RTT_Handler(void);
// WATCHDOG TIMER
extern  void WDT_Handler(void);
// PMC
extern  void PMC_Handler(void);
// EFC0
extern  void EFC0_Handler(void);
// EFC1
extern  void EFC1_Handler(void);
// DBGU
extern  void DBGU_Handler(void);
// HSMC4
extern  void HSMCI_Handler(void);
// Parallel IO Controller A
extern  void PIOA_Handler(void);
// Parallel IO Controller B
extern  void PIOB_Handler(void);
// Parallel IO Controller C
extern  void PIOC_Handler(void);
extern  void PIOD_Handler(void);
extern  void PIOE_Handler(void);
extern  void PIOF_Handler(void);

// USART 0
extern  void USART0_Handler(void);
// USART 1
extern  void USART1_Handler(void);
// USART 2
extern  void USART2_Handler(void);
// USART 3
extern  void USART3_Handler(void);
// Multimedia Card Interface
extern  void MCI0_Handler(void);
// TWI 0
extern  void TWI0_Handler(void);
// TWI 1
extern  void TWI1_Handler(void);
// Serial Peripheral Interface 0
extern  void SPI0_Handler(void);
// Serial Synchronous Controller
extern  void SSC_Handler(void);
// Timer Counter 0
extern  void TC0_Handler(void);
// Timer Counter 1
extern  void TC1_Handler(void);
// Timer Counter 2
extern  void TC2_Handler(void);
extern  void TC3_Handler(void);
extern  void TC4_Handler(void);
extern  void TC5_Handler(void);
// PWM Controller
extern  void PWM_Handler(void);
// ADC controller
extern  void ADC_Handler(void);
// HDMA
extern  void HDMA_Handler(void);
// USB Device High Speed UDP_HS
extern  void UDPD_Handler(void);

extern  void UART_Handler(void);
extern  void CAN0_Handler(void);
extern  void CAN1_Handler(void);
extern  void DACC_Handler(void);
extern  void DMAC_Handler(void);
extern  void UOTGHS_Handler(void);
extern  void TRNG_Handler(void);


/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* EXCEPTIONS_H_INCLUDED */
