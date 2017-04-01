#include <util/delay.h> 


#include "config.h"
#include "usb_drv.h"
#include "usb_task.h"
#include "wdt_drv.h"
#include "power_drv.h"
#include "usb_standard_request.h"
#include <avr/eeprom.h>


void hid_task_init(void);
int hid_task(void);


//_____ M A C R O S ________________________________________________________

#ifndef F_CPU
  #define F_CPU 8000000 
#endif

#define _USE_EEPROM_


#ifdef _USE_EEPROM_
   #define GET_NEXT_CHAR(x)  (eeprom_read_byte((unsigned char *)(x)))
#else
   #define GET_NEXT_CHAR(x) (translate(PHRASE[x]))
#endif

#define DELAYTIME 50
#define CHASETIME 200

#define CHARWIDTH 7 
#define DISPLENGTH  8
#define MAXLEN 510

unsigned int SCROLLSPEED = 1;



/* Constant Array Declaration to refelect the fonts
 * Note: All LEDs are low active, hence, the font
 *       maps are generated in an inverted fashion.
 *
 * The following table was generated with an OpenOffice Calc file (fontgen.ods) 
 * that is also made available for MS Excel 2003 (the latter, however, requires 
 * that the optional "Analysis ToolPak add-in" is installed - available during 
 * the standard installation.)
 */
unsigned char characters [][CHARWIDTH]  =
{
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  //SPACE 0
 {0xFF, 0x80, 0x77, 0x77, 0x77, 0x80, 0xFF},  //A 1
 {0xFF, 0x00, 0x6E, 0x6E, 0x6E, 0x91, 0xFF},  //B 2
 {0xFF, 0x81, 0x7E, 0x7E, 0x7E, 0x7E, 0xFF},  //C 3
 {0xFF, 0x00, 0x7E, 0x7E, 0x7E, 0x81, 0xFF},  //D 4
 {0xFF, 0x00, 0x6E, 0x6E, 0x6E, 0x7E, 0xFF},  //E 5
 {0xFF, 0x00, 0x6F, 0x6F, 0x6F, 0x7F, 0xFF},  //F 6
 {0xFF, 0x81, 0x7E, 0x76, 0x76, 0xB1, 0xFF},  //G 7
 {0xFF, 0x00, 0xEF, 0xEF, 0xEF, 0x00, 0xFF},  //H 8
 {0xFF, 0xFF, 0x7E, 0x00, 0x7E, 0xFF, 0xFF},  //I 9
 {0xFF, 0xFD, 0xFE, 0xFE, 0xFE, 0x01, 0xFF},  //J 10
 {0xFF, 0x00, 0xEF, 0xEF, 0xD7, 0x38, 0xFF},  //K 11
 {0xFF, 0x01, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF},  //L 12
 {0xFF, 0x00, 0xBF, 0xDF, 0xBF, 0x00, 0xFF},  //M 13
 {0xFF, 0x00, 0x9F, 0xE7, 0xF9, 0x00, 0xFF},  //N 14
 {0xFF, 0x81, 0x7E, 0x7E, 0x7E, 0x81, 0xFF},  //O 15
 {0xFF, 0x00, 0x77, 0x77, 0x77, 0x8F, 0xFF},  //P 16
 {0xFF, 0x81, 0x7E, 0x7A, 0x7D, 0x82, 0xFF},  //Q 17
 {0xFF, 0x00, 0x77, 0x77, 0x73, 0x8C, 0xFF},  //R 18
 {0xFF, 0x9C, 0x6E, 0x6E, 0x6E, 0xB1, 0xFF},  //S 19
 {0xFF, 0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0xFF},  //T 20
 {0xFF, 0x01, 0xFE, 0xFE, 0xFE, 0x01, 0xFF},  //U 21
 {0xFF, 0x03, 0xFD, 0xFE, 0xFD, 0x03, 0xFF},  //V 22
 {0xFF, 0x00, 0xFD, 0xFB, 0xFD, 0x00, 0xFF},  //W 23
 {0xFF, 0x38, 0xD7, 0xEF, 0xD7, 0x38, 0xFF},  //X 24
 {0xFF, 0x3F, 0xDF, 0xE0, 0xDF, 0x3F, 0xFF},  //Y 25
 {0xFF, 0x78, 0x76, 0x6E, 0x5E, 0x3E, 0xFF},  //Z 26
 {0xFF, 0x81, 0x7A, 0x76, 0x6E, 0x81, 0xFF},  //0 27
 {0xFF, 0xFF, 0xDF, 0xBF, 0x00, 0xFF, 0xFF},  //1 28
 {0xFF, 0xBC, 0x7A, 0x76, 0x6E, 0x9E, 0xFF},  //2 29
 {0xFF, 0xBD, 0x7E, 0x6E, 0x6E, 0x91, 0xFF},  //3 30
 {0xFF, 0x07, 0xF7, 0xC0, 0xF7, 0xF7, 0xFF},  //4 31
 {0xFF, 0x0E, 0x6E, 0x6E, 0x6E, 0x71, 0xFF},  //5 32
 {0xFF, 0x81, 0x6E, 0x6E, 0x6E, 0xF1, 0xFF},  //6 33
 {0xFF, 0x7F, 0x7C, 0x73, 0x4F, 0x3F, 0xFF},  //7 34
 {0xFF, 0x91, 0x6E, 0x6E, 0x6E, 0x91, 0xFF},  //8 35
 {0xFF, 0x9D, 0x6E, 0x6E, 0x6E, 0x81, 0xFF},  //9 36
 {0xFF, 0xFF, 0x02, 0x02, 0xFF, 0xFF, 0xFF},  //! 37
 {0xFF, 0x67, 0x5A, 0x5A, 0xBB, 0xFF, 0xFF},  //? 38
 {0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0xF7, 0xFF},  //- 39
 {0xFF, 0xEF, 0xEF, 0x83, 0xEF, 0xEF, 0xFF},  //+ 40
 {0xFF, 0xAB, 0xC7, 0x01, 0xC7, 0xAB, 0xFF},  //* 41
 {0xFF, 0xFF, 0xFF, 0xD7, 0xD7, 0xFF, 0xFF},  //: 42
 {0xFF, 0xFF, 0xFE, 0xFD, 0xD7, 0xFF, 0xFF},  //, 43
 {0xFF, 0xFF, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF},  //. 44
 {0xFF, 0xDD, 0x9E, 0xF2, 0x9E, 0xDD, 0xFF},  //Smiley 45
 {0xFF, 0xC7, 0x83, 0xC1, 0x83, 0xc7, 0xFF},  //Heart  46
 {0xFF, 0xFF, 0xC3, 0xBD, 0x7E, 0xFF, 0xFF},  // ( 47
 {0xFF, 0xFF, 0x7E, 0xBD, 0xC3, 0xFF, 0xFF},  // ) 48
 {0xFF, 0xEB, 0xEB, 0xEB, 0xEB, 0xEB, 0xFF},  // = 49

 };  


