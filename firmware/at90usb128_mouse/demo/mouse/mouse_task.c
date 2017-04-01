//!
//! @file mouse_task.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file manages the Mouse task.
//!
//!
//! @version 1.15 at90usb128-demo-mouse-1_0_3 $Id: mouse_task.c,v 1.15 2006/08/01 13:16:44 rletendu Exp $
//!
//! @todo
//! @bug
//!/

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "mouse_task.h"
#include "lib_mcu/usb/usb_drv.h"
#include "lib_mcu/adc/adc_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "lib_mcu/wdt/wdt_drv.h"






//_____ M A C R O S ________________________________________________________

#define Usb_mouse_up()                  (usb_mouse_report[2]-=MOUSE_SPEED)
#define Usb_mouse_down()                (usb_mouse_report[2]+=MOUSE_SPEED)
#define Usb_mouse_left()                (usb_mouse_report[1]-=MOUSE_SPEED)
#define Usb_mouse_right()               (usb_mouse_report[1]+=MOUSE_SPEED)
#define Usb_mouse_click_left()          (usb_mouse_report[0] |= 0x01)
#define Usb_mouse_click_right()         (usb_mouse_report[0] |= 0x02)
#define Usb_mouse_click_middle()        (usb_mouse_report[0] |= 0x04)
#define Usb_mouse_release_left()        (usb_mouse_report[0] &= ~0x01)
#define Usb_mouse_release_right()       (usb_mouse_report[0] &= ~0x02)
#define Usb_mouse_release_middle()      (usb_mouse_report[0] &= ~0x04)
#define Usb_mouse_scroll_up()           (usb_mouse_report[3]++)
#define Usb_mouse_scroll_down()         (usb_mouse_report[3]--)
#define Usb_mouse_report_reset()        (usb_mouse_report[0]=0,usb_mouse_report[1]=0,usb_mouse_report[2]=0,usb_mouse_report[3]=0)

#define Is_mouse_left_event()         Is_joy_left()
#define Is_mouse_right_event()        Is_joy_right()
#define Is_mouse_up_event()           Is_joy_up()
#define Is_mouse_down_event()         Is_joy_down()
#define Is_mouse_click_left_event()   Is_hwb()
#define Is_mouse_release_left_event() !Is_hwb()




//_____ D E F I N I T I O N S ______________________________________________



//_____ D E C L A R A T I O N S ____________________________________________

U8 report_ready;
U8 usb_mouse_report[4];
U16 wheel;
volatile U8 cpt_sof;
extern  U8   usb_configuration_nb;


//!
//! @brief This function initializes the hardware/software resources required for mouse task.
//!
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
//!
//!/
void mouse_task_init(void)
{
   Joy_init();
   Hwb_button_init();
   init_adc();
   Usb_mouse_report_reset();
   report_ready=TRUE;
   wheel=Get_adc_pot_val();
   cpt_sof=0;
   Usb_enable_sof_interrupt();
}





//! @brief Entry point of the mouse management
//!
//! This function links the mouse and the USB bus.
//!
//! @param none
//!
//! @return none
void mouse_task(void)
{
   if(Is_device_enumerated() && is_usb_mouse_event() && !Is_usb_report_ready())
   {
      report_ready=TRUE;
   }

   if (Is_device_enumerated() && Is_usb_report_ready())
   {
      Usb_select_endpoint(EP_MOUSE_IN);
      if (Is_usb_write_enabled())
      {
         Usb_set_report_not_ready();
         Usb_write_byte(usb_mouse_report[0]);
         Usb_write_byte(usb_mouse_report[1]);
         Usb_write_byte(usb_mouse_report[2]);
         Usb_write_byte(usb_mouse_report[3]);
         Usb_ack_in_ready();
      }
   }
}

//! @brief Is_usb_mouse_event
//!
//! This function returns TRUE if a event occurs on the mouse
//! (FALSE if not). The mouse report is updated by this function
//!
//! @param none
//!
//! @return none
bit is_usb_mouse_event(void)
{
   static bit usb_mouse_event_stored;
   U16 new_wheel;

#if (USB_LOW_SPEED_DEVICE==DISABLE)
   if(cpt_sof<NB_IDLE_POLLING_SOF) return FALSE;
   cpt_sof=0;
#endif

   Usb_mouse_report_reset();

   new_wheel=Get_adc_pot_val();
   if(new_wheel>680)
   {
      Usb_mouse_scroll_down();
      usb_mouse_event_stored = 1;
   }
   if(new_wheel<340)
   {
      Usb_mouse_scroll_up();
      usb_mouse_event_stored = 1;
   }
   wheel=new_wheel;

   if(Is_mouse_click_left_event())
   {
      Usb_mouse_click_left();
      usb_mouse_event_stored = 1;
   }

   if (Is_mouse_left_event())
   {
      Usb_mouse_left();
      usb_mouse_event_stored = 1;
   }

   if (Is_mouse_right_event())
   {
      Usb_mouse_right();
      usb_mouse_event_stored = 1;
   }

   if (Is_mouse_down_event())
   {
      Usb_mouse_down();
      usb_mouse_event_stored = 1;
   }

   if (Is_mouse_up_event())
   {
      Usb_mouse_up();
      usb_mouse_event_stored = 1;
   }

   if (usb_mouse_event_stored == 1)
   {
      usb_mouse_event_stored = 0;
      return TRUE;
   }
   else {return FALSE;}

}


//! @brief sof_action
//!
//! This function increments the cpt_sof counter each times
//! the USB Start Of Frame interrupt subroutine is executed (1ms)
//! Usefull to manage time delays
//!
//! @param none
//!
//! @return none
void sof_action()
{
   cpt_sof++;
}


//! @brief vbus_off_action
//!
//! This function increments the action to be executed upon
//! the USB VBUS disconnection
//! Here a Vbus lost lead to detach
//!
//! @param none
//!
//! @return none
void vbus_off_action(void)
{
   Usb_detach();
}
