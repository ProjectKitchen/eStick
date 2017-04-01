

//   Programm Knightrider
//   die leutchdende Led wandert von 0 bis 7 und zur�ck !!


#include "eStick.h"   // Das brauchen wir, damit der estick funktioniert

int main( void )    // Beginn des Hauptprogramms
{

   unsigned int i;      //  Variable i   : kann ganzzahlige positive Werte annehmen
   unsigned int dir;    //  Variable dir : kann ganzzahlige positive Werte annehmen

   INIT_LEDS;        // das brauchen wir, um die Leds verwenden zu k�nnen

   i = 0;            // Variable i (f�r aktuelle Leuchtposition verwendet): null setzen
   dir = 1;          // Variable dir (f�r Richtung verwendet): eins setzen - "vorw�rts"

   while (1)        //  Endlos-Schleife
   {

  	if (dir == 1)	  // wenn Richtung gleich eins (vorw�rts)
	{
		SET_LED(i);       // Led Nr. i einschalten
 	    WAIT_MS(70);      // kurz warten (70 Millisekunden)
		CLEAR_LED(i);     // Led Nr. i ausschalten
	}
	else              // sonst (Richtung ungleich eins: r�ckw�rts) 
	{
		SET_LED(7-i);     // Led Nr. 7-i einschalten
 	    WAIT_MS(70);      // kurz warten (70 Millisekunden)
		CLEAR_LED(7-i);   // Led Nr. 7-i ausschalten
	}

    i = i + 1;         // i erh�hen
	if (i == 8)		   // am ende einer richtung angelangt ?
	{
		dir = ~dir;	   // Die Richtung �ndern
		i=0;		   // i null setzen
	}

   }  // zur�ck zum Schleifenbeginn

}   // Ende des Hauptprogramms

