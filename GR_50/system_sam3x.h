/**
 * \file
 *
 * \brief Provides the low-level initialization functions that called 
 * on chip startup.
 *
 * Copyright (c) 2011-2012 Atmel Corporation. All rights reserved.
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

#ifndef SYSTEM_SAM3X_H_INCLUDED
#define SYSTEM_SAM3X_H_INCLUDED

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

#include <stdint.h>
#include "core_cm3.h"
  
/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR SAM3X8E */
/* ************************************************************************** */

/* Device characteristics */
#define CHIP_FREQ_SLCK_RC_MIN           (20000UL)
#define CHIP_FREQ_SLCK_RC               (32000UL)
#define CHIP_FREQ_SLCK_RC_MAX           (44000UL)
#define CHIP_FREQ_MAINCK_RC_4MHZ        (4000000UL)
#define CHIP_FREQ_MAINCK_RC_8MHZ        (8000000UL)
#define CHIP_FREQ_MAINCK_RC_12MHZ       (12000000UL)
#define CHIP_FREQ_CPU_MAX               (84000000UL)
#define CHIP_FREQ_XTAL_32K              (32768UL)
#define CHIP_FREQ_XTAL_12M              (12000000UL)

/* Embedded Flash Write Wait State */
#define CHIP_FLASH_WRITE_WAIT_STATE     (6U)

/* Embedded Flash Read Wait State (VDDCORE set at 1.8V) */
#define CHIP_FREQ_FWS_0                 (19000000UL) /**< \brief Maximum operating frequency when FWS is 0 */
#define CHIP_FREQ_FWS_1                 (50000000UL) /**< \brief Maximum operating frequency when FWS is 1 */
#define CHIP_FREQ_FWS_2                 (64000000UL) /**< \brief Maximum operating frequency when FWS is 2 */
#define CHIP_FREQ_FWS_3                 (80000000UL) /**< \brief Maximum operating frequency when FWS is 3 */
#define CHIP_FREQ_FWS_4                 (90000000UL) /**< \brief Maximum operating frequency when FWS is 4 */
  
 
#define CKGR_MOR_MOSCRCF_4_MHz   (0x0u << 4)
#define CKGR_MOR_MOSCRCF_8_MHz   (0x1u << 4)
#define CKGR_MOR_MOSCRCF_12_MHz   (0x2u << 4)

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAM3X8E */
/* ************************************************************************** */
/** \addtogroup SAM3X8E_base Peripheral Base Address Definitions */
/*@{*/

#define HSMCI      CAST(Hsmci     , 0x40000000U) /**< \brief (HSMCI     ) Base Address */
#define SSC        CAST(Ssc       , 0x40004000U) /**< \brief (SSC       ) Base Address */
#define SPI0       CAST(Spi       , 0x40008000U) /**< \brief (SPI0      ) Base Address */
#define TC0        CAST(Tc        , 0x40080000U) /**< \brief (TC0       ) Base Address */
#define TC1        CAST(Tc        , 0x40084000U) /**< \brief (TC1       ) Base Address */
#define TC2        CAST(Tc        , 0x40088000U) /**< \brief (TC2       ) Base Address */
#define TWI0       CAST(Twi       , 0x4008C000U) /**< \brief (TWI0      ) Base Address */
#define PDC_TWI0   CAST(Pdc       , 0x4008C100U) /**< \brief (PDC_TWI0  ) Base Address */
#define TWI1       CAST(Twi       , 0x40090000U) /**< \brief (TWI1      ) Base Address */
#define PDC_TWI1   CAST(Pdc       , 0x40090100U) /**< \brief (PDC_TWI1  ) Base Address */
#define PWM        CAST(Pwm       , 0x40094000U) /**< \brief (PWM       ) Base Address */
#define PDC_PWM    CAST(Pdc       , 0x40094100U) /**< \brief (PDC_PWM   ) Base Address */
#define USART0     CAST(Usart     , 0x40098000U) /**< \brief (USART0    ) Base Address */
#define PDC_USART0 CAST(Pdc       , 0x40098100U) /**< \brief (PDC_USART0) Base Address */
#define USART1     CAST(Usart     , 0x4009C000U) /**< \brief (USART1    ) Base Address */
#define PDC_USART1 CAST(Pdc       , 0x4009C100U) /**< \brief (PDC_USART1) Base Address */
#define USART2     CAST(Usart     , 0x400A0000U) /**< \brief (USART2    ) Base Address */
#define PDC_USART2 CAST(Pdc       , 0x400A0100U) /**< \brief (PDC_USART2) Base Address */
#define USART3     CAST(Usart     , 0x400A4000U) /**< \brief (USART3    ) Base Address */
#define PDC_USART3 CAST(Pdc       , 0x400A4100U) /**< \brief (PDC_USART3) Base Address */
#define UOTGHS     CAST(Uotghs    , 0x400AC000U) /**< \brief (UOTGHS    ) Base Address */
#define EMAC       CAST(Emac      , 0x400B0000U) /**< \brief (EMAC      ) Base Address */
#define CAN0       CAST(Can       , 0x400B4000U) /**< \brief (CAN0      ) Base Address */
#define CAN1       CAST(Can       , 0x400B8000U) /**< \brief (CAN1      ) Base Address */
#define TRNG       CAST(Trng      , 0x400BC000U) /**< \brief (TRNG      ) Base Address */
#define ADC        CAST(Adc       , 0x400C0000U) /**< \brief (ADC       ) Base Address */
#define PDC_ADC    CAST(Pdc       , 0x400C0100U) /**< \brief (PDC_ADC   ) Base Address */
#define DMAC       CAST(Dmac      , 0x400C4000U) /**< \brief (DMAC      ) Base Address */
#define DACC       CAST(Dacc      , 0x400C8000U) /**< \brief (DACC      ) Base Address */
#define PDC_DACC   CAST(Pdc       , 0x400C8100U) /**< \brief (PDC_DACC  ) Base Address */
#define SMC        CAST(Smc       , 0x400E0000U) /**< \brief (SMC       ) Base Address */
#define MATRIX     CAST(Matrix    , 0x400E0400U) /**< \brief (MATRIX    ) Base Address */
#define PMC        CAST(Pmc       , 0x400E0600U) /**< \brief (PMC       ) Base Address */
#define UART       CAST(Uart      , 0x400E0800U) /**< \brief (UART      ) Base Address */
#define PDC_UART   CAST(Pdc       , 0x400E0900U) /**< \brief (PDC_UART  ) Base Address */
#define CHIPID     CAST(Chipid    , 0x400E0940U) /**< \brief (CHIPID    ) Base Address */
#define EFC0       CAST(Efc       , 0x400E0A00U) /**< \brief (EFC0      ) Base Address */
#define EFC1       CAST(Efc       , 0x400E0C00U) /**< \brief (EFC1      ) Base Address */
#define PIOA       CAST(Pio       , 0x400E0E00U) /**< \brief (PIOA      ) Base Address */
#define PIOB       CAST(Pio       , 0x400E1000U) /**< \brief (PIOB      ) Base Address */
#define PIOC       CAST(Pio       , 0x400E1200U) /**< \brief (PIOC      ) Base Address */
#define PIOD       CAST(Pio       , 0x400E1400U) /**< \brief (PIOD      ) Base Address */
#define RSTC       CAST(Rstc      , 0x400E1A00U) /**< \brief (RSTC      ) Base Address */
#define SUPC       CAST(Supc      , 0x400E1A10U) /**< \brief (SUPC      ) Base Address */
#define RTT        CAST(Rtt       , 0x400E1A30U) /**< \brief (RTT       ) Base Address */
#define WDT        CAST(Wdt       , 0x400E1A50U) /**< \brief (WDT       ) Base Address */
#define RTC        CAST(Rtc       , 0x400E1A60U) /**< \brief (RTC       ) Base Address */
#define GPBR       CAST(Gpbr      , 0x400E1A90U) /**< \brief (GPBR      ) Base Address */

  /** \brief Efc hardware registers */
