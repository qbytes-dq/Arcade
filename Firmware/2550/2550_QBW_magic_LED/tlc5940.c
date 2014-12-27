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

/***


Each port has three registers for its operation. These registers are:

TRIS register (data direction register)
PORT register (reads the levels on the pins of the device)
LAT register (output latch)


***/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"             // I/O pin mapping
#include "delays.h"
#include "tlc5940.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
BYTE		RC_Buttons0 = WAIT;

// ==========================================================
#pragma udata gpr1=0x100
	BYTE large_action[48];
	unsigned short large_value[48];
//	unsigned short large_current[48];
#pragma udata  // return to default section

#pragma udata usb6=0x0600
	BYTE  large_stepSize[48];
	BYTE  large_stepDec[48];	
	
//	BYTE  large_SKIP[48];
//	BYTE  large_CNTR[48];
	
//	BYTE  large_TRIG[48];		
#pragma udata  // return to default section

// ==========================================================

BYTE  *action_ptr = &large_action[0];
unsigned short *value_ptr  = &large_value[0];
//unsigned short *current_ptr= &large_current[0];

BYTE  *step1_ptr  = &large_stepSize[0];
BYTE  *step2_ptr  = &large_stepDec[0];
//BYTE  *skip_ptr   = &large_SKIP[0];
//BYTE  *cntr_ptr   = &large_CNTR[0];
//BYTE  *trig_ptr   = &large_TRIG[0];

// ==========================================================

//char *ptr;
//ptr = &r[0];

// ==========================================================


//BOOL GSCLK_TRIGGER = FLAG_TRUE;


short update_flag = 0; 
short pol = 1; 
signed long d = 0;
unsigned short dq = 0; 
unsigned short dq1 = 0;
unsigned short dq2 = 0; 
unsigned short dq3=4;

unsigned short banks = 1; 


//unsigned short SCLK_Cnt = 0; 
unsigned short ledcnt  = 0; // 15,  0-15 LEDs
unsigned short chipcnt = 0; // 15,  0-15 LEDs
         short led12b  = 0; // 4096, PWM
         short gray6b  = 0; // 63 Grayscale
unsigned short color   = 0;
BYTE grayscale = 0b111111;


//==============================================
/*--- Relay Structure ---*/
/*--- Relay Structure ---*/
/*--- Relay Structure ---*/
/*--- Relay Structure ---*/

struct RELAYBITS
  {
  unsigned rca:1;     /* SEL_UNBAL relay */
  unsigned earth:1;   /* EARTHSEL relay */
  unsigned ground:1;  /* GND_RLY relay */
  unsigned phase:1;   /* Phase invert relay */
  unsigned bridge:1;  /* Mono amplifier mode */ 
  unsigned dummy:2;   /* Alignment bits */
  unsigned mute:1;    /* MUTE relay */
  };
  
/*--- Relay bits union ---*/

typedef union
  {
  struct RELAYBITS Bits; 
  unsigned char data;
  }RELAY;
  
volatile RELAY RELAYbits;
//==============================================

  

BYTE dutyClk;

BYTE DUTY_CYCLE=0;
	
BOOL GSCLK_TRIGGER = FLAG_TRUE;

BYTE TRIGGER = 0x00;


  
#define STEP 0x02

//#define MIN 0x00 + STEP
//#define MID 0x80
//#define MAX 0xFF - STEP

//BYTE		MY_Spinner[ARSIZE];

static BYTE k;

//struct wp_char{
//      BYTE wp_now;
//      BYTE wp_old;
//      BYTE wp_pos;
//      BYTE wp_last;
//}ar[ARSIZE];
//
//struct wp_char *in_p;

unsigned short chip_cnt = 0; // 15,  0-15 LEDs
         short led_12b = 0; // 4096, PWM
unsigned short color_ = 0;

int loop;

//==============================================
//==============================================


unsigned short led_cnt = 0; // 15,  0-15 LEDs
         short gray_6b = 0; // 63 Grayscale
BYTE gray_scale = 0b111111;

//#define OverSpin LATAbits.LATA6

/** D E C L A R A T I O N S **************************************************/
#pragma code

