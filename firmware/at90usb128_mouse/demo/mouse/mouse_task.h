/**
 * @file mouse_task.h,v
 *
 * Copyright (c) 2004 Atmel.
 *
 * Please read file license.txt for copyright notice.
 *
 * @brief This file contains the function declarations
 *
 * @version 1.2 at90usb128-demo-mouse-1_0_3 $Id: mouse_task.h,v 1.2 2005/11/02 13:32:50 rletendu Exp $
 *
 * @todo
 * @bug
 */

#ifndef _MOUSE_TASK_H_
#define _MOUSE_TASK_H_

//_____ I N C L U D E S ____________________________________________________


#include "config.h"

//_____ M A C R O S ________________________________________________________
#define Is_usb_report_ready()           (report_ready)
#define Usb_set_report_not_ready()      (report_ready = 0)
#define Usb_set_report_ready()          (report_ready = 1)


//_____ D E C L A R A T I O N S ____________________________________________

bit is_usb_mouse_event(void);
void sof_action(void);


#endif /* _MOUSE_TASK_H_ */

