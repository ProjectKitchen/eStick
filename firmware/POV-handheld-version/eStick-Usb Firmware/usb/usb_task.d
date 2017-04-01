usb_task.o usb_task.d : usb/usb_task.c conf/config.h mcu.h conf/compiler.h \
 conf/conf_usb.h usb/usb_task.h usb/usb_drv.h usb/usb_descriptors.h \
 usb/usb_standard_request.h usb/power_drv.h usb/wdt_drv.h usb/pll_drv.h \
 usb/usb_device_task.h
