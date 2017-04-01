//!
//! @file hid_task.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file manages the generic HID IN/OUT task.
//!
//!
//! @version 1.1 at90usb162-hidgen-1_0_1 $Id: hid_task.c,v 1.1 2006/12/12 09:48:04 arobert Exp $
//!
//! @todo
//! @bug
//!/

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "usb_drv.h"
#include "usb_descriptors.h"
#include "usb_standard_request.h"
#include "usb_specific_request.h"
#include <avr/eeprom.h>


//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________



//_____ D E C L A R A T I O N S ____________________________________________

extern bit   usb_connected;
extern  U8   usb_configuration_nb;
volatile U8 cpt_sof=0;
U8 last_joy=0;

//! Declare function pointer to USB bootloader entry point
void (*start_bootloader) (void)=(void (*)(void))0xf000;


extern unsigned int PHRASELENGTH;


//!
//! @brief This function initializes the target board ressources.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
//!
//!/
void hid_task_init(void)
{
   Leds_init();
   Joy_init();
   Leds_set_val(0);
}



//! @brief Entry point of the HID generic communication task
//!
//! This function manages IN/OUT repport management.
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
int hid_task()
{
   U8 dummy=0;
   U8 dummy2=0;
   U8 joy;
   U32 volatile tempo;
   U8 led_state;
   U8 led_number;
   U8 phrase_continues;


    if(Is_device_enumerated())                     //! Check USB HID is enumerated
    {
      Usb_select_endpoint(EP_HID_OUT);    //! Get Data repport from Host
      if(Is_usb_receive_out())
      {
         led_state  = Usb_read_byte()&0x0F;       //! ReportOUT[0] is LED state

         if (led_state==0x0F)
		 {
		    phrase_continues=Usb_read_byte();
		    eeprom_write_byte((unsigned char *)PHRASELENGTH++,Usb_read_byte()); 
			eeprom_write_byte((unsigned char *)PHRASELENGTH++,Usb_read_byte()); 
			eeprom_write_byte((unsigned char *)PHRASELENGTH++,Usb_read_byte()); 
			
			if (!phrase_continues) 
			{
			    eeprom_write_byte((unsigned char *)PHRASELENGTH,0xFF);
				Usb_ack_receive_out();
				Usb_detach();
				return(0);
			}
		 }
		 else
		 {
 		 led_number = Usb_read_byte()&0x0F;      //! ReportOut[1] is LED number (1..4)
         switch (led_number)
         {
            case 1:
               if(led_state)
               {  Led0_off();   }
               else {Led0_on();}
               break;
            case 2:
               if(led_state)
               {  Led1_off();   }
               else {Led1_on();}
               break;
            case 3:
               if(led_state)
               {  Led2_off();   }
               else {Led2_on();}
               break;
            case 4:
               if(led_state)
               {  Led3_off();   }
               else {Led3_on();}
               break;
         }
         GPIOR1 = Usb_read_byte();          //! not used
         dummy  = Usb_read_byte();           //! In combinaisoon with nex byte allows
         dummy2 = Usb_read_byte();          //! the host to send an enter DFU mode event
		 }
         Usb_ack_receive_out();
      }

      if(dummy==0x55 && dummy2==0xAA)     //! Check if we received DFU mode command from host
      {
         Leds_off();
         Usb_detach();                    //! Detach actual generic HID application
         for(tempo=0;tempo<70000;tempo++);//! Wait some time before
         (*start_bootloader)();           //! Jumping to booltoader
      }

      joy=0;                              //! Now we build the Joytick information
      if(Is_joy_up()|| Is_joy_down() || Is_joy_right() || Is_joy_left() )                     //! Check for UP event
      {
        joy=0x01;
      }
      Usb_select_endpoint(EP_HID_IN);     //! Ready to send these information to the host application
      if(Is_usb_write_enabled())
      {
         if(joy!=last_joy)
         {
            Usb_write_byte(joy);
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_write_byte(GPIOR1);           //! Dummy (not used)
            Usb_ack_in_ready();               //! Send data over the USB
            last_joy=joy;
         }
      }
    }
	return(1);
}

//! @brief sof_action
//!
//! This function increments the cpt_sof counter each times
//! the USB Start Of Frame interrupt subroutine is executed (1ms)
//! Usefull to manage time delays
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
void sof_action()
{
   cpt_sof++;
}