//==============================================
//==============================================
//==============================================
void	TLC5940_Init(void)
{
	
	//GSCLK = 0;//   output_low(GSCLK); 
	SCLK  = 0;  //   output_low(SCLK);                      
	DCPRG = 0;   //   output_low(DCPRG); 
	VPRG  = 0;  //   output_high(VPRG);      
	XLAT  = 0;  //   output_low(XLAT);    
	BLANK = 0;  //   output_high(BLANK); 
      
	// Default everything off.
	for (dq=0;dq<48;dq++)
	{
		action_ptr[dq]=HOLD;
		
		value_ptr[dq]  =MIN;
//		current_ptr[dq]=MIN;
		
		step1_ptr[dq]=MIN;
		step2_ptr[dq]=MIN;
	}

	Set_DotCorrect(63,21,32); // Default RGB, can override later with DOC_COR 0xDC

}//TLC5940_Init

//==============================================
void Clear_GrayScale()
{

	for (chip_cnt=0; chip_cnt < 48; chip_cnt++) // Simulate 12 Chips 4 board (missing player 0)
	{	
		color_ = 0;//dq*16;			
		// =========================================================
		for(led_12b = 0;led_12b < 12; led_12b++)
			{
				SIN = (color_ & 0b0000100000000000) ? 1 : 0;
			
				SCLK = 1;
				color_ <<= 1;
				SCLK = 0;						
			}	
		SCLK = 0;
	}
	
	//BLANK = 1;
	
	 XLAT  = 1;
	 Nop();
	 XLAT  = 0;
	 					
	SCLK = 1;
	SCLK = 0;			
	
	//BLANK = 0;	
	
	SIN = 0;	
}	


//==============================================
void	Set_DotCorrect(BYTE red, BYTE green, BYTE blue)
{  
      SCLK  = 0;  //   output_low(SCLK);                      
      DCPRG = 0;   //   output_low(DCPRG); 
      VPRG  = 1;  //   output_high(VPRG);      
      XLAT  = 0;  //   output_low(XLAT);    
//    BLANK = 1;  //   output_high(BLANK);     
	
	//// ================================================	
	// DC Correct 16 channel 6 bits each (96 bits)
	//DCPRG=0;// DCPRG=L - connected to EEPROM ,,, DCPRG=H - connected to DC REG
	//VPRG =1; // DC Correct ON
	//VPRG =1; // VPG=gnd - GS mode ,,, VPG=vcc - DC MODE
	
	DCPRG = 1;
	
	/*
	Features:
	Size: 5mm (pin length approx. 25mm)
	Emitted Colour : Red / Green / Blue
	Pins sequence: RED/Common Anode (positive terminal)/Green/Blue
	Lens Color : Diffused
	Luminous Intensity: 4000/8000/5000mcd
	DQ-Lum:
	4000=63
	8000=31.50
	5000=50.40
	
	Forward Voltage (V) : 2.1~3.4
	View Angle: About 25 degree.
	
	Please test to add current limiting resistor, it will be very easy to burn out the LED resistance of a few hundred to 1000ohm can
	R: wavelength 630-640nm Brightness 1000-1200mcd Voltage 1.8-2.0V
	G: wavelength 515-512nm Brightness 3000-5000mcd Voltage 3.2-3.4V
	B: wavelength 465-475nm Brightness 2000-3000mcd Voltage 3.2-3.4V
	
	DQ-Low---Looks good
	R 1000=63.00
	G 3000=21.00
	B 2000=31.50
	DQ-High--Low yellow
	R 1200=63.00
	G 5000=15.12
	B 3000=25.20
	
	*/
	
	for (led_cnt=0; led_cnt < 48; led_cnt++)
	{
		
		if (led_cnt%3==0)// Blue
		{
			//gray_scale= 32;
			gray_scale= blue;
		}		
		if (led_cnt%3==1)// Green
		{
			//gray_scale = 21;
			gray_scale = green;
		}	
		if (led_cnt%3==2)// Red
		{
			//gray_scale = 63;
			gray_scale = red;
		}		
		
		for(gray_6b = 0;gray_6b < 6; gray_6b++)
			{
				SIN = (gray_scale & 0b100000) ? 1 : 0;

				SCLK = 1;
				gray_scale <<= 1;
				SCLK = 0;
			}
	}	                  

	 XLAT  = 1;
	 Nop();
	 XLAT  = 0;
	 
         
	// ================================================	
	// ================================================	
	// ================================================	
		 VPRG =0; // DC Correct OFF    
	//	BLANK = 0;	  
	
	Clear_GrayScale();// Is this needed?????

} //Set_DotCorrect


