

//   Programm Blinky
//   blinkt mit Led Nr. 0 am eStick im Sekundentakt


#include "eStick.h"   // Das brauchen wir, damit der estick funktioniert

int main( void )    // Beginn des Hauptprogramms
{

   INIT_LEDS;       // das brauchen wir, um die Leds verwenden zu können

   while (1)        //  Endlos-Schleife
   {

	 SET_LED(0);      // Led Nr. 0 einschalten
 	 WAIT_MS(500);    // halbe Sekunde warten
	 CLEAR_LED(0);    // Led Nr. 0 ausschalten
	 WAIT_MS(500);    // halbe Sekunde warten

   }  // zurück zum Schleifenbeginn

}   // Ende des Hauptprogramms

