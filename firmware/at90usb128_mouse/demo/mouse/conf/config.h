//! @file config.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the system configuration definition
//!
//! @version 1.1 at90usb128-demo-mouse-1_0_3 $Id: config.h,v 1.1 2006/03/14 12:25:22 rletendu Exp $
//!
//! @todo
//! @bug

#ifndef _CONFIG_H_
#define _CONFIG_H_

//! @defgroup global_config Application configuration
//! @{

//_____ I N C L U D E S ____________________________________________________


#ifdef AVRGCC
   #define __AVR_AT90USBxxx__
#endif

#include "lib_mcu\compiler.h" //!< Compiler definitions


#ifdef AVRGCC
   #include <avr/io.h>
#else
   #include "lib_mcu\mcu.h" //!< Register declaration
#endif
#include "conf/conf_scheduler.h" //!< Scheduler tasks declaration

#define  STK525   0
#define  USBKEY   1

//! Enable or not the ADC usage
#define  USE_ADC
//! To include proper target hardware definitions, select
//! target board (USBKEY or STK525)
#define TARGET_BOARD STK525

#if (TARGET_BOARD==USBKEY)
   //! @warning for #define USBKEY_HAS_321_DF, only first prototypes versions have AT45DB321C memories
   //! should be undefined for std series
   #define USBKEY_HAS_321_DF
   #include "lib_board\usb_key\usb_key.h"
#elif (TARGET_BOARD==STK525)
   #include "lib_board\stk_525\stk_525.h"
#else
   #error TARGET_BOARD must be defined somewhere
#endif


//! CPU core frequency in kHz
#define FOSC 8000


// -------- END Generic Configuration -------------------------------------

// UART Sample configuration, if we have one ... __________________________
#define BAUDRATE        57600
#define USE_UART2

#define uart_putchar putchar
#define r_uart_ptchar int
#define p_uart_ptchar int


// ADC Sample configuration, if we have one ... ___________________________

//! ADC Prescaler value
#define ADC_PRESCALER 64
//! Right adjust
#define ADC_RIGHT_ADJUST_RESULT 1
//! AVCC As reference voltage (See adc_drv.h)
#define ADC_INTERNAL_VREF  2

//!Mouse configuration
#define NB_IDLE_POLLING_SOF  3   //!10ms before looking for new mouse hardware event
#define MOUSE_SPEED          1

//! @}

#endif // _CONFIG_H_