typedef struct {
  RwReg EEFC_FMR; /**< \brief (Efc Offset: 0x00) EEFC Flash Mode Register */
  WoReg EEFC_FCR; /**< \brief (Efc Offset: 0x04) EEFC Flash Command Register */
  RoReg EEFC_FSR; /**< \brief (Efc Offset: 0x08) EEFC Flash Status Register */
  RoReg EEFC_FRR; /**< \brief (Efc Offset: 0x0C) EEFC Flash Result Register */
} Efc;


/** \brief Pmc hardware registers */
typedef struct {
  WoReg PMC_SCER;      /**< \brief (Pmc Offset: 0x0000) System Clock Enable Register */
  WoReg PMC_SCDR;      /**< \brief (Pmc Offset: 0x0004) System Clock Disable Register */
  RoReg PMC_SCSR;      /**< \brief (Pmc Offset: 0x0008) System Clock Status Register */
  RoReg Reserved1[1];
  WoReg PMC_PCER0;     /**< \brief (Pmc Offset: 0x0010) Peripheral Clock Enable Register 0 */
  WoReg PMC_PCDR0;     /**< \brief (Pmc Offset: 0x0014) Peripheral Clock Disable Register 0 */
  RoReg PMC_PCSR0;     /**< \brief (Pmc Offset: 0x0018) Peripheral Clock Status Register 0 */
  RwReg CKGR_UCKR;     /**< \brief (Pmc Offset: 0x001C) UTMI Clock Register */
  RwReg CKGR_MOR;      /**< \brief (Pmc Offset: 0x0020) Main Oscillator Register */
  RoReg CKGR_MCFR;     /**< \brief (Pmc Offset: 0x0024) Main Clock Frequency Register */
  RwReg CKGR_PLLAR;    /**< \brief (Pmc Offset: 0x0028) PLLA Register */
  RoReg Reserved2[1];
  RwReg PMC_MCKR;      /**< \brief (Pmc Offset: 0x0030) Master Clock Register */
  RoReg Reserved3[1];
  RwReg PMC_USB;       /**< \brief (Pmc Offset: 0x0038) USB Clock Register */
  RoReg Reserved4[1];
  RwReg PMC_PCK[3];    /**< \brief (Pmc Offset: 0x0040) Programmable Clock 0 Register */
  RoReg Reserved5[5];
  WoReg PMC_IER;       /**< \brief (Pmc Offset: 0x0060) Interrupt Enable Register */
  WoReg PMC_IDR;       /**< \brief (Pmc Offset: 0x0064) Interrupt Disable Register */
  RoReg PMC_SR;        /**< \brief (Pmc Offset: 0x0068) Status Register */
  RoReg PMC_IMR;       /**< \brief (Pmc Offset: 0x006C) Interrupt Mask Register */
  RwReg PMC_FSMR;      /**< \brief (Pmc Offset: 0x0070) Fast Startup Mode Register */
  RwReg PMC_FSPR;      /**< \brief (Pmc Offset: 0x0074) Fast Startup Polarity Register */
  WoReg PMC_FOCR;      /**< \brief (Pmc Offset: 0x0078) Fault Output Clear Register */
  RoReg Reserved6[26];
  RwReg PMC_WPMR;      /**< \brief (Pmc Offset: 0x00E4) Write Protect Mode Register */
  RoReg PMC_WPSR;      /**< \brief (Pmc Offset: 0x00E8) Write Protect Status Register */
  RoReg Reserved7[5];
  WoReg PMC_PCER1;     /**< \brief (Pmc Offset: 0x0100) Peripheral Clock Enable Register 1 */
  WoReg PMC_PCDR1;     /**< \brief (Pmc Offset: 0x0104) Peripheral Clock Disable Register 1 */
  RoReg PMC_PCSR1;     /**< \brief (Pmc Offset: 0x0108) Peripheral Clock Status Register 1 */
  RwReg PMC_PCR;       /**< \brief (Pmc Offset: 0x010C) Peripheral Control Register */
} Pmc;
/* -------- PMC_SCER : (PMC Offset: 0x0000) System Clock Enable Register -------- */
#define PMC_SCER_UOTGCK (0x1u << 5) /**< \brief (PMC_SCER) Enable USB OTG Clock (48 MHz, USB_48M) for UTMI */
#define PMC_SCER_PCK0 (0x1u << 8) /**< \brief (PMC_SCER) Programmable Clock 0 Output Enable */
#define PMC_SCER_PCK1 (0x1u << 9) /**< \brief (PMC_SCER) Programmable Clock 1 Output Enable */
#define PMC_SCER_PCK2 (0x1u << 10) /**< \brief (PMC_SCER) Programmable Clock 2 Output Enable */
/* -------- PMC_SCDR : (PMC Offset: 0x0004) System Clock Disable Register -------- */
#define PMC_SCDR_UOTGCK (0x1u << 5) /**< \brief (PMC_SCDR) Disable USB OTG Clock (48 MHz, USB_48M) for UTMI */
#define PMC_SCDR_PCK0 (0x1u << 8) /**< \brief (PMC_SCDR) Programmable Clock 0 Output Disable */
#define PMC_SCDR_PCK1 (0x1u << 9) /**< \brief (PMC_SCDR) Programmable Clock 1 Output Disable */
#define PMC_SCDR_PCK2 (0x1u << 10) /**< \brief (PMC_SCDR) Programmable Clock 2 Output Disable */
/* -------- PMC_SCSR : (PMC Offset: 0x0008) System Clock Status Register -------- */
#define PMC_SCSR_UOTGCK (0x1u << 5) /**< \brief (PMC_SCSR) USB OTG Clock (48 MHz, USB_48M) for UTMI */
#define   PMC_SCSR_UOTGCK_DISABLE (0x0u << 5) /**< \brief (PMC_SCSR) USB_48M is disabled in normal operation mode. */
#define   PMC_SCSR_UOTGCK_ENABLE (0x1u << 5) /**< \brief (PMC_SCSR) Enable USB_48M (to use if SPDCONF =1). */
#define PMC_SCSR_PCK0 (0x1u << 8) /**< \brief (PMC_SCSR) Programmable Clock 0 Output Status */
#define PMC_SCSR_PCK1 (0x1u << 9) /**< \brief (PMC_SCSR) Programmable Clock 1 Output Status */
#define PMC_SCSR_PCK2 (0x1u << 10) /**< \brief (PMC_SCSR) Programmable Clock 2 Output Status */
/* -------- PMC_PCER0 : (PMC Offset: 0x0010) Peripheral Clock Enable Register 0 -------- */
#define PMC_PCER0_PID8 (0x1u << 8) /**< \brief (PMC_PCER0) Peripheral Clock 8 Enable */
#define PMC_PCER0_PID9 (0x1u << 9) /**< \brief (PMC_PCER0) Peripheral Clock 9 Enable */
#define PMC_PCER0_PID10 (0x1u << 10) /**< \brief (PMC_PCER0) Peripheral Clock 10 Enable */
#define PMC_PCER0_PID11 (0x1u << 11) /**< \brief (PMC_PCER0) Peripheral Clock 11 Enable */
#define PMC_PCER0_PID12 (0x1u << 12) /**< \brief (PMC_PCER0) Peripheral Clock 12 Enable */
#define PMC_PCER0_PID13 (0x1u << 13) /**< \brief (PMC_PCER0) Peripheral Clock 13 Enable */
#define PMC_PCER0_PID14 (0x1u << 14) /**< \brief (PMC_PCER0) Peripheral Clock 14 Enable */
#define PMC_PCER0_PID15 (0x1u << 15) /**< \brief (PMC_PCER0) Peripheral Clock 15 Enable */
#define PMC_PCER0_PID16 (0x1u << 16) /**< \brief (PMC_PCER0) Peripheral Clock 16 Enable */
#define PMC_PCER0_PID17 (0x1u << 17) /**< \brief (PMC_PCER0) Peripheral Clock 17 Enable */
#define PMC_PCER0_PID18 (0x1u << 18) /**< \brief (PMC_PCER0) Peripheral Clock 18 Enable */
#define PMC_PCER0_PID19 (0x1u << 19) /**< \brief (PMC_PCER0) Peripheral Clock 19 Enable */
#define PMC_PCER0_PID20 (0x1u << 20) /**< \brief (PMC_PCER0) Peripheral Clock 20 Enable */
#define PMC_PCER0_PID21 (0x1u << 21) /**< \brief (PMC_PCER0) Peripheral Clock 21 Enable */
#define PMC_PCER0_PID22 (0x1u << 22) /**< \brief (PMC_PCER0) Peripheral Clock 22 Enable */
#define PMC_PCER0_PID23 (0x1u << 23) /**< \brief (PMC_PCER0) Peripheral Clock 23 Enable */
#define PMC_PCER0_PID24 (0x1u << 24) /**< \brief (PMC_PCER0) Peripheral Clock 24 Enable */
#define PMC_PCER0_PID25 (0x1u << 25) /**< \brief (PMC_PCER0) Peripheral Clock 25 Enable */
#define PMC_PCER0_PID26 (0x1u << 26) /**< \brief (PMC_PCER0) Peripheral Clock 26 Enable */
#define PMC_PCER0_PID27 (0x1u << 27) /**< \brief (PMC_PCER0) Peripheral Clock 27 Enable */
#define PMC_PCER0_PID28 (0x1u << 28) /**< \brief (PMC_PCER0) Peripheral Clock 28 Enable */
#define PMC_PCER0_PID29 (0x1u << 29) /**< \brief (PMC_PCER0) Peripheral Clock 29 Enable */
#define PMC_PCER0_PID30 (0x1u << 30) /**< \brief (PMC_PCER0) Peripheral Clock 30 Enable */
#define PMC_PCER0_PID31 (0x1u << 31) /**< \brief (PMC_PCER0) Peripheral Clock 31 Enable */
/* -------- PMC_PCDR0 : (PMC Offset: 0x0014) Peripheral Clock Disable Register 0 -------- */
#define PMC_PCDR0_PID8 (0x1u << 8) /**< \brief (PMC_PCDR0) Peripheral Clock 8 Disable */
#define PMC_PCDR0_PID9 (0x1u << 9) /**< \brief (PMC_PCDR0) Peripheral Clock 9 Disable */
#define PMC_PCDR0_PID10 (0x1u << 10) /**< \brief (PMC_PCDR0) Peripheral Clock 10 Disable */
#define PMC_PCDR0_PID11 (0x1u << 11) /**< \brief (PMC_PCDR0) Peripheral Clock 11 Disable */
#define PMC_PCDR0_PID12 (0x1u << 12) /**< \brief (PMC_PCDR0) Peripheral Clock 12 Disable */
#define PMC_PCDR0_PID13 (0x1u << 13) /**< \brief (PMC_PCDR0) Peripheral Clock 13 Disable */
#define PMC_PCDR0_PID14 (0x1u << 14) /**< \brief (PMC_PCDR0) Peripheral Clock 14 Disable */
#define PMC_PCDR0_PID15 (0x1u << 15) /**< \brief (PMC_PCDR0) Peripheral Clock 15 Disable */
#define PMC_PCDR0_PID16 (0x1u << 16) /**< \brief (PMC_PCDR0) Peripheral Clock 16 Disable */
#define PMC_PCDR0_PID17 (0x1u << 17) /**< \brief (PMC_PCDR0) Peripheral Clock 17 Disable */
#define PMC_PCDR0_PID18 (0x1u << 18) /**< \brief (PMC_PCDR0) Peripheral Clock 18 Disable */
#define PMC_PCDR0_PID19 (0x1u << 19) /**< \brief (PMC_PCDR0) Peripheral Clock 19 Disable */
#define PMC_PCDR0_PID20 (0x1u << 20) /**< \brief (PMC_PCDR0) Peripheral Clock 20 Disable */
#define PMC_PCDR0_PID21 (0x1u << 21) /**< \brief (PMC_PCDR0) Peripheral Clock 21 Disable */
#define PMC_PCDR0_PID22 (0x1u << 22) /**< \brief (PMC_PCDR0) Peripheral Clock 22 Disable */
#define PMC_PCDR0_PID23 (0x1u << 23) /**< \brief (PMC_PCDR0) Peripheral Clock 23 Disable */
#define PMC_PCDR0_PID24 (0x1u << 24) /**< \brief (PMC_PCDR0) Peripheral Clock 24 Disable */
#define PMC_PCDR0_PID25 (0x1u << 25) /**< \brief (PMC_PCDR0) Peripheral Clock 25 Disable */
#define PMC_PCDR0_PID26 (0x1u << 26) /**< \brief (PMC_PCDR0) Peripheral Clock 26 Disable */
#define PMC_PCDR0_PID27 (0x1u << 27) /**< \brief (PMC_PCDR0) Peripheral Clock 27 Disable */
#define PMC_PCDR0_PID28 (0x1u << 28) /**< \brief (PMC_PCDR0) Peripheral Clock 28 Disable */
#define PMC_PCDR0_PID29 (0x1u << 29) /**< \brief (PMC_PCDR0) Peripheral Clock 29 Disable */
#define PMC_PCDR0_PID30 (0x1u << 30) /**< \brief (PMC_PCDR0) Peripheral Clock 30 Disable */
#define PMC_PCDR0_PID31 (0x1u << 31) /**< \brief (PMC_PCDR0) Peripheral Clock 31 Disable */
/* -------- PMC_PCSR0 : (PMC Offset: 0x0018) Peripheral Clock Status Register 0 -------- */
#define PMC_PCSR0_PID8 (0x1u << 8) /**< \brief (PMC_PCSR0) Peripheral Clock 8 Status */
#define PMC_PCSR0_PID9 (0x1u << 9) /**< \brief (PMC_PCSR0) Peripheral Clock 9 Status */
#define PMC_PCSR0_PID10 (0x1u << 10) /**< \brief (PMC_PCSR0) Peripheral Clock 10 Status */
#define PMC_PCSR0_PID11 (0x1u << 11) /**< \brief (PMC_PCSR0) Peripheral Clock 11 Status */
#define PMC_PCSR0_PID12 (0x1u << 12) /**< \brief (PMC_PCSR0) Peripheral Clock 12 Status */
#define PMC_PCSR0_PID13 (0x1u << 13) /**< \brief (PMC_PCSR0) Peripheral Clock 13 Status */
#define PMC_PCSR0_PID14 (0x1u << 14) /**< \brief (PMC_PCSR0) Peripheral Clock 14 Status */
#define PMC_PCSR0_PID15 (0x1u << 15) /**< \brief (PMC_PCSR0) Peripheral Clock 15 Status */
#define PMC_PCSR0_PID16 (0x1u << 16) /**< \brief (PMC_PCSR0) Peripheral Clock 16 Status */
#define PMC_PCSR0_PID17 (0x1u << 17) /**< \brief (PMC_PCSR0) Peripheral Clock 17 Status */
#define PMC_PCSR0_PID18 (0x1u << 18) /**< \brief (PMC_PCSR0) Peripheral Clock 18 Status */
#define PMC_PCSR0_PID19 (0x1u << 19) /**< \brief (PMC_PCSR0) Peripheral Clock 19 Status */
#define PMC_PCSR0_PID20 (0x1u << 20) /**< \brief (PMC_PCSR0) Peripheral Clock 20 Status */
#define PMC_PCSR0_PID21 (0x1u << 21) /**< \brief (PMC_PCSR0) Peripheral Clock 21 Status */
#define PMC_PCSR0_PID22 (0x1u << 22) /**< \brief (PMC_PCSR0) Peripheral Clock 22 Status */
#define PMC_PCSR0_PID23 (0x1u << 23) /**< \brief (PMC_PCSR0) Peripheral Clock 23 Status */
#define PMC_PCSR0_PID24 (0x1u << 24) /**< \brief (PMC_PCSR0) Peripheral Clock 24 Status */
#define PMC_PCSR0_PID25 (0x1u << 25) /**< \brief (PMC_PCSR0) Peripheral Clock 25 Status */
#define PMC_PCSR0_PID26 (0x1u << 26) /**< \brief (PMC_PCSR0) Peripheral Clock 26 Status */
#define PMC_PCSR0_PID27 (0x1u << 27) /**< \brief (PMC_PCSR0) Peripheral Clock 27 Status */
#define PMC_PCSR0_PID28 (0x1u << 28) /**< \brief (PMC_PCSR0) Peripheral Clock 28 Status */
#define PMC_PCSR0_PID29 (0x1u << 29) /**< \brief (PMC_PCSR0) Peripheral Clock 29 Status */
#define PMC_PCSR0_PID30 (0x1u << 30) /**< \brief (PMC_PCSR0) Peripheral Clock 30 Status */
#define PMC_PCSR0_PID31 (0x1u << 31) /**< \brief (PMC_PCSR0) Peripheral Clock 31 Status */
/* -------- CKGR_UCKR : (PMC Offset: 0x001C) UTMI Clock Register -------- */
#define CKGR_UCKR_UPLLEN (0x1u << 16) /**< \brief (CKGR_UCKR) UTMI PLL Enable */
#define CKGR_UCKR_UPLLCOUNT_Pos 20
#define CKGR_UCKR_UPLLCOUNT_Msk (0xfu << CKGR_UCKR_UPLLCOUNT_Pos) /**< \brief (CKGR_UCKR) UTMI PLL Start-up Time */
#define CKGR_UCKR_UPLLCOUNT(value) ((CKGR_UCKR_UPLLCOUNT_Msk & ((value) << CKGR_UCKR_UPLLCOUNT_Pos)))
/* -------- CKGR_MOR : (PMC Offset: 0x0020) Main Oscillator Register -------- */
#define CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CKGR_MOR) Main Crystal Oscillator Enable */
#define CKGR_MOR_MOSCXTBY (0x1u << 1) /**< \brief (CKGR_MOR) Main Crystal Oscillator Bypass */
#define CKGR_MOR_WAITMODE (0x1u << 2) /**< \brief (CKGR_MOR) Wait Mode Command */
#define CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Enable */
#define CKGR_MOR_MOSCRCF_Pos 4
#define CKGR_MOR_MOSCRCF_Msk (0x7u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Frequency Selection */
#define   CKGR_MOR_MOSCRCF_4MHz (0x0u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 4 MHz (default) */
#define   CKGR_MOR_MOSCRCF_8MHz (0x1u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 8 MHz */
#define   CKGR_MOR_MOSCRCF_12MHz (0x2u << 4) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 12 MHz */
#define CKGR_MOR_MOSCXTST_Pos 8
#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))
#define CKGR_MOR_KEY_Pos 16
#define CKGR_MOR_KEY_Msk (0xffu << CKGR_MOR_KEY_Pos) /**< \brief (CKGR_MOR) Password */
#define CKGR_MOR_KEY(value) ((CKGR_MOR_KEY_Msk & ((value) << CKGR_MOR_KEY_Pos)))
#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
#define CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CKGR_MOR) Clock Failure Detector Enable */
/* -------- CKGR_MCFR : (PMC Offset: 0x0024) Main Clock Frequency Register -------- */
#define CKGR_MCFR_MAINF_Pos 0
#define CKGR_MCFR_MAINF_Msk (0xffffu << CKGR_MCFR_MAINF_Pos) /**< \brief (CKGR_MCFR) Main Clock Frequency */
#define CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CKGR_MCFR) Main Clock Ready */
/* -------- CKGR_PLLAR : (PMC Offset: 0x0028) PLLA Register -------- */
#define CKGR_PLLAR_DIVA_Pos 0
#define CKGR_PLLAR_DIVA_Msk (0xffu << CKGR_PLLAR_DIVA_Pos) /**< \brief (CKGR_PLLAR) Divider */
#define CKGR_PLLAR_DIVA(value) ((CKGR_PLLAR_DIVA_Msk & ((value) << CKGR_PLLAR_DIVA_Pos)))
#define CKGR_PLLAR_PLLACOUNT_Pos 8
#define CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CKGR_PLLAR) PLLA Counter */
#define CKGR_PLLAR_PLLACOUNT(value) ((CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos)))
#define CKGR_PLLAR_MULA_Pos 16
#define CKGR_PLLAR_MULA_Msk (0x7ffu << CKGR_PLLAR_MULA_Pos) /**< \brief (CKGR_PLLAR) PLLA Multiplier */
#define CKGR_PLLAR_MULA(value) ((CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos)))
#define CKGR_PLLAR_STUCKTO1 (0x1u << 29) /**< \brief (CKGR_PLLAR)  */
/* -------- PMC_MCKR : (PMC Offset: 0x0030) Master Clock Register -------- */
#define PMC_MCKR_CSS_Pos 0
#define PMC_MCKR_CSS_Msk (0x3u << PMC_MCKR_CSS_Pos) /**< \brief (PMC_MCKR) Master Clock Source Selection */
#define   PMC_MCKR_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_MCKR) Slow Clock is selected */
#define   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_MCKR) Main Clock is selected */
#define   PMC_MCKR_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_MCKR) PLLA Clock is selected */
#define   PMC_MCKR_CSS_UPLL_CLK (0x3u << 0) /**< \brief (PMC_MCKR) UPLL/2 Clock is selected */
#define PMC_MCKR_PRES_Pos 4
#define PMC_MCKR_PRES_Msk (0x7u << PMC_MCKR_PRES_Pos) /**< \brief (PMC_MCKR) Processor Clock Prescaler */
#define   PMC_MCKR_PRES_CLK_1 (0x0u << 4) /**< \brief (PMC_MCKR) Selected clock */
#define   PMC_MCKR_PRES_CLK_2 (0x1u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 2 */
#define   PMC_MCKR_PRES_CLK_4 (0x2u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 4 */
#define   PMC_MCKR_PRES_CLK_8 (0x3u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 8 */
#define   PMC_MCKR_PRES_CLK_16 (0x4u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 16 */
#define   PMC_MCKR_PRES_CLK_32 (0x5u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 32 */
#define   PMC_MCKR_PRES_CLK_64 (0x6u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 64 */
#define   PMC_MCKR_PRES_CLK_3 (0x7u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 3 */
#define PMC_MCKR_UPLLDIV (0x1u << 13) /**< \brief (PMC_MCKR) UPLL Divider */
/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
#define PMC_USB_USBS (0x1u << 0) /**< \brief (PMC_USB) USB Input Clock Selection */
#define PMC_USB_USBDIV_Pos 8
#define PMC_USB_USBDIV_Msk (0xfu << PMC_USB_USBDIV_Pos) /**< \brief (PMC_USB) Divider for USB Clock. */
#define PMC_USB_USBDIV(value) ((PMC_USB_USBDIV_Msk & ((value) << PMC_USB_USBDIV_Pos)))
/* -------- PMC_PCK[3] : (PMC Offset: 0x0040) Programmable Clock 0 Register -------- */
#define PMC_PCK_CSS_Pos 0
#define PMC_PCK_CSS_Msk (0x7u << PMC_PCK_CSS_Pos) /**< \brief (PMC_PCK[3]) Master Clock Source Selection */
#define   PMC_PCK_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_PCK[3]) Slow Clock is selected */
#define   PMC_PCK_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_PCK[3]) Main Clock is selected */
#define   PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_PCK[3]) PLLA Clock is selected */
#define   PMC_PCK_CSS_UPLL_CLK (0x3u << 0) /**< \brief (PMC_PCK[3]) UPLL/2 Clock is selected */
#define   PMC_PCK_CSS_MCK (0x4u << 0) /**< \brief (PMC_PCK[3]) Master Clock is selected */
#define PMC_PCK_PRES_Pos 4
#define PMC_PCK_PRES_Msk (0x7u << PMC_PCK_PRES_Pos) /**< \brief (PMC_PCK[3]) Programmable Clock Prescaler */
#define   PMC_PCK_PRES_CLK_1 (0x0u << 4) /**< \brief (PMC_PCK[3]) Selected clock */
#define   PMC_PCK_PRES_CLK_2 (0x1u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 2 */
#define   PMC_PCK_PRES_CLK_4 (0x2u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 4 */
#define   PMC_PCK_PRES_CLK_8 (0x3u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 8 */
#define   PMC_PCK_PRES_CLK_16 (0x4u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 16 */
#define   PMC_PCK_PRES_CLK_32 (0x5u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 32 */
#define   PMC_PCK_PRES_CLK_64 (0x6u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 64 */
/* -------- PMC_IER : (PMC Offset: 0x0060) Interrupt Enable Register -------- */
#define PMC_IER_MOSCXTS (0x1u << 0) /**< \brief (PMC_IER) Main Crystal Oscillator Status Interrupt Enable */
#define PMC_IER_LOCKA (0x1u << 1) /**< \brief (PMC_IER) PLL A Lock Interrupt Enable */
#define PMC_IER_MCKRDY (0x1u << 3) /**< \brief (PMC_IER) Master Clock Ready Interrupt Enable */
#define PMC_IER_LOCKU (0x1u << 6) /**< \brief (PMC_IER) UTMI PLL Lock Interrupt Enable */
#define PMC_IER_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IER) Programmable Clock Ready 0 Interrupt Enable */
#define PMC_IER_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IER) Programmable Clock Ready 1 Interrupt Enable */
#define PMC_IER_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IER) Programmable Clock Ready 2 Interrupt Enable */
#define PMC_IER_MOSCSELS (0x1u << 16) /**< \brief (PMC_IER) Main Oscillator Selection Status Interrupt Enable */
#define PMC_IER_MOSCRCS (0x1u << 17) /**< \brief (PMC_IER) Main On-Chip RC Status Interrupt Enable */
#define PMC_IER_CFDEV (0x1u << 18) /**< \brief (PMC_IER) Clock Failure Detector Event Interrupt Enable */
/* -------- PMC_IDR : (PMC Offset: 0x0064) Interrupt Disable Register -------- */
#define PMC_IDR_MOSCXTS (0x1u << 0) /**< \brief (PMC_IDR) Main Crystal Oscillator Status Interrupt Disable */
#define PMC_IDR_LOCKA (0x1u << 1) /**< \brief (PMC_IDR) PLL A Lock Interrupt Disable */
#define PMC_IDR_MCKRDY (0x1u << 3) /**< \brief (PMC_IDR) Master Clock Ready Interrupt Disable */
#define PMC_IDR_LOCKU (0x1u << 6) /**< \brief (PMC_IDR) UTMI PLL Lock Interrupt Disable */
#define PMC_IDR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IDR) Programmable Clock Ready 0 Interrupt Disable */
#define PMC_IDR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IDR) Programmable Clock Ready 1 Interrupt Disable */
#define PMC_IDR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IDR) Programmable Clock Ready 2 Interrupt Disable */
#define PMC_IDR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IDR) Main Oscillator Selection Status Interrupt Disable */
#define PMC_IDR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IDR) Main On-Chip RC Status Interrupt Disable */
#define PMC_IDR_CFDEV (0x1u << 18) /**< \brief (PMC_IDR) Clock Failure Detector Event Interrupt Disable */
/* -------- PMC_SR : (PMC Offset: 0x0068) Status Register -------- */
#define PMC_SR_MOSCXTS (0x1u << 0) /**< \brief (PMC_SR) Main XTAL Oscillator Status */
#define PMC_SR_LOCKA (0x1u << 1) /**< \brief (PMC_SR) PLL A Lock Status */
#define PMC_SR_MCKRDY (0x1u << 3) /**< \brief (PMC_SR) Master Clock Status */
#define PMC_SR_LOCKU (0x1u << 6) /**< \brief (PMC_SR) UTMI PLL Lock Status */
#define PMC_SR_OSCSELS (0x1u << 7) /**< \brief (PMC_SR) Slow Clock Oscillator Selection */
#define PMC_SR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_MOSCSELS (0x1u << 16) /**< \brief (PMC_SR) Main Oscillator Selection Status */
#define PMC_SR_MOSCRCS (0x1u << 17) /**< \brief (PMC_SR) Main On-Chip RC Oscillator Status */
#define PMC_SR_CFDEV (0x1u << 18) /**< \brief (PMC_SR) Clock Failure Detector Event */
#define PMC_SR_CFDS (0x1u << 19) /**< \brief (PMC_SR) Clock Failure Detector Status */
#define PMC_SR_FOS (0x1u << 20) /**< \brief (PMC_SR) Clock Failure Detector Fault Output Status */
/* -------- PMC_IMR : (PMC Offset: 0x006C) Interrupt Mask Register -------- */
#define PMC_IMR_MOSCXTS (0x1u << 0) /**< \brief (PMC_IMR) Main Crystal Oscillator Status Interrupt Mask */
#define PMC_IMR_LOCKA (0x1u << 1) /**< \brief (PMC_IMR) PLL A Lock Interrupt Mask */
#define PMC_IMR_MCKRDY (0x1u << 3) /**< \brief (PMC_IMR) Master Clock Ready Interrupt Mask */
#define PMC_IMR_LOCKU (0x1u << 6) /**< \brief (PMC_IMR) UTMI PLL Lock Interrupt Mask */
#define PMC_IMR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IMR) Programmable Clock Ready 0 Interrupt Mask */
#define PMC_IMR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IMR) Programmable Clock Ready 1 Interrupt Mask */
#define PMC_IMR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IMR) Programmable Clock Ready 2 Interrupt Mask */
#define PMC_IMR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IMR) Main Oscillator Selection Status Interrupt Mask */
#define PMC_IMR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IMR) Main On-Chip RC Status Interrupt Mask */
#define PMC_IMR_CFDEV (0x1u << 18) /**< \brief (PMC_IMR) Clock Failure Detector Event Interrupt Mask */
/* -------- PMC_FSMR : (PMC Offset: 0x0070) Fast Startup Mode Register -------- */
#define PMC_FSMR_FSTT0 (0x1u << 0) /**< \brief (PMC_FSMR) Fast Startup Input Enable 0 */
#define PMC_FSMR_FSTT1 (0x1u << 1) /**< \brief (PMC_FSMR) Fast Startup Input Enable 1 */
#define PMC_FSMR_FSTT2 (0x1u << 2) /**< \brief (PMC_FSMR) Fast Startup Input Enable 2 */
#define PMC_FSMR_FSTT3 (0x1u << 3) /**< \brief (PMC_FSMR) Fast Startup Input Enable 3 */
#define PMC_FSMR_FSTT4 (0x1u << 4) /**< \brief (PMC_FSMR) Fast Startup Input Enable 4 */
#define PMC_FSMR_FSTT5 (0x1u << 5) /**< \brief (PMC_FSMR) Fast Startup Input Enable 5 */
#define PMC_FSMR_FSTT6 (0x1u << 6) /**< \brief (PMC_FSMR) Fast Startup Input Enable 6 */
#define PMC_FSMR_FSTT7 (0x1u << 7) /**< \brief (PMC_FSMR) Fast Startup Input Enable 7 */
#define PMC_FSMR_FSTT8 (0x1u << 8) /**< \brief (PMC_FSMR) Fast Startup Input Enable 8 */
#define PMC_FSMR_FSTT9 (0x1u << 9) /**< \brief (PMC_FSMR) Fast Startup Input Enable 9 */
#define PMC_FSMR_FSTT10 (0x1u << 10) /**< \brief (PMC_FSMR) Fast Startup Input Enable 10 */
#define PMC_FSMR_FSTT11 (0x1u << 11) /**< \brief (PMC_FSMR) Fast Startup Input Enable 11 */
#define PMC_FSMR_FSTT12 (0x1u << 12) /**< \brief (PMC_FSMR) Fast Startup Input Enable 12 */
#define PMC_FSMR_FSTT13 (0x1u << 13) /**< \brief (PMC_FSMR) Fast Startup Input Enable 13 */
#define PMC_FSMR_FSTT14 (0x1u << 14) /**< \brief (PMC_FSMR) Fast Startup Input Enable 14 */
#define PMC_FSMR_FSTT15 (0x1u << 15) /**< \brief (PMC_FSMR) Fast Startup Input Enable 15 */
#define PMC_FSMR_RTTAL (0x1u << 16) /**< \brief (PMC_FSMR) RTT Alarm Enable */
#define PMC_FSMR_RTCAL (0x1u << 17) /**< \brief (PMC_FSMR) RTC Alarm Enable */
#define PMC_FSMR_USBAL (0x1u << 18) /**< \brief (PMC_FSMR) USB Alarm Enable */
#define PMC_FSMR_LPM (0x1u << 20) /**< \brief (PMC_FSMR) Low Power Mode */
/* -------- PMC_FSPR : (PMC Offset: 0x0074) Fast Startup Polarity Register -------- */
#define PMC_FSPR_FSTP0 (0x1u << 0) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP1 (0x1u << 1) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP2 (0x1u << 2) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP3 (0x1u << 3) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP4 (0x1u << 4) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP5 (0x1u << 5) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP6 (0x1u << 6) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP7 (0x1u << 7) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP8 (0x1u << 8) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP9 (0x1u << 9) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP10 (0x1u << 10) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP11 (0x1u << 11) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP12 (0x1u << 12) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP13 (0x1u << 13) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP14 (0x1u << 14) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
#define PMC_FSPR_FSTP15 (0x1u << 15) /**< \brief (PMC_FSPR) Fast Startup Input Polarity */
/* -------- PMC_FOCR : (PMC Offset: 0x0078) Fault Output Clear Register -------- */
#define PMC_FOCR_FOCLR (0x1u << 0) /**< \brief (PMC_FOCR) Fault Output Clear */
/* -------- PMC_WPMR : (PMC Offset: 0x00E4) Write Protect Mode Register -------- */
#define PMC_WPMR_WPEN (0x1u << 0) /**< \brief (PMC_WPMR) Write Protect Enable */
#define PMC_WPMR_WPKEY_Pos 8
#define PMC_WPMR_WPKEY_Msk (0xffffffu << PMC_WPMR_WPKEY_Pos) /**< \brief (PMC_WPMR) Write Protect KEY */
#define PMC_WPMR_WPKEY(value) ((PMC_WPMR_WPKEY_Msk & ((value) << PMC_WPMR_WPKEY_Pos)))
/* -------- PMC_WPSR : (PMC Offset: 0x00E8) Write Protect Status Register -------- */
#define PMC_WPSR_WPVS (0x1u << 0) /**< \brief (PMC_WPSR) Write Protect Violation Status */
#define PMC_WPSR_WPVSRC_Pos 8
#define PMC_WPSR_WPVSRC_Msk (0xffffu << PMC_WPSR_WPVSRC_Pos) /**< \brief (PMC_WPSR) Write Protect Violation Source */
/* -------- PMC_PCER1 : (PMC Offset: 0x0100) Peripheral Clock Enable Register 1 -------- */
#define PMC_PCER1_PID32 (0x1u << 0) /**< \brief (PMC_PCER1) Peripheral Clock 32 Enable */
#define PMC_PCER1_PID33 (0x1u << 1) /**< \brief (PMC_PCER1) Peripheral Clock 33 Enable */
#define PMC_PCER1_PID34 (0x1u << 2) /**< \brief (PMC_PCER1) Peripheral Clock 34 Enable */
#define PMC_PCER1_PID35 (0x1u << 3) /**< \brief (PMC_PCER1) Peripheral Clock 35 Enable */
#define PMC_PCER1_PID36 (0x1u << 4) /**< \brief (PMC_PCER1) Peripheral Clock 36 Enable */
#define PMC_PCER1_PID37 (0x1u << 5) /**< \brief (PMC_PCER1) Peripheral Clock 37 Enable */
#define PMC_PCER1_PID38 (0x1u << 6) /**< \brief (PMC_PCER1) Peripheral Clock 38 Enable */
#define PMC_PCER1_PID39 (0x1u << 7) /**< \brief (PMC_PCER1) Peripheral Clock 39 Enable */
#define PMC_PCER1_PID40 (0x1u << 8) /**< \brief (PMC_PCER1) Peripheral Clock 40 Enable */
#define PMC_PCER1_PID41 (0x1u << 9) /**< \brief (PMC_PCER1) Peripheral Clock 41 Enable */
#define PMC_PCER1_PID42 (0x1u << 10) /**< \brief (PMC_PCER1) Peripheral Clock 42 Enable */
#define PMC_PCER1_PID43 (0x1u << 11) /**< \brief (PMC_PCER1) Peripheral Clock 43 Enable */
#define PMC_PCER1_PID44 (0x1u << 12) /**< \brief (PMC_PCER1) Peripheral Clock 44 Enable */
/* -------- PMC_PCDR1 : (PMC Offset: 0x0104) Peripheral Clock Disable Register 1 -------- */
#define PMC_PCDR1_PID32 (0x1u << 0) /**< \brief (PMC_PCDR1) Peripheral Clock 32 Disable */
#define PMC_PCDR1_PID33 (0x1u << 1) /**< \brief (PMC_PCDR1) Peripheral Clock 33 Disable */
#define PMC_PCDR1_PID34 (0x1u << 2) /**< \brief (PMC_PCDR1) Peripheral Clock 34 Disable */
#define PMC_PCDR1_PID35 (0x1u << 3) /**< \brief (PMC_PCDR1) Peripheral Clock 35 Disable */
#define PMC_PCDR1_PID36 (0x1u << 4) /**< \brief (PMC_PCDR1) Peripheral Clock 36 Disable */
#define PMC_PCDR1_PID37 (0x1u << 5) /**< \brief (PMC_PCDR1) Peripheral Clock 37 Disable */
#define PMC_PCDR1_PID38 (0x1u << 6) /**< \brief (PMC_PCDR1) Peripheral Clock 38 Disable */
#define PMC_PCDR1_PID39 (0x1u << 7) /**< \brief (PMC_PCDR1) Peripheral Clock 39 Disable */
#define PMC_PCDR1_PID40 (0x1u << 8) /**< \brief (PMC_PCDR1) Peripheral Clock 40 Disable */
#define PMC_PCDR1_PID41 (0x1u << 9) /**< \brief (PMC_PCDR1) Peripheral Clock 41 Disable */
#define PMC_PCDR1_PID42 (0x1u << 10) /**< \brief (PMC_PCDR1) Peripheral Clock 42 Disable */
#define PMC_PCDR1_PID43 (0x1u << 11) /**< \brief (PMC_PCDR1) Peripheral Clock 43 Disable */
#define PMC_PCDR1_PID44 (0x1u << 12) /**< \brief (PMC_PCDR1) Peripheral Clock 44 Disable */
/* -------- PMC_PCSR1 : (PMC Offset: 0x0108) Peripheral Clock Status Register 1 -------- */
#define PMC_PCSR1_PID32 (0x1u << 0) /**< \brief (PMC_PCSR1) Peripheral Clock 32 Status */
#define PMC_PCSR1_PID33 (0x1u << 1) /**< \brief (PMC_PCSR1) Peripheral Clock 33 Status */
#define PMC_PCSR1_PID34 (0x1u << 2) /**< \brief (PMC_PCSR1) Peripheral Clock 34 Status */
#define PMC_PCSR1_PID35 (0x1u << 3) /**< \brief (PMC_PCSR1) Peripheral Clock 35 Status */
#define PMC_PCSR1_PID36 (0x1u << 4) /**< \brief (PMC_PCSR1) Peripheral Clock 36 Status */
#define PMC_PCSR1_PID37 (0x1u << 5) /**< \brief (PMC_PCSR1) Peripheral Clock 37 Status */
#define PMC_PCSR1_PID38 (0x1u << 6) /**< \brief (PMC_PCSR1) Peripheral Clock 38 Status */
#define PMC_PCSR1_PID39 (0x1u << 7) /**< \brief (PMC_PCSR1) Peripheral Clock 39 Status */
#define PMC_PCSR1_PID40 (0x1u << 8) /**< \brief (PMC_PCSR1) Peripheral Clock 40 Status */
#define PMC_PCSR1_PID41 (0x1u << 9) /**< \brief (PMC_PCSR1) Peripheral Clock 41 Status */
#define PMC_PCSR1_PID42 (0x1u << 10) /**< \brief (PMC_PCSR1) Peripheral Clock 42 Status */
#define PMC_PCSR1_PID43 (0x1u << 11) /**< \brief (PMC_PCSR1) Peripheral Clock 43 Status */
#define PMC_PCSR1_PID44 (0x1u << 12) /**< \brief (PMC_PCSR1) Peripheral Clock 44 Status */
/* -------- PMC_PCR : (PMC Offset: 0x010C) Peripheral Control Register -------- */
#define PMC_PCR_PID_Pos 0
#define PMC_PCR_PID_Msk (0x3fu << PMC_PCR_PID_Pos) /**< \brief (PMC_PCR) Peripheral ID */
#define PMC_PCR_PID(value) ((PMC_PCR_PID_Msk & ((value) << PMC_PCR_PID_Pos)))
#define PMC_PCR_CMD (0x1u << 12) /**< \brief (PMC_PCR) Command */
#define PMC_PCR_DIV_Pos 16
#define PMC_PCR_DIV_Msk (0x3u << PMC_PCR_DIV_Pos) /**< \brief (PMC_PCR) Divisor Value */
#define   PMC_PCR_DIV_PERIPH_DIV_MCK (0x0u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK */
#define   PMC_PCR_DIV_PERIPH_DIV2_MCK (0x1u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/2 */
#define   PMC_PCR_DIV_PERIPH_DIV4_MCK (0x2u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/4 */
#define PMC_PCR_EN (0x1u << 28) /**< \brief (PMC_PCR) Enable */

