//! @file conf_usb.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the possible external configuration of the USB
//!
//!
//! @version 1.1 at90usb162-hidgen-1_0_1 $Id: conf_usb.h,v 1.1 2006/12/12 09:48:05 arobert Exp $
//!
//! @todo
//! @bug
#ifndef _CONF_USB_H_
#define _CONF_USB_H_

//! @defgroup usb_general_conf USB application configuration
//!
//! @{
   // _________________ USB MODE CONFIGURATION ____________________________
   //
   //! @defgroup USB_op_mode USB operating modes configuration
   //! defines to enable device or host usb operating modes
   //! supported by the application
   //! @{

      //! @brief ENABLE to activate the device software library support
      //!
      //! Possible values ENABLE or DISABLE
      #define USB_DEVICE_FEATURE          ENABLED

   //! @}
   // _________________ USB REGULATOR CONFIGURATION _______________________
   //
   //! @defgroup USB_reg_mode USB regulator configuration
   //! @{

   //! @brief Enable the internal regulator for USB pads
   //!
   //! When the application voltage is lower than 3.5V, to optimize power consumption
   //! the internal USB pads regulatr can be disabled.
#ifndef USE_USB_PADS_REGULATOR
//   #define USE_USB_PADS_REGULATOR   ENABLE      // Possible values ENABLE or DISABLE
   #define USE_USB_PADS_REGULATOR   DISABLE      // Possible values ENABLE or DISABLE
#endif
   //! @}




// _________________ DEVICE MODE CONFIGURATION __________________________

   //! @defgroup USB_device_mode_cfg USB device operating mode configuration
   //!
   //! @{

#define Usb_unicode(a)			((U16)(a))

#define NB_ENDPOINTS          2  // number of endpoints in the application
#define EP_HID_IN             1
#define EP_HID_OUT            2

#define USB_REMOTE_WAKEUP     DISABLED   //! don't allow remote wake up

#define VBUS_SENSING_IO       DISABLED   //! device will connect directly on reset

#define USB_RESET_CPU         DISABLED   //! an USB reset does not reset the CPU

   //! @defgroup device_cst_actions USB device custom actions
   //!
   //! @{
   // write here the action to associate to each USB event
   // be carefull not to waste time in order not disturbing the functions
#define Usb_sof_action()         sof_action();
#define Usb_wake_up_action()
#define Usb_resume_action()
#define Usb_suspend_action()
#define Usb_reset_action()
#define Usb_vbus_on_action()
#define Usb_vbus_off_action()
#define Usb_set_configuration_action()
   //! @}

extern void sof_action(void);
   //! @}

//! @}

#endif // _CONF_USB_H_
