//! @file usb_standard_request.h,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @briefProcess USB device enumeration requests header file.
//!
//! This file contains the USB endpoint 0 management routines corresponding to
//! the standard enumeration process (refer to chapter 9 of the USB
//! specification.
//! This file calls routines of the usb_specific_request.c file for non-standard
//! request management.
//! The enumeration parameters (descriptor tables) are contained in the
//! usb_descriptors.c file.
//!
//! @version 1.3 at90usb162-hidgen-1_0_1 $Id: usb_standard_request.h,v 1.3 2006/09/12 13:16:50 rletendu Exp $
//!
//! @todo
//! @bug

#ifndef _USB_ENUM_H_
#define _USB_ENUM_H_

//_____ I N C L U D E S ____________________________________________________

#include "usb_task.h"
#include "usb_descriptors.h"

//_____ M A C R O S ________________________________________________________

//_____ S T A N D A R D    D E F I N I T I O N S ___________________________

//! @defgroup std_request USB device standard  requests decoding module
//! @{



        // Device State
#define ATTACHED                          0
#define POWERED                           1
#define DEFAULT                           2
#define ADDRESSED                         3
#define CONFIGURED                        4
#define SUSPENDED                         5

#define USB_CONFIG_ATTRIBUTES_RESERVED    0x80
#define USB_CONFIG_BUSPOWERED            (USB_CONFIG_ATTRIBUTES_RESERVED | 0x00)
#define USB_CONFIG_SELFPOWERED           (USB_CONFIG_ATTRIBUTES_RESERVED | 0x40)
#define USB_CONFIG_REMOTEWAKEUP          (USB_CONFIG_ATTRIBUTES_RESERVED | 0x20)

#define USB_STATUS_REMOTEWAKEUP           0x02

//_____ D E C L A R A T I O N ______________________________________________

   //! @brief Returns true when device connected and correctly enumerated with an host.
   //! The device high level application should tests this before performing any applicative requests
#define Is_device_enumerated()            ((usb_configuration_nb!=0)   ? TRUE : FALSE)
#define Is_device_not_enumerated()        ((usb_configuration_nb!=0)   ? FALSE : TRUE)




//! @brief This function reads the SETUP request sent to the default control endpoint
//! and calls the appropriate function. When exiting of the usb_read_request
//! function, the device is ready to manage the next request.
//!
//! If the received request is not supported or a none USB standard request, the function
//! will call for custom decoding function in usb_specific_request module.
//!
//! @param none
//!
//! @return none
//! @note list of supported requests:
//! GET_DESCRIPTOR
//! GET_CONFIGURATION
//! SET_ADDRESS
//! SET_CONFIGURATION
//! CLEAR_FEATURE
//! SET_FEATURE
//! GET_STATUS
//!
void    usb_process_request( void);

extern  U8   usb_configuration_nb;

//! @}

#endif  // _USB_ENUM_H_

