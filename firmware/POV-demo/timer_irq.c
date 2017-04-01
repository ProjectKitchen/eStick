
// why is there no Compare Match A Interrupt?

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t a = 0;
uint8_t c = 0;

// why is there no Compare Match A Interrupt?


ISR(TIMER0_COMPB_vect)
{
	a++;
}


ISR(TIMER0_OVF_vect)
{
	c++;
}



int main(void)
{
    
	DDRB = 0x7F;    // set all 7 pins on port B to outputs
	// TCCR0A = 0x02;	// WGM01 = 1 ... Clear Timer on Compare Match Mode
	TCCR0B = 0x02;  // PreScaler ... clk_io/8
	OCR0A = 0x6E;	// Compare Value
	//TIMSK0 = 0x02;	// enable Output A Compare match Interrupt
	TIMSK0 = 1 << OCIE0A;
	sei();			// Set Enable Interrupts
	
	while(1)		// endless loop
	{
		;
	}

}
