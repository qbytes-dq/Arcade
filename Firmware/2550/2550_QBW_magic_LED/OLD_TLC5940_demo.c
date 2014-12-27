/************************************************************************
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Much of "ChromSysTLC5940lib.h" C18 library was based off of a Hi-Tech C based library found at
http://www.waitingforfriday.com/index.php/USB_RGB_LED_VU_Meter written by
a different author.

Hi-Tech C to C18 conversion done by www.ChromationSystems.com

It is setup for a 48mhz processor speed(20mhz XTAL), requires exclusive use of TMR0,
and CCP1(which uses TMR2 and is pin RC2) Different configurations of timers 
or pins could be used, with code modification.

This code is meant to be ran on a 48 Channel Mono / 16 Channel RGB LED Controller but it can
easily be ported to other devices, please check the HardwareProfile - ChromSys16RGBUSB.h for 
pinouts and other details. No USB is enabled in this example code.
More information at http://www.chromationsystems.com/48channled.html

There are only the most basic of patterns enabled here, but they can be easily altered or expanded.
- There are 2 cycle patterns, one is all the LEDs the same, the other cascades a rainbow/gradient.
- There is 1 flash pattern, the LEDs flash from color to color, change the FlashFrameXX constants to alter
the colors flashed.

If you would like a full featured firmware and software for controlling RGB LEDs please visit:
http://www.chromationsystems.com/colormotion.html

Visit www.ChromationSystems.com/c18-tlc5940.html for updates and more details

Released June 19, 2012 by www.ChromationSystems.com

//************************************************************************/

#include <p18f2550.h>
#include <timers.h> //Interrupt Timers

#include "HardwareProfile - ChromSys16RGBUSB.h" // Setup constants, configuration bits, and Pin #defines 
												// This can be edited for different hardware platforms

typedef union tag8FLAGS { 
    unsigned char asByte;        // allows access to the full 8 bits 
    struct tag8BITS { 
  unsigned b0:1;    
  unsigned b1:1;    
  unsigned b2:1;    
  unsigned b3:1;
  unsigned b4:1;  
  unsigned b5:1;    
  unsigned b6:1;
  unsigned b7:1;
    }; 
} T8_FLAGS;

typedef union tag16FLAGS { 
    unsigned int asByte;        // allows access to the full 16 bits 
    struct tag16BITS { 
  unsigned b0:1;    
  unsigned b1:1;    
  unsigned b2:1;    
  unsigned b3:1;
  unsigned b4:1;  
  unsigned b5:1;    
  unsigned b6:1;
  unsigned b7:1;
  unsigned b8:1;    
  unsigned b9:1;    
  unsigned b10:1;    
  unsigned b11:1;
  unsigned b12:1;  
  unsigned b13:1;    
  unsigned b14:1;
  unsigned b15:1;    
    }; 
} T16_FLAGS; 

#pragma idata //initialized data section

T8_FLAGS Flags;
T8_FLAGS  CycleFlags;

T16_FLAGS  RedFlags; 
T16_FLAGS  GreenFlags; 
T16_FLAGS  BlueFlags; 
 
#define waitingForXLAT Flags.b1
#define updatePending Flags.b2
#define ToggleFlag Flags.b3
#define BounceFlag Flags.b4
#define PackTheData Flags.b5
#define CycleType Flags.b6
#define ChangeFlag Flags.b7

int i=0; //used in for()
int q=0;//used in for()

int bitCounter=0; //used in the TLC library
unsigned char byteCounter=0;//used in the TLC library
int GSCLK_Counter=0;//used in the TLC library
int DATA_Counter=0;//used in the TLC library


int CycleCounter=0; //used as a timing source for the patterns
int CounterHold=0; //used as timing source
unsigned char LEDnum=0; //for altering the LEDs