unsigned int PHRASELENGTH;
#ifndef _USE_EEPROM_
  unsigned char PHRASE[80] = "          SLOW \201  MODERATE \202  FASTER \203   FAST    SLOWER   SLOWER   SLOW AGAIN  ";
#endif


void chase_leds(void)
{
  static unsigned char bit=0,bitdir=0;
  static unsigned int bittime=0;

  PORTB=~(1<<bit);
  _delay_loop_2(DELAYTIME);
  if (bittime++>CHASETIME)
  {
     bittime=0;
     if (bitdir) { if (bit<7) bit++; else bitdir=0;}
     else { if (bit>0) bit--; else bitdir=1;}
  }
}

unsigned char translate(unsigned char c)
{
	if ((c >= 'A') && (c<='Z')) c = c-'A'+1;
	else if ((c >= '0') && (c<='9')) c = c-'0'+27;
	else if (c == '!') c = 37;
	else if (c == '?') c = 38;
	else if (c == '-') c = 39;
	else if (c == '+') c = 40;
	else if (c == '*') c = 41;
	else if (c == ':') c = 42;
	else if (c == ',') c = 43;
	else if (c == '.') c = 44;
	else if (c == '$') c = 45;
	else if (c == '&') c = 46;
	else if (c == '(') c = 47;
	else if (c == ')') c = 48;
	else if (c == '=') c = 49;
	else if (c<200) c=0;
    return(c);
}

/******************************************************************************
 * Main Routine
 *****************************************************************************/