//#endif 
/* -------- EEFC_FMR : (EFC Offset: 0x00) EEFC Flash Mode Register -------- */
#define EEFC_FMR_FRDY (0x1u << 0) /**< \brief (EEFC_FMR) Ready Interrupt Enable */
#define EEFC_FMR_FWS_Pos 8
#define EEFC_FMR_FWS_Msk (0xfu << EEFC_FMR_FWS_Pos) /**< \brief (EEFC_FMR) Flash Wait State */
#define EEFC_FMR_FWS(value) ((EEFC_FMR_FWS_Msk & ((value) << EEFC_FMR_FWS_Pos)))
#define EEFC_FMR_SCOD (0x1u << 16) /**< \brief (EEFC_FMR) Sequential Code Optimization Disable */
#define EEFC_FMR_FAM (0x1u << 24) /**< \brief (EEFC_FMR) Flash Access Mode */
/* -------- EEFC_FCR : (EFC Offset: 0x04) EEFC Flash Command Register -------- */
#define EEFC_FCR_FCMD_Pos 0
#define EEFC_FCR_FCMD_Msk (0xffu << EEFC_FCR_FCMD_Pos) /**< \brief (EEFC_FCR) Flash Command */
#define EEFC_FCR_FCMD(value) ((EEFC_FCR_FCMD_Msk & ((value) << EEFC_FCR_FCMD_Pos)))
#define EEFC_FCR_FARG_Pos 8
#define EEFC_FCR_FARG_Msk (0xffffu << EEFC_FCR_FARG_Pos) /**< \brief (EEFC_FCR) Flash Command Argument */
#define EEFC_FCR_FARG(value) ((EEFC_FCR_FARG_Msk & ((value) << EEFC_FCR_FARG_Pos)))
#define EEFC_FCR_FKEY_Pos 24
#define EEFC_FCR_FKEY_Msk (0xffu << EEFC_FCR_FKEY_Pos) /**< \brief (EEFC_FCR) Flash Writing Protection Key */
#define EEFC_FCR_FKEY(value) ((EEFC_FCR_FKEY_Msk & ((value) << EEFC_FCR_FKEY_Pos)))
/* -------- EEFC_FSR : (EFC Offset: 0x08) EEFC Flash Status Register -------- */
#define EEFC_FSR_FRDY (0x1u << 0) /**< \brief (EEFC_FSR) Flash Ready Status */
#define EEFC_FSR_FCMDE (0x1u << 1) /**< \brief (EEFC_FSR) Flash Command Error Status */
#define EEFC_FSR_FLOCKE (0x1u << 2) /**< \brief (EEFC_FSR) Flash Lock Error Status */
/* -------- EEFC_FRR : (EFC Offset: 0x0C) EEFC Flash Result Register -------- */
#define EEFC_FRR_FVALUE_Pos 0
#define EEFC_FRR_FVALUE_Msk (0xffffffffu << EEFC_FRR_FVALUE_Pos) /**< \brief (EEFC_FRR) Flash Result Value */


  
extern uint32_t SystemCoreClock;	/* System Clock Frequency (Core Clock) */

/**
 * @brief Setup the microcontroller system.
 * Initialize the System and update the SystemCoreClock variable.
 */
void SystemInit(void);

/**
 * @brief Updates the SystemCoreClock with current core Clock 
 * retrieved from cpu registers.
 */
void SystemCoreClockUpdate(void);

/** 
 * Initialize flash.
 */
void system_init_flash(uint32_t ul_clk);



#endif /* SYSTEM_SAM3X_H_INCLUDED */
