/*********************************************************************
 * FileName:        adc.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         sprut
 * Copyright:       2007 Joerg Bredendiek (sprut)
 *
 *
 ********************************************************************/


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"             // I/O pin mapping
#include "delays.h"
#include "adc.h"


/** V A R I A B L E S ********************************************************/
#pragma udata
BYTE		ADC_Kanal;
BYTE		ADC_Out_0;
BYTE		ADC_Out_1;
BYTE		ADC_Out_2;
BYTE		ADC_Out_3;
BYTE		ADC_Out_4;
BYTE		ADC_Out_5;


/** D E C L A R A T I O N S **************************************************/
#pragma code

void Init_ADC(void)
{
	ADC_Kanal = 0;
	ADC_Out_0 = 0x7f;		// Mittelstellung
	ADC_Out_1 = 0x7f;
	ADC_Out_2 = 0x7f;
	ADC_Out_3 = 0x7f;
	ADC_Out_4 = 0x7f;
	ADC_Out_5 = 0x7f;
	mInitADC()			// AN0,1,2,3,4,5
	ADCON0bits.GO = 1;
}


//** A D C *******************************************************************************//

// ADC-Ergebnis auslesen
// neuen Kanal einstellen
// ADC starten
void UP_ADC(void)
{
	if (ADCON0bits.NOT_DONE) return;     // Wait for conversion

	switch (ADC_Kanal)
	{
		case 0: ADC_Out_0 = ADRESH; break;
		case 1: ADC_Out_1 = ADRESH; break;
		case 2: ADC_Out_2 = ADRESH; break;
		case 3: ADC_Out_3 = ADRESH; break;
		case 4: ADC_Out_4 = ADRESH; break;
		case 5: ADC_Out_5 = ADRESH; break;
	}

	ADC_Kanal++;
	//if (ADC_Kanal > 5) ADC_Kanal = 0;
	if (ADC_Kanal > 1) ADC_Kanal = 0;
	
	switch (ADC_Kanal)
	{
//		case 0:	ADCON0 = 0x01; 	break;	//AN0
//		case 1:	ADCON0 = 0x05; 	break;	//AN1
//		case 2:	ADCON0 = 0x09; 	break;	//AN2
//		case 3:	ADCON0 = 0x0D; 	break;	//AN3
//		case 4:	ADCON0 = 0x11; 	break;	//AN4
//		case 5:	ADCON0 = 0x15; 	break;	//AN5
		
//		case 0:	ADCON0bits.CHS = 0x01; 	break;	//AN0
//		case 1:	ADCON0bits.CHS = 0x05; 	break;	//AN1
//		case 2:	ADCON0bits.CHS = 0x09; 	break;	//AN2
//		case 3:	ADCON0bits.CHS = 0x0D; 	break;	//AN3
//		case 4:	ADCON0bits.CHS = 0x11; 	break;	//AN4
//		case 5:	ADCON0bits.CHS = 0x15; 	break;	//AN5
		
		case 0:	ADCON0bits.CHS = 0b0000; 	break;	//AN0
		case 1:	ADCON0bits.CHS = 0b0001; 	break;	//AN1
		case 2:	ADCON0bits.CHS = 0b0010; 	break;	//AN2
		case 3:	ADCON0bits.CHS = 0b0011; 	break;	//AN3
		case 4:	ADCON0bits.CHS = 0b0100; 	break;	//AN4
		case 5:	ADCON0bits.CHS = 0b0101; 	break;	//AN5

	}
	ADCON0bits.GO = 1;   
} // UP_ADC