void run_text (void)
{


  unsigned char actchar=0, pov_active=0;
  unsigned int  char_index, col_index;
  unsigned int  timestamp=0; 
  unsigned int  cycletime=20000,triggertime=10000;
  unsigned int  startpos=0, lights_on=0, pos=0;
  unsigned int  waittime=0,  wait_active=0;
  unsigned int  blinktime=0, blink_active=0;
  unsigned int  char_width=170;
  unsigned char double_display = 0, dbl_act=0;
  volatile int  char_delay;

  DDRC = 0x04;  // set direction for the Latche Enable (LE) PortC.2 on the  eStick to output
  PORTC = 0x04; // make the Latch transparent 
  DDRB = 0xFF;  // set Port PORTB to output 
  DDRD &= ~(1<<PD5);  // set sensor pin on port D to input
  PORTD |= (1<<PD5);  // activate pullup on sensor pin

  TCCR1B=3; // 16-bit Timer1 runs at 250kHz
  TCNT1=0;

    while(1)
    {
  

	   if (PIND & (1<<PD5))  {  // turn finished 
			  
		   while (PIND & (1<<PD5)) ;  // wait until start condition 	 

		   cycletime=TCNT1;
		   TCNT1=0;

	//	   cycletime=timestamp;
		   timestamp=0;
		   pos=0; 			    // reset display pos to start column   
		   dbl_act=0;

	       if (blinktime) blinktime--; 

	       if (waittime) waittime--; 
		   else startpos+=SCROLLSPEED;     // increase start column if not waiting

	       if (!waittime) triggertime= (cycletime>>1)-4;
		   else triggertime=(cycletime>>1)-cycletime/600*SCROLLSPEED;

		   if (startpos>=PHRASELENGTH*CHARWIDTH) {  // text finished 
		      startpos=0; 
			  wait_active=0; blink_active=0;
		   }  
	   }

	   if (double_display && !dbl_act)  {    // repeat in second half of turn
	       if (TCNT1>=triggertime) {
		      pos=0; dbl_act=1;
		   }
	   }  

	   if (timestamp<500)  { // fast enough: activate POV
	       timestamp++; pov_active=1;
	   }
	   else {  // too slow: deactivate POV, chase leds 
	   	  pov_active=0; startpos=0; pos=0;  lights_on=0;
	   }
		   

	   if (pov_active)  { 

              char_index=(startpos+pos)/CHARWIDTH;
			  col_index =(startpos+pos)%CHARWIDTH;
		   
              if (char_index >= PHRASELENGTH) actchar=0;
			  else  actchar=GET_NEXT_CHAR(char_index);

			  if (actchar >= 200)  // handle special control characters
			  {
			    switch (actchar) {
				   case 201: SCROLLSPEED=1; break;
				   case 202: SCROLLSPEED=2; break;
				   case 203: SCROLLSPEED=3; break;
				   case 204: SCROLLSPEED=4; break;
				   case 205: if (wait_active<char_index) {waittime=20; wait_active=char_index;} break;
				   case 206: if (blink_active<char_index) {blinktime=70; blink_active=char_index;} break;
				   case 207: double_display=1; break;
				   case 208: double_display=0; break;
				   case 209: char_width=400; break;
				   case 210: char_width=170; break;
				   case 211: char_width=100; break;

				 }
				 actchar=0;
			  }


			  if (pos<DISPLENGTH*CHARWIDTH) {    // in display range: display act column
			       if (blinktime % 10 > 5) PORTB=0xff;   // blink action
				   else PORTB = characters[actchar][col_index];
			  	   pos++; 
			  } 
		   	  else  PORTB=0xff;  // no in range: turn lights off
		   
		  
              for (char_delay=cycletime/char_width;char_delay>0;char_delay--)
 			     if (PIND & (1<<PD5)) break;
			     // wait calculated time, break if turn finished to minimize jitter

	   }   
	   else  chase_leds();
   }
}
 



//_____ D E F I N I T I O N S ______________________________________________

int main(void)
{

   DDRD=0x10;   // PD4= output, 0V, all others input with pullup
   PORTD=0xef;
   _delay_loop_2(1000);
   
   if (PIND & (1<<PD5))
   {

     Usb_enable_regulator();

	 #ifndef  AVRGCC
   		Wdt_off();
	 #else
   		wdt_reset();
   		Wdt_clear_flag();
   		Wdt_change_enable();
   		Wdt_stop();
	 #endif

     Clear_prescaler();
  
     usb_task_init();
     hid_task_init();

     do  usb_task();  while (hid_task()) ;
	 
   }
  

   Set_prescaler(3);


   
#ifdef _USE_EEPROM_
   for (PHRASELENGTH=0;(eeprom_read_byte((unsigned char *)PHRASELENGTH)<0xFF) && PHRASELENGTH<MAXLEN-1;PHRASELENGTH++); 
#else
   PHRASELENGTH = sizeof (PHRASE);

   PHRASE[5]=203;
/*
   PHRASE[15]=202;
   PHRASE[16]=209;
   PHRASE[26]=205;
   PHRASE[27]=210;
   PHRASE[36]=203;
   PHRASE[44]=211;
   PHRASE[53]=205;
   PHRASE[63]=201;
*/
#endif
 
   run_text();

   return 0;
}