unsigned char Mode=1;
unsigned char FrameVar[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char FlashFrame=0;
unsigned char SettingsNumber=0; //Pattern Variable
unsigned char MaxSettings=2; //Maximum Pattern Settings
unsigned char MaxFrames=0; //Max Frames for Flash Patterns

unsigned char SwCount=0; //for switch debounce

//alter these Registers to change the colors.
unsigned char RedHoldVal[] ={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
unsigned char GreenHoldVal[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char BlueHoldVal[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//if you are short on RAM, these 2 can be combined with with minimal code altering
unsigned char DotCorrection[48]; //holds the dot correction data to be sent on startup, it is set in main()
unsigned char packedGreyScale[72];//holds the data to be sent after its been expanded from 8-bit to 12-bit number

//START ROM CONSTANTS
const rom unsigned int BtChk[] = { //this table is used for logical ANDs for dynamic bit checks,
0b0000000000000001,0b0000000000000010,0b0000000000000100,0b0000000000001000,
0b0000000000010000,0b0000000000100000,0b0000000001000000,0b0000000010000000,
0b0000000100000000,0b0000001000000000,0b0000010000000000,0b0000100000000000,
0b0001000000000000,0b0010000000000000,0b0100000000000000,0b1000000000000000};

//creates a seamless rainbow cascade
rom unsigned char Pattern1RHold[] ={255,	208,	161,	114	,67,0,0,0,0,0,	0,7,54,101,148,195};
rom unsigned char Pattern1GHold[] ={1, 47	,94,	141	,188,235	,228,181,134,87,40,0,0,0,0,0,0};
rom unsigned char Pattern1BHold[] ={0,0,0,0,0,0,27,	74,121,168,215,248,201,154,107,60};
rom unsigned char Pattern1FrameVar[]={0,0,0,0,0,0, 1,1,1,1,1,2,2,2,2,	2};


 //Red - Yellow - Green - Teal - Blue - Purple - White
 //Flash Frames, data is used to fill each LED, 8 frames with 3 bytes per RGB output(16)
 rom unsigned char FlashFrameR1[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameR2[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameR3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameR4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameR5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameR6[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameR7[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameR8[]={255,0,0,255,0,0,255,0,0,255,0,0,255,0} ;   
 
 rom unsigned char FlashFrameG1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameG2[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameG3[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameG4[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameG5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameG6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameG7[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameG8[]={0,0,255,0,0,255,0,0,255,0,0,255,0,255};   
 
 rom unsigned char FlashFrameB1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameB2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameB3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 rom unsigned char FlashFrameB4[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameB5[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameB6[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameB7[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
 rom unsigned char FlashFrameB8[]= {0,255,0,0,255,0,0,255,0,0,255,0,255,0};     
 
//Function & Macro Declaration
#define bsf(var,bitno) var=(var | BtChk[bitno]);
#define bcf(var,bitno) var=(var ^ BtChk[bitno]);

//define Mode Constants, makes the code easier to follow, only cycle and flash are implemented in this soruce code
#define mStall 0
#define mCycle 1
#define mFlash 2
#define mLive 3 //not used in this code
#define mSlideUp 4 //not used in this code
#define mSlideDown 5 //not used in this code

#define LEDTotal 16 //16 RGB Channels

//Function Declarations
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
unsigned char ReadEEPROM(unsigned char address);
void WriteEEPROM(unsigned int address, unsigned char data);

void InitTLC5940(unsigned char DCset);
void UserInit(void);
void set_timer(void);
void XLATinterrupt(void);
void setInitGrayScales(void);
void PackData(void);

void ChangePattern(void);
void ModeFlash(void);
void ModeCycle(void);
unsigned char BitCheck(unsigned int var,unsigned int bitno);
void SwitchPress1(void);
void SwitchPress2(void);
void SwitchPress3(void);

#if defined(__18CXX)
	#define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
	#else	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
	#endif
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#endif
	#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	//Note: If this project is built while one of the bootloaders has
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#endif	//end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"

	#pragma code
	
	#include "ChromSysTLC5940lib.h" //holds all the TLC5940 functions

//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode

	void YourHighPriorityISRCode()
	{
//run other code here
	}

#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()
{
	if (INTCONbits.TMR0IF) //uses TMR0 as timing source
	{
	PackTheData=1;	
	CycleCounter--;	//this is the timer that controls the main functions such as ModeCycle and ModeFlash
	XLATinterrupt(); //TLC required function
	INTCONbits.TMR0IF = 0;// Clear the timer0 interrupt flag
	INTCONbits.GIEL = 1;
	}
}//end function


void MainLoop (void)
{
//Monitor the switches
if(Switch1==0) SwitchPress1();
if(Switch2==0) SwitchPress2();
if(Switch3==0) SwitchPress3();

//this monitors the timer that allows the LED colors to be altered
if(CycleCounter <= 0)
{
	CycleCounter=CounterHold;//TimerHold is the overall speed of the pattern
	
	switch(Mode)
	{
	case mCycle:
		ModeCycle();
		break;
	case mFlash:
		ModeFlash();
		break;	
	}			
	PackData();	//preps the data for sending to the TLCs
}	

_asm//loop forever
goto MainLoop
_endasm
}

void ModeFlash(void)
{
// This uses ROM variables to fill the color Hold Registers
// The LEDs will flash from color to color at specified speed

//MaxFrames is set in PatternChange and effects how many frames are ran
//before starting at 0 again	
	if(FlashFrame != MaxFrames) FlashFrame++;
	else FlashFrame=0;
	
	switch(FlashFrame)
	{
	case 0:
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR1[i]; 
		GreenHoldVal[i] = FlashFrameG1[i];
		BlueHoldVal[i] = FlashFrameB1[i];
		}	
		break;
	case 1:
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR2[i]; 
		GreenHoldVal[i] = FlashFrameG2[i];
		BlueHoldVal[i] = FlashFrameB2[i];
		}
		break;
	case 2:
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR3[i]; 
		GreenHoldVal[i] = FlashFrameG3[i];
		BlueHoldVal[i] = FlashFrameB3[i];
		}
		break;
	case 3:
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR4[i]; 
		GreenHoldVal[i] = FlashFrameG4[i];
		BlueHoldVal[i] = FlashFrameB4[i];
		}
		break;
	case 4:
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR5[i]; 
		GreenHoldVal[i] = FlashFrameG5[i];
		BlueHoldVal[i] = FlashFrameB5[i];
		}
		break;
	case 5:
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR6[i]; 
		GreenHoldVal[i] = FlashFrameG6[i];
		BlueHoldVal[i] = FlashFrameB6[i];
		}
		break;
	case 6:	
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR7[i]; 
		GreenHoldVal[i] = FlashFrameG7[i];
		BlueHoldVal[i] = FlashFrameB7[i];
		}
		break;
	case 7:	
		for(i=0; i != LEDTotal; i++)
		{
		RedHoldVal[i] = FlashFrameR8[i]; 
		GreenHoldVal[i] = FlashFrameG8[i];
		BlueHoldVal[i] = FlashFrameB8[i];
		}
		break;
	}				
}//end func


void ModeCycle(void)
{
// Two methods of cycling the colors up or down:
// The first is the simpliest, only 2 colors change and together thier values will equal 255,for a consistant 
// brightness, when one goes down the other goes up,  example yellow is: Red=128, Green=128
 
//The second is a full color cycle, it cycles to inbetween colors, its not consistant brightness but overall
//looks better, example Yellow is: Red=255, Green=255

//There are many more dynamic ways to do this, but this is the simplest

	if(CycleType==1)
	{	
	 for(i=0; i != LEDTotal; i++)
	  {
	  LEDnum=i;   
	  switch(FrameVar[LEDnum])
	  {
	  case 0: //red to green
	    GreenHoldVal[LEDnum]++;
	    
	    if(RedHoldVal[LEDnum] != 0) RedHoldVal[LEDnum]--;
	    if(GreenHoldVal[LEDnum]==255) FrameVar[LEDnum]++;
	    break;
	    
	  case 1: //green to blue
	    BlueHoldVal[LEDnum]++;  
	    
	    if(GreenHoldVal[LEDnum] != 0) GreenHoldVal[LEDnum]--;
	    if(BlueHoldVal[LEDnum]==255) FrameVar[LEDnum]++;
	    break;
	    
	  case 2: //blue to red
	    RedHoldVal[LEDnum]++;
	    
	    if(BlueHoldVal[LEDnum] != 0) BlueHoldVal[LEDnum]--;    
	    if(RedHoldVal[LEDnum]==255)FrameVar[LEDnum]=0;;  
	    break;    
	    }  //end switch
	  }  //end for
	}//end if
	else
	{
	  for(i=0; i != LEDTotal; i++)
	  {
	  LEDnum=i;
	  switch(FrameVar[LEDnum])
	  {
	  case 0: //white to red
	    GreenHoldVal[LEDnum]--;    
	    if(BlueHoldVal[LEDnum] != 0) BlueHoldVal[LEDnum]--;   
	    if(GreenHoldVal[LEDnum]==0) FrameVar[LEDnum]++;
	    break;
	  case 1: //red to yellow
	    GreenHoldVal[LEDnum]++;
	    if(GreenHoldVal[LEDnum]==255) FrameVar[LEDnum]++;
	    break;
	  case 2://yellow to green
	    RedHoldVal[LEDnum]--;
	    if(RedHoldVal[LEDnum]==0) FrameVar[LEDnum]++;
	    break; 
	  case 3: //green to teal
	    BlueHoldVal[LEDnum]++;
	    if(BlueHoldVal[LEDnum]==255) FrameVar[LEDnum]++;
	    break;  
	  case 4: //teal to blue
	    GreenHoldVal[LEDnum]--;
	    if(GreenHoldVal[LEDnum]==0) FrameVar[LEDnum]++;
	    break;
	  case 5: //blue to purple
	    RedHoldVal[LEDnum]++;
	    if(RedHoldVal[LEDnum]==255)FrameVar[LEDnum]++;   
	    break;    
	  case 6: //blue to white
	    GreenHoldVal[LEDnum]++;
	    if(RedHoldVal[LEDnum]==255) FrameVar[LEDnum] = 0;   
	    break;
	    }  //end switch
	  }//end for
	}//end else
}//end func

void main (void)
{
	//Automatically starts here
	UserInit(); //All hardware and some variables setup here
		
	SettingsNumber=1; // or ReadEEPROM(0x00);
	ChangePattern(); //Does the setup for the selected pattern and returns
	
	_asm 
	goto MainLoop //Everything happens from this function
	_endasm
}


void ChangePattern(void)
{
// This function is called when the pattern is to be changed, it sets up
// all the required variables
		
	switch(SettingsNumber)
	{
	case 0: //full fade	
		for(i=0; i != LEDTotal;i++)
		{
		RedHoldVal[i]=255;	
		GreenHoldVal[i]=0;	
		BlueHoldVal[i]=0;		
		FrameVar[i]=0;	
		}
		CounterHold=10;	
		CycleType=0;
		Mode=mCycle;	
		break;
	case 1://casecade fade
		for(i=0; i != LEDTotal;i++)
		{
		RedHoldVal[i]=Pattern1RHold[i];	
		GreenHoldVal[i]=Pattern1GHold[i];		
		BlueHoldVal[i]=Pattern1BHold[i];		
		FrameVar[i]=Pattern1FrameVar[i];	
		}
		CounterHold=10;
		CycleType=1;
		Mode=mCycle;			
		break;		
	case 2: //flash pattern
		FlashFrame=0;
		ModeFlash();
		MaxFrames=7;
		CounterHold=1000;
		Mode=mFlash;
		break;		
	}	
	//more patterns can be added but also alter MaxSettings variable	
}//end func


//================= START BUTTONS ===============

void SwitchPress1(void)
{
	if(Switch1 == 0) 
	{
	SwCount++;
	
	if(SwCount >=100)
	{
	SwCount=0;
	
	if(SettingsNumber < MaxSettings) SettingsNumber++;
	else SettingsNumber=0;
	
	//WriteEEPROM(0x00, SettingsNumber);
	
	ChangePattern();
	
	while(Switch1==0) Nop();
	}
	else return;
	}
}//end Function

void SwitchPress2(void)
{
	if(Switch2 == 0) 
	{
	SwCount++;
	
	if(SwCount >=100)
	{
	SwCount=0;
	
	//toggles the interrupts on or off, will disable the LED outputs
	INTCONbits.GIE =! INTCONbits.GIE;
	
	while(Switch2==0) Nop();
	}
	else return;
	}
}//end Function

void SwitchPress3(void)
{
	if(Switch3 == 0) 
	{
	SwCount++;
	
	if(SwCount >=100)
	{
	SwCount=0;
	
	if(SettingsNumber > 0) SettingsNumber--;
	else SettingsNumber=MaxSettings;
	
	//WriteEEPROM(0x00, SettingsNumber);
	
	ChangePattern();
	
	while(Switch3==0) Nop();
	}
	else return;
	}
}//end Function

//========================================

unsigned char BitCheck(unsigned int var,unsigned int bitno) //returns 1 or 0
{
	//dynamic bit Checks
	bitno = BtChk[bitno];
	
	if(var&bitno)
	{
	return 1;
	}
	return 0;
}


void UserInit(void)
	{
	Flags.asByte=0x00; //clear all the flags

	OSCCONbits.IRCF0=1;
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1; //int oscillator set for 8Mhz

	ADCON0 = 0x00; //turn off and setup unwanted hardware
	ADCON1 = 0x0F; 
	ADCON2 = 0x00;
	CMCON=0x07;

	TRISA = 0x00; //set everything to outputs
	TRISB = 0x00;
	TRISC = 0x00;

	Flags.asByte=0x00;

	TRISBbits.RB4=1; //setup switches
	TRISBbits.RB3=1;
	TRISBbits.RB2=1;

	ToggleFlag=0;
	BounceFlag=0;
	waitingForXLAT = 1; //flag used with TLC5940 Library
	updatePending=1; //flag is used if new data is pending

	PORTA=0x00;
	PORTB=0x00;
	PORTC=0x00;
	LATA = 0x00;
	LATB = 0x00;
	LATC = 0x00;

	PIR1bits.CCP1IF=0; //clear CCP int
	PIR2bits.CCP2IF=0; //clear CCP int

	INTCONbits.PEIE = 1; // Enable Peripheral interrupt 
	INTCONbits.GIE = 1;	// Enble Global interrupt, REQUIRED FOR LOW PRIORITY

//if any custom dot correction values are required
//set all of them below, then call InitTLC5940(0) to use the custom values or
//InitTLC5940(1) to have all the dot correction values set to maximum current.
//packedGreyScale does double duty for Dot Correction values, which are only used at startup

// Just like PackData(), the Dot Correction values must be arranged correctly i
// so the outputs will be correct. It would be better if this was somehow in a for()
// but its to confusing, but I always set all Dot Correction to 63, the white it creates is
// close enough, as the colors seem pretty even. DCcolor constants set in HardwareProfile

	//start TLC 3		
	packedGreyScale[0]=DCblue; //blue 11

	packedGreyScale[1]=DCred;//red 12
	packedGreyScale[2]=DCgreen; //green 12
	packedGreyScale[3]=DCblue;//blue 12
	
	packedGreyScale[4]=DCred;//red 13
	packedGreyScale[5]=DCgreen; 	//green 13
	packedGreyScale[6]=DCblue;//blue 13
	
	packedGreyScale[7]=DCred;//red 14
	packedGreyScale[8]=DCgreen; //green 14
	packedGreyScale[9]=DCblue;//blue	14
	
	packedGreyScale[10]=DCred;//red 15
	packedGreyScale[11]=DCgreen; //green 15
	packedGreyScale[12]=DCblue; //blue 15

	packedGreyScale[13]=DCred; //red 16
	packedGreyScale[14]=DCgreen; //green 16
	packedGreyScale[15]=DCblue; //blue 16
	
//start TLC 2		
	packedGreyScale[16]=DCgreen;  //green6
	packedGreyScale[17]=DCblue; //blue 6
	
	packedGreyScale[18]=DCred;//red 7
	packedGreyScale[19]=DCgreen;//green 7
	packedGreyScale[20]=DCblue; //blue 7
	
	packedGreyScale[21]=DCred; //red 8
	packedGreyScale[22]=DCgreen; //green 8
	packedGreyScale[23]=DCblue;  //blue 8
	
	packedGreyScale[24]=DCred; //red 9
	packedGreyScale[25]=DCgreen;	//green 9
	packedGreyScale[26]=DCblue;	//blue 9
	
	packedGreyScale[27]=DCred;	//red 10
	packedGreyScale[28]=DCgreen;  //green 10
	packedGreyScale[29]=DCblue; //blue 10
	
	packedGreyScale[30]=DCred;	//red 11
	packedGreyScale[31]=DCgreen;	//green 11
	
//start TLC 1		
	packedGreyScale[32]=DCred;	//red 1
	packedGreyScale[33]=DCgreen;	//green 1
	packedGreyScale[34]=DCblue;	//blue 1
	
	packedGreyScale[35]=DCred;	//red 2
	packedGreyScale[36]=DCgreen;	//green 2
	packedGreyScale[37]=DCblue;	//blue 2
	
	packedGreyScale[38]=DCred;	//red 3
	packedGreyScale[39]=DCgreen;	//green 3
	packedGreyScale[40]=DCblue;	//blue 3
	
	packedGreyScale[41]=DCred;	//red4
	packedGreyScale[42]=DCgreen;	//green4
	packedGreyScale[43]=DCblue;	//blue 4
	
	packedGreyScale[44]=DCred;	//red 5
	packedGreyScale[45]=DCgreen;	//green 5
	packedGreyScale[46]=DCblue;	//blue 5
	
	packedGreyScale[47]=DCred;	//red 6


	//All the required hardware is setup in the InitTLC5940() function 
	InitTLC5940(0); //Custom Dot Correction set the 0 to 1 to set to max current
}//end UserInit

// ============== EEPROM ROUTINES ==================

unsigned char ReadEEPROM(unsigned char Address)
{
    EECON1=0;                   //ensure CFGS=0 and EEPGD=0 
    EEADR = Address;
    EECON1bits.RD = 1;
		return EEDATA; // Return with the data
}

//==================================
// EEPROM write routine

void WriteEEPROM(unsigned int Address, unsigned char Data)
{
static unsigned char GIE_Status; // Variable to save Global Interrupt Enable bit

//EEADRH = (unsigned char)(Address>>8); // Load the high byte of the EEPROM address
EEADR = (unsigned char)Address; // Load the low byte of the EEPROM address
EEDATA = Data; // Load the EEPROM data
EECON1bits.WREN = 1; // Enable EEPROM writes
GIE_Status = INTCONbits.GIE; // Save the Global Interrupt Enable bit
INTCONbits.GIE = 0; // Disable global interrupts
EECON2 = 0x55; // Required sequence to start the write cycle
EECON2 = 0xAA; // Required sequence to start the write cycle
EECON1bits.WR = 1; // Required sequence to start the write cycle
INTCONbits.GIE = GIE_Status; // Restore the Global Interrupt Enable bit
EECON1bits.WREN = 0; // Disable EEPROM writes
while (EECON1bits.WR); // Wait for the write cycle to complete
}

