/*
 * Simple Port Toggle Demo program.
 * M. Horauer, FH Technikum Wien
 */
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#define T 1
#define P 2

int main (void)
{
  DDRB = 0x7F;  // set the Port Pin PORTB.0 to output
  while(1)
  {

    PORTB = 0x7F;  // B
    _delay_ms(T);
    PORTB = 0x49;  
    _delay_ms(T);
    PORTB = 0x49;  
    _delay_ms(T);
    PORTB = 0x36;  
    _delay_ms(T);

    PORTB = 0x00;  
    _delay_ms(P);

  
    PORTB = 0x7F;  // E
    _delay_ms(T);
    PORTB = 0x49;  
    _delay_ms(T);
    PORTB = 0x49;  
    _delay_ms(T);
    PORTB = 0x49;  
    _delay_ms(T);

    PORTB = 0x00;  
    _delay_ms(P);


    PORTB = 0x7F;  // L  
    _delay_ms(T);
    PORTB = 0x01;  
    _delay_ms(T);
    PORTB = 0x01;  
    _delay_ms(T);
    PORTB = 0x01;  
    _delay_ms(T);


    PORTB = 0x00;  
    _delay_ms(P);

	_delay_ms(12*T+3*P);

#if 0

    PORTB = ~0x00;  // E
    _delay_us(T);
    PORTB = ~0x36;  
    _delay_us(T);
    PORTB = ~0x36;  
    _delay_us(T);
    PORTB = ~0x36;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);

    PORTB = ~0x00;  // K
    _delay_us(T);
    PORTB = ~0x77;  
    _delay_us(T);
    PORTB = ~0x08;  
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);


    PORTB = ~0x3F;  // T
    _delay_us(T);
    PORTB = ~0x00;  
    _delay_us(T);
    PORTB = ~0x3F;  
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);


    PORTB = ~0x00;  // R
    _delay_us(T);
    PORTB = ~0x67;  
    _delay_us(T);
    PORTB = ~0x48;  
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);


    PORTB = ~0x41;  // O
    _delay_us(T);
    PORTB = ~0x3E;  
    _delay_us(T);
    PORTB = ~0x3E;  
    _delay_us(T);
    PORTB = ~0x41;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);


    PORTB = ~0x00;  // N
    _delay_us(T);
    PORTB = ~0x67;  
    _delay_us(T);
    PORTB = ~0x97;  
    _delay_us(T);
    PORTB = ~0x00;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);

    PORTB = ~0x00;  // I
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);

    PORTB = ~0x7F;  
    _delay_us(P);

    PORTB = ~0x00;  // K
    _delay_us(T);
    PORTB = ~0x77;  
    _delay_us(T);
    PORTB = ~0x08;  
    _delay_us(T);
    PORTB = ~0x7F;  
    _delay_us(T);

#endif
    _delay_ms(10);
  }
}
 
