/*********************************************************************
 * FileName:        adc.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         sprut
 * Copyright:       2007 Joerg Bredendiek (sprut)
 *
 *
 ********************************************************************/

#ifndef ADC_H
#define ADC_H

/** I N C L U D E S **********************************************************/
#include "HardwareProfile.h"     

/** D E F I N I T I O N S ****************************************************/
// Tad = Tosc / 32 = 1.5 MHz  ->   0.66 us
// AC-time= 12 Tad = 8 us
// AN1,2,3,4 auf input
//	RA1/AN1 und RA3/AN3 auf input
//	ADCON0=0x01:	AN0, ADC-ein
//	ADCON1=0x0B:	Referenzen-Vdd-Vss, AN0..AN3 sind anaoge Eingaenge
//	ADCON2=0x2A:	left-justified, Aquisi=12Tad, Fad=Fosc/32
//	Wandlung braucht 24xTad -> 62500 ADC-Wandlungen/s

//#define mInitADC()	TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1; TRISAbits.TRISA3=1; ADCON0=0x01; ADCON1=0x0B; ADCON2=0x2A; //schnell  AN0..3
//#define mInitADC() PORTA = 0b00000000; TRISA = 0b00111111; 	ADCON0=0x01; 	ADCON1=0b1001;	ADCON2=0x2A; 	//schnell AN0..4
//                           pins low;           6 inputs;  


//#define mInitADC() TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1; TRISAbits.TRISA3=1; TRISAbits.TRISA4=1; TRISAbits.TRISA5=1; ADCON0=0x01; ADCON1=0b1001;	ADCON2=0x2A; 	//schnell AN0..4
//#define mInitADC() TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1; TRISAbits.TRISA3=1; TRISAbits.TRISA4=1; TRISAbits.TRISA5=1; ADCON0=0x01; ADCON1=0b1101;	ADCON2=0x2A; 	//schnell AN0..1 others digital

#define mInitADC() PORTA = 0b00111111; TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1; TRISAbits.TRISA3=1; TRISAbits.TRISA4=1; TRISAbits.TRISA5=1; ADCON0=0x01; ADCON1=0b1101;	ADCON2=0x2A; 	//schnell AN0..1 others digital
//#define mInitADC() PORTA = 0b00111111; TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1; TRISAbits.TRISA3=1; TRISAbits.TRISA4=1; TRISAbits.TRISA5=1; TRISAbits.TRISA6=1; ADCON0=0x01; ADCON1=0b1111;	ADCON2=0x2A; 	//schnell AN0..1 others digital
//#define mInitADC() TRISAbits.TRISA0=1; TRISAbits.TRISA1=1; TRISAbits.TRISA2=1; TRISAbits.TRISA3=1; TRISAbits.TRISA4=1; TRISAbits.TRISA5=1; ADCON0=0x00; ADCON1=0b1111;	ADCON2=0x00; 	//schnell AN0..1 others digital


/** E X T E R N     **********************************************************/
extern	BYTE		ADC_Kanal;
extern	BYTE		ADC_Out_0;
extern	BYTE		ADC_Out_1;
extern	BYTE		ADC_Out_2;
extern	BYTE		ADC_Out_3;
extern	BYTE		ADC_Out_4;
extern	BYTE		ADC_Out_5;


/** P U B L I C  P R O T O T Y P E S *****************************************/
void Init_ADC(void);
void UP_ADC(void);

/** P R I V A T E  P R O T O T Y P E S ***************************************/

#endif	// ADC_H

/****  E N D E  *********************************************/
