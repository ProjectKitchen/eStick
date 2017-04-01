//! @file conf_scheduler.h,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the scheduler configuration definition
//!
//! @version 1.2 at90usb128-demo-mouse-1_0_3 $Id: conf_scheduler.h,v 1.2 2006/03/14 12:22:26 rletendu Exp $
//!
//! @todo
//! @bug

#ifndef _CONF_SCHEDULER_H_
#define _CONF_SCHEDULER_H_



//! @defgroup scheduler_conf Scheduler configuration
//! @{
#define SCHEDULER_TYPE          SCHEDULER_FREE  // SCHEDULER_(TIMED|TASK|FREE|CUSTOM)
#define Scheduler_task_1_init   usb_task_init
#define Scheduler_task_1        usb_task
#define Scheduler_task_2_init   mouse_task_init
#define Scheduler_task_2        mouse_task
//! @}

#endif  //! _CONF_SCHEDULER_H_

