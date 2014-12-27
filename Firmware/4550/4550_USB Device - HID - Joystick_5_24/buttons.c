/*********************************************************************
 * FileName:        buttons.c
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
#include "buttons.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
BYTE		RC_Buttons0;
BYTE		RC_Buttons1;
BYTE		RC_Buttons2;

BYTE		J_ButtonsX;
BYTE		J_ButtonsY;

/** D E C L A R A T I O N S **************************************************/
#pragma code

void	Button_Init(void)
{
	// ==============
	// pull ups PortB
	TRISB = 0b11111111; // All inputs
	PORTB = 0x00;
	//INTCON2bits.RBPU=0;  // pull up
	EnablePullups();     //PORTB pullup resistors enabled.	
		
	// ==============
	// pull ups PortD	
	TRISD = 0b11111111; // All inputs
	PORTD = 0x00;
	PORTEbits.RDPU = 1; // Turn on pull-ups
}	//Button_Init


void	UP_Button(void)
{
	RC_Buttons0 = ~PORTB;
	RC_Buttons1 = ~PORTD;
	//RC_Buttons2 = (~PORTA )& 0b00111100;
	RC_Buttons2 = 0;
	
	// X pos (left/right)
	J_ButtonsX = 128;	
	if (!PORTAbits.RA4)
	{
		J_ButtonsX = 0; //Left
	} else
	if (!PORTAbits.RA3)
	{
		J_ButtonsX = 255; // Right
	}
		
//	
//	// Y pos (up/down)
	J_ButtonsY = 128;	
	if (!PORTAbits.RA2) //Down
	{
		J_ButtonsY = 0;
	} else
	if (!PORTAbits.RA5)
	{
		J_ButtonsY = 255; // Up
	}	
		
}	//UP_Button





