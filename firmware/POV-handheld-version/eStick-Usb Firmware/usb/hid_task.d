hid_task.o hid_task.d : usb/hid_task.c conf/config.h mcu.h conf/compiler.h \
 conf/conf_usb.h usb/usb_drv.h usb/usb_descriptors.h \
 usb/usb_standard_request.h usb/usb_task.h usb/usb_specific_request.h \
 eeprom.h
