// ============================================
// = AT90USB162 REFERENCE DESIGN
// = Wired mouse with philips PNL2021 sensor
// ********************************************
// = Driver file for basic peripherals
// =============================================

#ifndef _CONFIG
#define _CONFIG

#include "mcu.h"   //<avr/io.h> 
#include "compiler.h"

#define FOSC 8000

// USB
// Used if VBUS_SENSING_IO is defined as "ENABLED"
#define   VBUS_SENSE_PORT     PORTC   // PORTx
#define   VBUS_SENSE_PIN      PINC    // PINx
#define   VBUS_SENSE_DDR      DDRC    // DDRx
#define   VBUS_SENSE_IO       4       // 0...7


// LEDs
// ****
#define   Leds_init()          (DDRB = 0xFF, PORTB = 0x7F, DDRC=4, PORTC=4)

#define   Led0_on()            (PORTB |= 0x01)                  // PD0
#define   Led0_off()           (PORTB &= ~0x01)
#define   Led0_toggle()        (PORTB ^= 0x01)
#define   Led1_on()            (PORTB |= 0x02)                  // PD1
#define   Led1_off()           (PORTB &= ~0x02)
#define   Led1_toggle()        (PORTB ^= 0x02)
#define   Led2_on()            (PORTB |= 0x04)                  // PD4
#define   Led2_off()           (PORTB &= ~0x04)
#define   Led2_toggle()        (PORTB ^= 0x04)
#define   Led3_on()            (PORTB |= 0x08)                  // PD5
#define   Led3_off()           (PORTB &= ~0x08)
#define   Led3_toggle()        (PORTB ^= 0x08)

#define   Leds_set_val(c)      (Leds_off(),PORTB |= c)
#define   Leds_get_val()       (PINB)
#define   Leds_off()           (PORTB = 0x7F)

// PUSHBUTTONS
// ***********

#define   Joy_init()                (DDRD = 0x10, PORTD = 0xEF)
#define   Push_button_init()        Joy_init()

#define   Is_joy_left()             0 //(((PIND&0x10) == 0) ? TRUE : FALSE)    // PB4
#define   Is_joy_not_left()         1 //(((PIND&0x10) == 0) ? FALSE : TRUE)
#define   Is_button_left()          Is_joy_left()
#define   Is_button_not_left()      Is_joy_not_left()

#define   Is_joy_middle()           (((PIND&0x01) == 0) ? TRUE : FALSE)    // PB0
#define   Is_joy_not_middle()       (((PIND&0x01) == 0) ? FALSE : TRUE)
#define   Is_joy_select()           Is_joy_middle()
#define   Is_joy_not_select()       Is_joy_not_middle()
#define   Is_button_middle()        Is_joy_middle()
#define   Is_button_not_middle()    Is_joy_not_middle()

#define   Is_joy_right()            (((PIND&0x40) == 0) ? TRUE : FALSE)    // PB6
#define   Is_joy_not_right()        (((PIND&0x40) == 0) ? FALSE : TRUE)
#define   Is_button_right()         Is_joy_right()
#define   Is_button_not_right()     Is_joy_not_right()

#define   Is_joy_down()             (((PIND&0x80) == 0) ? TRUE : FALSE)    // PB7
#define   Is_joy_not_down()         (((PIND&0x80) == 0) ? FALSE : TRUE)
#define   Is_button_down()          Is_joy_down()
#define   Is_button_not_down()      Is_joy_not_down()

#define   Is_joy_up()                (((PIND&0x20) == 0) ? TRUE : FALSE)    // PB5
#define   Is_joy_not_up()            (((PIND&0x20) == 0) ? FALSE : TRUE)
#define   Is_button_up()            Is_joy_up()
#define   Is_button_not_up()        Is_joy_not_up()


//#define   Hwb_button_init()         (DDRD &= ~0x80)
//#define   Is_hwb()                  (((PIND&0x80) == 0) ? TRUE : FALSE)   // PD7
#endif
