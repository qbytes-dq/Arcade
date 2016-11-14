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
#include "spinners.h"

/** V A R I A B L E S ********************************************************/
#pragma udata

#define STEP 0x01

#define MIN (-127) + STEP
#define MID 0x00
#define MAX 127 - STEP

char		MY_Spinner[ARSIZE];

static BYTE k;

struct wp_char{
      char wp_now;
      char wp_old;
      char wp_pos;
      char wp_last;
}ar[ARSIZE];

struct wp_char *in_p;

int loop;

/** D E C L A R A T I O N S **************************************************/
#pragma code

//==============================================
//==============================================
//==============================================
void	Spinners_Init(void)
{
//	// RC0,1,2  sind die Zeilen > output, aber nur einzeln wärend der Abfrage
//	// RB0..7 sind die Spalten  > input  und pull up
//    TRISC = 0xFF;
//    TRISB = 0xFF;
//	LATB  = 0;
//	INTCON2bits.RBPU = 0;	// pull up
//
//	mZeile_0 = 0;
//	mZeile_1 = 0;
//	mZeile_2 = 0;
//	RC_Buttons0 = 0;
//	RC_Buttons1 = 0;
//	RC_Buttons2 = 0;

}	//Button_Init

//==============================================
//==============================================
//==============================================
//void Check_Move (BYTE now, BYTE old, BYTE pos)
void Check_Move (struct wp_char * inp)
{
   k = inp->wp_now | (inp->wp_old >>2);//..using lower 4 bits now

   switch(k)
   {
     case 0b0000:
     case 0b0101:
     case 0b1010:
     case 0b1111:  break;   //..nothing changed
 
     case 0b0001:
     case 0b0111:
     case 0b1110:
     case 0b1000:  
				{if (inp->wp_pos < MAX)
						{
						inp->wp_pos+=STEP;
//						if (inp->wp_pos == MID)
//							{
//							inp->wp_pos+=0X20;
//							} else 
//							{
//							inp->wp_pos+=STEP;
//							}
						}
                         break;
 				}	
     case 0b0100:
     case 0b0010:
     case 0b1011:
     case 0b1101:
				{
				  if (inp->wp_pos > MIN)
						{
						inp->wp_pos-=STEP;
//						if (inp->wp_pos == MID)
//							{
//							inp->wp_pos-=0X20;
//							} else 
//							{
//							inp->wp_pos-=STEP;
//							}
						}
                         break;
 				}	
     default:    //..more than one bit changed
                		break;
   }
   inp->wp_old = inp->wp_now;
return;
}



//==============================================
//==============================================
//==============================================
void	Spinner_Move(void)
{
//LATDbits.LATD0 = ~LATDbits.LATD0;

ar[0].wp_now = ((PORTE<<1) & 0b00001100);//, RE1 & RE2
ar[1].wp_now = ((PORTC<<2) & 0b00001100);//, RC0 & RC1
ar[2].wp_now = ((PORTC>>4) & 0b00001100);//, RC6 & RC7

	for (loop =0;loop<ARSIZE;loop++)
	{
		Check_Move (&ar[loop]);
	}
	//for(in_p = ar; in_p < &ar[ARSIZE]; in_p++)
	//	{
	//	Check_Move (in_p);
	//	}	
}

//==============================================
//==============================================
//==============================================
void	UP_Spinner(void)
{
	for (loop =0;loop<ARSIZE;loop++)
	{
//		if (ar[loop].wp_last != MID)
		{
			MY_Spinner[loop]=ar[loop].wp_pos;
		}
		ar[loop].wp_last=ar[loop].wp_pos;
		ar[loop].wp_pos = MID; // set value to 128 (255/2) (Middle)
	}
}	//UP_Button
