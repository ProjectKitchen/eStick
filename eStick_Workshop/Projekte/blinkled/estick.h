

#include <avr/io.h>
#include <util/delay.h>

#define SET_LED(x)     PORTB &= (~(1<<(x)))
#define CLEAR_LED(x)   PORTB |= (1<<(x))

#define WAIT_MS(x)   for (int i=0; i<x; i++) \
                     _delay_ms(1);

#define INIT_LEDS    DDRD=0x10;    \
                     PORTD=0xef;   \
                     DDRC = 0x04;  \
                     PORTC = 0x04; \
                     DDRB = 0xff;  \
                     PORTB =0xff;


   // PD4= output, 0V, all others input with pullup
   // set direction for the Latche Enable (LE) PortC.2 
   // make the Latch transparent   
   // set Port PORTB to output 

