

//   Programm Knightrider
//   die leutchdende Led wandert von 0 bis 7 und zurück !!


#include "eStick.h"   // Das brauchen wir, damit der estick funktioniert

int main( void )    // Beginn des Hauptprogramms
{

   unsigned int i;      //  Variable i   : kann ganzzahlige positive Werte annehmen
   unsigned int dir;    //  Variable dir : kann ganzzahlige positive Werte annehmen

   INIT_LEDS;        // das brauchen wir, um die Leds verwenden zu können

   i = 0;            // Variable i (für aktuelle Leuchtposition verwendet): null setzen
   dir = 1;          // Variable dir (für Richtung verwendet): eins setzen - "vorwärts"

   while (1)        //  Endlos-Schleife
   {

  	if (dir == 1)	  // wenn Richtung gleich eins (vorwärts)
	{
		SET_LED(i);       // Led Nr. i einschalten
 	    WAIT_MS(70);      // kurz warten (70 Millisekunden)
		CLEAR_LED(i);     // Led Nr. i ausschalten
	}
	else              // sonst (Richtung ungleich eins: rückwärts) 
	{
		SET_LED(7-i);     // Led Nr. 7-i einschalten
 	    WAIT_MS(70);      // kurz warten (70 Millisekunden)
		CLEAR_LED(7-i);   // Led Nr. 7-i ausschalten
	}

    i = i + 1;         // i erhöhen
	if (i == 8)		   // am ende einer richtung angelangt ?
	{
		dir = ~dir;	   // Die Richtung ändern
		i=0;		   // i null setzen
	}

   }  // zurück zum Schleifenbeginn

}   // Ende des Hauptprogramms

