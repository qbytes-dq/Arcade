/*********************************************************************
 * FileName:        tlc5940.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 *
 *
 ********************************************************************/

#ifndef TLC5940_H
#define TLC5940_H

/** I N C L U D E S **********************************************************/
#include "HardwareProfile.h"     

/** D E F I N I T I O N S ****************************************************/

// ***************************
// Limits
// ***************************
#define MIN		    0
#define MAX			4095

// ***************************
// TLC CMD
// ***************************
#define TLC_CMD			0x00
#define PID_GET			0xEE
#define PID_SET			0xFF

// ***************************
// TLC Actions
// ***************************
#define HOLD			0x00

#define DUTY_ON			0x71
#define DUTY_OFF		0x72

#define UP_HOLD			0x81
#define DW_HOLD			0x82

#define SAW_UP			0x91
//#define SAW_UP2			0x93
#define SAW_DW			0x92
//#define SAW_DW2			0x94

#define SAW_UP_TRIG			0x93
#define SAW_DW_TRIG			0x94


#define DOT_COR			0xDC

#define INVERT			0xFF


// ***************************
// PIC18 Pin outs
// ***************************
#define SOUT	LATBbits.LATB6 //                                              

#define XERR 	LATBbits.LATB7 //Error Output, not read  - Gen I/O                                
//SOUT
//#define GSCLK 	LATBbits.LATB1 //CCP1 - grey scale clock
#define DCPRG 	LATBbits.LATB5 //                                              
//VCC      
//GND
#define BLANK 	LATBbits.LATB4 //ResetsCounter, blanks all outs - Gen I/O
#define XLAT 	LATBbits.LATB3 //when high, writes data from input register to DC or GS registers  - Gen I/O
#define SCLK 	LATBbits.LATB2 //SPI Data Shift Clock, SCL/SCK
#define SIN 	LATBbits.LATB1 //serial data output, SDO/RX 
#define VPRG 	LATBbits.LATB0 //changes between Dot and Grey data  - Gen I/O

// ***************************
// TLC States
// ***************************
#define WAIT	0x00
#define READY	0xFF

/** E X T E R N     **********************************************************/

extern	BYTE		RC_Buttons0;
//extern	BYTE		RC_Buttons0;
//extern	BYTE		RC_Buttons1;
//extern	BYTE		RC_Buttons2;

//#define ARSIZE 3
//
//extern	BYTE		MY_Spinner[ARSIZE];

//extern	BYTE		MY_Spinner0;
//extern	BYTE		MY_Spinner1;
//extern	BYTE		MY_Spinner2;

//extern BOOL GSCLK_TRIGGER = FLAG_TRUE;

/** P U B L I C  P R O T O T Y P E S *****************************************/
void	TLC5940_Init(void);

void	Set_DotCorrect(BYTE, BYTE, BYTE);
void    Clear_GrayScale(void);
void	Do_GrayScale(void);

void USB_TLC5940(unsigned char ReceivedDataBuffer[]);

void set_GSCLK_TRIG(void);

void set_DUTY_CYCLE( BYTE);

BYTE get_TRIGGERED( void);
void clear_TRIGGERED( void);
/** P R I V A T E  P R O T O T Y P E S ***************************************/

#endif	// TLC5940_H

/****  E N D E  *********************************************/