//==============================================
void	Do_GrayScale(void)
{
//	OverSpin = 0;
//	
//	for (loop =0; loop<ARSIZE; loop++)
//	{
//		MY_Spinner[loop]=ar[loop].wp_pos;
//
//		ar[loop].wp_last=ar[loop].wp_pos;
//		ar[loop].wp_pos = MID; // set value to 128 (255/2) (Middle)
//		
//		if (MY_Spinner[loop] >= MAX || MY_Spinner[loop] <= MIN)
//		{
//			OverSpin = 1;
//		}	
//	}

	    if (GSCLK_TRIGGER == FLAG_TRUE)
	    {      	    
			BLANK = 1;			
			XLAT  = 1;			
			LATCbits.LATC7=1;  
						
			XLAT  = 0;
			
			// Reset GSCLK_Counter = 0
			//GSCLK_Counter = 0;			
			GSCLK_TRIGGER= FLAG_FALSE;
			
			BLANK = 0;

			// =========================================================


			//for (chipcnt=0; chipcnt < (48*banks); chipcnt++) // Simulate 12 Chips 4 board (missing player 0)
			for (chipcnt=0; chipcnt < (48); chipcnt++) // Simulate 12 Chips 4 board (missing player 0)
			{
		        switch(action_ptr[chipcnt])
				{

					//==================================================
					case HOLD:  //HOLD
						
						break;
						
					//==================================================
					case DUTY_ON:  //PWM on
					
						if (step1_ptr[chipcnt]==dutyClk)
						{
							value_ptr [chipcnt]=MAX;
							action_ptr[chipcnt]=DUTY_OFF;
						}	
						break;
					
					//==================================================
					case DUTY_OFF:  //PWM off
					
						if (step2_ptr[chipcnt]==dutyClk)
						{
							value_ptr [chipcnt]=MIN;
							action_ptr[chipcnt]=DUTY_ON;
						}	
						break;
											
//					//==================================================
//					case UP_HOLD:	// Up and Hold
//					
//						value_ptr[chipcnt]++;
//						if (value_ptr [chipcnt] >= MAX)
//						{
//							value_ptr [chipcnt]=MAX;
//							action_ptr[chipcnt]=HOLD;
//						}	
//						break;
//					
//					//==================================================
//					case DW_HOLD:	// Down and Hold
//					
//						value_ptr[chipcnt]--;
//						if (value_ptr[chipcnt] <= MIN	)
//						{
//							value_ptr[chipcnt]=MIN;
//							action_ptr[chipcnt]=HOLD;						
//						}	
//						break;						
					
					//==================================================
					//==================================================
					//==================================================
					//==================================================
					
//action_ptr[15]=SAW_UP;
//value_ptr [15]=MIN;
//step1_ptr [15]=1;					
					case SAW_UP:	// SawTooth up  (1 of 2)
					
						
						if (value_ptr[chipcnt] <= (MAX - step1_ptr[chipcnt]))
						{						
							value_ptr[chipcnt] += step1_ptr[chipcnt];
						}
						else	
						{
							value_ptr[chipcnt]  = MAX;
							//action_ptr[chipcnt] = SAW_DW;
							action_ptr[chipcnt] = HOLD;	
						}							
						break;						
					
					//==================================================
					case SAW_DW:	// SawTooth down (2 of 2)
					
						if (value_ptr[chipcnt] >= (MIN + step1_ptr[chipcnt]))
						{
							value_ptr[chipcnt] -= step1_ptr[chipcnt];
						}
						else	
						{
							value_ptr[chipcnt]  = MIN;
							//action_ptr[chipcnt] = SAW_UP;
							action_ptr[chipcnt] = HOLD;							
						}
						break;						
							
							
					//==================================================
					//==================================================
					//==================================================
						case SAW_UP_TRIG:	// SawTooth up  (1 of 2)
					
						
						if (value_ptr[chipcnt] <= (MAX - step1_ptr[chipcnt]))
						{						
							value_ptr[chipcnt] += step1_ptr[chipcnt];
						}
						else	
						{
							value_ptr[chipcnt]  = MAX;
							action_ptr[chipcnt] = HOLD;							
							TRIGGER=0x01;
						}							
						break;						
					
					//==================================================
					case SAW_DW_TRIG:	// SawTooth down (2 of 2)
					
						if (value_ptr[chipcnt] >= (MIN + step1_ptr[chipcnt]))
						{
							value_ptr[chipcnt] -= step1_ptr[chipcnt];
						}
						else	
						{
							value_ptr[chipcnt]  = MIN;
							action_ptr[chipcnt] = HOLD;						
							TRIGGER=0x01;
						}
						break;										
					//==================================================
					//==================================================
					//==================================================
//					case INVERT:	// INVERT (FlipFlop)
//					
////						current_ptr[chipcnt]++;
////						if (current_ptr[chipcnt]>=step1_ptr[chipcnt])
////						{
////							value_ptr[chipcnt] = ~value_ptr[chipcnt];
////							current_ptr[chipcnt]=0;
////						}						
//						break;						
					
					//==================================================																
		            default:	// Unknown command received
		            
			            break;	
			                  		
				}				
			}	

			// =========================================================
			// === Drive the LEDs, display results =====================
			// =========================================================
		   
			//for (chipcnt=0; chipcnt < (48*banks); chipcnt++) // Simulate 12 Chips 4 board (missing player 0)
			for (chipcnt=0; chipcnt < 48; chipcnt++) // Simulate 12 Chips 4 board (missing player 0)
			{
				color = value_ptr[chipcnt];	
				
				// =========================================================
				for(led12b = 0;led12b <(12);led12b++)
				{
					SIN = (color & 0b0000100000000000) ? 1 : 0;
				  //SIN = (color &         0b10000000) ? 1 : 0;
						
					/*--- Relay Structure ---*/  
					/*--- Relay Structure ---*/  
					/*--- Relay Structure ---*/  					
				//	RELAYbits.Bits.earth = SIN;	
					//RELAYbits.Bits.rca = (color & 0b0000100000000000) ? 1 : 0;
				//	RELAYbits.Bits.rca = (color & 0b10000000) ? 1 : 0;
					/*--- Relay Structure ---*/  
					/*--- Relay Structure ---*/  
					/*--- Relay Structure ---*/  
	
					SCLK = 1;
					color <<= 1;
					SCLK = 0;						
				}	
				SCLK = 0;
				SIN  = 0;
			}
		//	LATDbits.LATD1=0;
	 	}
	 	
}	//Do_GrayScale


