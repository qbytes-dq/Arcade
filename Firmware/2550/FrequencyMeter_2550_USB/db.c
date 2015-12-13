/*

http://web.stanford.edu/class/ee281/handouts/lcd_tutorial.pdf

*/

// Shows the band number as:  >#<
#define SHOWDB_VOLTS

#include <stdio.h>

	
extern char *   itoa(int val , char * buf); // signed int
char buffer2[10];

int i;

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h"
#include "delays.h"
#include "db.h"

#include "c:/MCC18/v3.47/h/xlcd.h"

/** V A R I A B L E S ********************************************************/
#pragma udata


//const char db[]   = "mW/dB ";
//const char db[]   = "-09dB ";
const char db[]   = "dB ";
//http://www.rapidtables.com/convert/power/mW_to_dBm.htm


float fval; 

  
#define MAX 10000
#define DIGS         5
#define TEN         10
int loop1=0;

unsigned char pos1;
unsigned char digit1;
unsigned long divBy1 = 0;

//==============================================
//==============================================
//==============================================
/** D E C L A R A T I O N S **************************************************/
#pragma code
	
	
// Assumes value is in millavolts   (2048 is  2.048V)
// Assumes max value in millavolts (99999 is 99.999V)

void
doVolt(unsigned long number)
{
	char displayHZ[] = {'.', '\0'};

	divBy1 = MAX;


		{
			// Loop 0 to 5 (total of 6 digits)
			for (loop1=0; loop1 < DIGS; loop1++)
			{
				digit1  = number / divBy1;
				number = number % divBy1;

			// We have a number to display
				while(BusyXLCD());
				WriteDataXLCD(0x30 + digit1);

				if (loop1 == 1) // put in period
				{
					while(BusyXLCD());
					putsXLCD(displayHZ);
				}
			
			divBy1 = divBy1 / TEN;				
			}			
		}
}



void
lcd_showdb(int adc)
{
//	char displayD[] = {'.', '\0'};
//		

//
//	// -----Frequency bands (ranges)-----
//	// Find Band			
//	numberBand = 3000;
//	for (band = 0;band <= 7; band ++)
//	{
//		if (number < numberBand)
//		{
//			break;  // Band found
//		}	
//		numberBand *=10;
//	}
//
//	displayB[0]=bands1[band];
//	while(BusyXLCD());
//	putsXLCD(&displayB[0]);
//
//	displayB[0]=bands2[band];
//	while(BusyXLCD());
//	putsXLCD(&displayB[0]);			
//	

//// Show ADC
//	while(BusyXLCD());				
//	itoa(adc,buffer2);
//	putsXLCD(buffer2);
//	
//	
//	// Show DB vs Volts vs Watts	
//	while(BusyXLCD());				
//	putsXLCD(&db);
////		
		
//--------------------------	
#ifdef SHOWDB	
	// Display band number		
	putcXLCD('>');			
	itoa(adc,buffer2);
	putsXLCD(buffer2);
	putcXLCD('<');			
#endif

//--------------------------	
#ifdef SHOWDB_VOLTS	
	i = adc * 2;
	doVolt(i);
#endif


}
