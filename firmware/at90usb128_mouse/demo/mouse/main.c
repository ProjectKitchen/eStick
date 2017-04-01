//!
//! @file main.c,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief Main for USB application.
//!
//! @version 1.6 at90usb128-demo-mouse-1_0_3 $Id: main.c,v 1.6 2006/08/02 09:41:50 rletendu Exp $
//!
//! @mainpage AT90USBxxx Mouse demonstration
//!
//! @section intro License
//! Use of this program is subject to Atmel's End User License Agreement.
//!
//! Please read file  \ref lic_page for copyright notice.
//!
//! @section install Description
//! This embedded application source code illustrates how to implement a HID mouse application
//! over the AT90USBxxx controller.
//!
//! @section sample About the sample application
//! By default the sample code is delivered configured for STK525, but
//! this sample application can be configured for both STK525 or AT90USBKey hardware, see #TARGET_BOARD
//! define value in config.h file.
//!
//! @section src_code About the source code
//! This source code is usable with the following compilers:
//! - IAR Embedded Workbench (4.20a and higher)
//! - AVRGCC (WinAVR 20060421), please read \ref GCC_page.
//!
//! Support for other compilers may required modifications or attention for:
//! - compiler.h file 
//! - special registers declaration file
//! - interrupt subroutines declarations
//!
//! @section arch Architecture
//! As illustrated in the figure bellow, the application entry point is located is the main.c file.
//! The main function first performs the initialization of a scheduler module and then runs it in an infinite loop.
//! The scheduler is a simple infinite loop calling all its tasks defined in the conf_scheduler.h file.
//! No real time schedule is performed, when a task ends, the scheduler calls the next task defined in
//! the configuration file (conf_scheduler.h).
//!
//! The sample dual role application is based on two different tasks:
//! - The usb_task  (usb_task.c associated source file), is the task performing the USB low level
//! enumeration process in device mode.
//! - The mouse task performs mouse events decoding and report construction to the USB host.
//!
//! \image html arch_full.gif
//!

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "modules/scheduler/scheduler.h"
#include "lib_mcu/wdt/wdt_drv.h"
#include "lib_mcu/power/power_drv.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

int main(void)
{
#ifndef  AVRGCC
   Wdt_off();
#else
   wdt_reset();
   Wdt_clear_flag();
   Wdt_change_enable();
   Wdt_stop();
#endif
   Clear_prescaler();
   scheduler();
	return 0;
}