//==============================================
unsigned short temp2;

void USB_TLC5940(unsigned char ReceivedDataBuffer[])
{
	// ReceivedDataBuffer layout.
	// 0 = always 0
	// 1 = Command
	// 2 = part 1 value - MSB
	// 3 = part 2 value - LSB
	// 4 = Step value
	
	switch(ReceivedDataBuffer[1]) //TLC Command ID.
		{	
		
		// Dot Corrections
		case DOT_COR: //Set_DotCorrect(63,21,32);
			Set_DotCorrect(	ReceivedDataBuffer[2],
							ReceivedDataBuffer[3],
							ReceivedDataBuffer[4]);

			break;
		
		// SAW
		case SAW_UP:
		case SAW_DW:		
		case SAW_UP_TRIG:
		case SAW_DW_TRIG: 
		
			action_ptr[ReceivedDataBuffer[2]] = ReceivedDataBuffer[1];

			// Set Step
			step1_ptr[ReceivedDataBuffer[2]]=ReceivedDataBuffer[4];
			break;
			
						
		// Most will fit in DEFAULT
		default:
			// Set Action
			action_ptr[ReceivedDataBuffer[2]] = ReceivedDataBuffer[1];	

			// Set Value
			temp2 = (unsigned short)ReceivedDataBuffer[3];
			temp2 = temp2 << 8;
			temp2 = temp2 | (unsigned short)ReceivedDataBuffer[4];
			value_ptr[ReceivedDataBuffer[2]] = temp2;

			// Set Step
			step1_ptr[ReceivedDataBuffer[2]]=ReceivedDataBuffer[4];
			break;
	}
}	

//==============================================
void set_GSCLK_TRIG()
{
	GSCLK_TRIGGER = FLAG_TRUE;
	
	// Inc Duty Clock
	dutyClk++;
	if (dutyClk>=DUTY_CYCLE)
	{
		dutyClk=0;
	}
}

//==============================================
void set_DUTY_CYCLE( BYTE dc)
{
	DUTY_CYCLE = dc;
}	


BYTE get_TRIGGERED()
{
	return TRIGGER;
}	

void clear_TRIGGERED()
{
	TRIGGER = 0x00;
}	