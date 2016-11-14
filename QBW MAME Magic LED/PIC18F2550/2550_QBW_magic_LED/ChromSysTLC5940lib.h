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

****************************************************************************

Much of this C18 library was based off of a Hi-Tech C based library found at
http://www.waitingforfriday.com/index.php/USB_RGB_LED_VU_Meter by
a different author.

Hi-Tech C to C18 conversion done by www.ChromationSystems.com

It is setup for a 48mhz processor speed, requires exclusive use of TMR0,
CCP1(which uses TMR2 and is pin RC2)

Different configurations of timers or pins could be used, with code modifications.

Visit www.ChromationSystems.com/c18-tlc5940.html for updates and more details
Please send any corrections, constructive input or anything of the sort to

Support@ChromationSystems.com

A kit, Utilizing 3x TLC5940 with USB communication is avaialble from the Web Store

More information at http://www.chromationsystems.com/48channled.html

Version 2, various tweaks and better comments over the first version,

====== Released 6/5/12 by www.ChromationSystems.com =======

************************************************************************/

void XLATinterrupt(void)
{
	// Process the XLAT interrupt		
	// Resets the LED outputs for the next cycle
	BLANK = 1;
	
	// Are we waiting for an XLAT pulse to latch new data?
	if (waitingForXLAT == 1)
	{
		XLAT = 1; 		// Pulse the XLAT signal

		XLAT = 0;
		waitingForXLAT = 0; 		// Clear the flag
	}
	
	// Turn on the LEDs
	BLANK = 0;	
	// Note: Once we have reset the 5940's PWM counter by toggling the BLANK pin we can
	// shift in the serial data (since the PWM pulse for GSCLK continues to run
	// in the background).  The shifting of the data must happen before the next
	// XLAT interrupt is due which means we have about 16,000 uS to do this.
	// As you add more and more TLC5940s this shifting will take longer and longer
	// until you simply can't shift the data in time, then it's time to buy another
	// PIC if you want to support more LED channels...
	//
	// Measuring this with an oscilloscope, 3 TLC5940s take about 250uS (measuring from
	// the start of the interrupt to the end) which means we can (in theory) support
	// about 20 TLC5940s cascaded (320 LED channels from a single PIC, not bad :)


if (updatePending == 1) //Is there new packed data ready to be sent?
{
	PIR1bits.SSPIF = 0; //clear transmission flag
	
		for (i = (NumTLC5940 * 24); i >= 0; i--)// i was byteCounter
		{
			// Send the byte to the SPI buffer

			SSPBUF = packedGreyScale[i];


			//not necassary as the time it takes to finish the for() iteration and go on to the next
			//is enough time for the byte to finish sending
			
		//while (PIR1bits.SSPIF == 0); // Wait for the transmission complete flag, Not Needed with fast SPI
		
			// Reset the transmission complete flag
			PIR1bits.SSPIF = 0;
		}
		
		// Serial data is now updated, clear the flag
		updatePending = 0;
		
		// Set the waiting for XLAT flag to indicate there is data waiting to be latched
		waitingForXLAT = 1;
		PackTheData=1;
}
	
		// Prepare for Next XLAT interrupt
		TMR0L  = XLATCOUNTL;	// Reset the timer0 counter
		TMR0H  = XLATCOUNTH;
}


void SendDotCorrection(void)
{
	// Set VPRG high (Dot correction mode)
	VPRG = 1;
	
	// Optionaly an array of unsigned char values which are 8 bits each, however the dot 
	// correction is expecting 6 bit data for each channel (0-63) so only send the 6 least
	// significant bits of each entry in the array.  The values need to be sent MSB first.

	//sends 6 bits per channel, 16 channels per chip x 3 chips
	
	q=0;	
	for (byteCounter = 0; byteCounter< (NumTLC5940 * 16); byteCounter++)
	{
		unsigned char bitMask = 0b00100000;	

		for (bitCounter = 5; bitCounter >= 0; bitCounter--)
		{
			// Set SIN to DC data bit
			q++;
			SIN = (packedGreyScale[byteCounter] & bitMask) >> bitCounter;			
			// Pulse the serial clock
			SCLK = 1;
			Nop();
			Nop();
			Nop();						
			SCLK = 0;			
			// Move to the next bit in the mask
			bitMask >>= 1;
		}
	}		
	// Pulse XLAT
	XLAT = 1;
	Nop();
	Nop();	
	XLAT = 0;
	
}//end SendDotCorrection



// Since the TLC5940 requires an 'extra' SCLK pulse the first time the grayscales
// are cycled we have to do one input cycle manually, after this we can use the SPI
// module for extra serial interface speed (this is due to the fact that there is
// no way to tell the SPI module to generate the extra clock pulse).
void setInitGrayScales()
{
	// Set VPRG = Low (Grayscale mode)
	VPRG = 0;
	
	// Reset GSCLK_Counter = 0
	GSCLK_Counter = 0;
	
	// Reset Data_Counter = 0
	DATA_Counter = 0;
	
	// Set BLANK = High (Turn LED's Off)
	BLANK = 1;
	
	for (GSCLK_Counter = 0; GSCLK_Counter < 4096; GSCLK_Counter++)
	{
		if (DATA_Counter > (NumTLC5940 * 192) )//amount of registers 3 * 192 data bits
		{
			// Pulse GSCLK
			GSCLK = 1;
			GSCLK = 0;
		}
		else
		{
			// Set SIN to the greyscale data bit

		
			SIN = 0; // We just output zero for everything during initialisation		
			// Pulse SCLK
			SCLK = 1;
			SCLK = 0;
			
			// Increment Data_Counter
			DATA_Counter++;
			
			// Pulse GSCLK
			GSCLK = 1;
			GSCLK = 0;
		}	
	}
	
	// Pulse XLAT to latch in GS data
	XLAT = 1;
	XLAT = 0;

	// Set BLANK = Low (Turn LED's on)
	BLANK = 0;
	
	// Send an extra SCLK pulse since this is the first grayscale cycle
	// after the dot correction data has been set
		
	// Pulse SCLK
	SCLK = 1;
	SCLK = 0;
}	



void InitTLC5940(unsigned char DCset)
{
	// Initialise device pins, these are defined in "HardwareProfile - ChromSys16RGBUSB.h"
	GSCLK 	= 0;
	SCLK 	= 0;
	VPRG 	= 1;
	XLAT 	= 0;
	BLANK 	= 1;
	

if(DCset==1) //parameter passed with function call, if 1, all dot correction values are set to max current
{
	for(i=0; i != (NumTLC5940 * 16);i++) packedGreyScale[i]=63;//sets all dot correction vars to full on
}

	SendDotCorrection();//send dot correction
	setInitGrayScales(); //set intial values

//setup SPI
	SSPSTAT = 0b11000000;	// SPI Master
							// Tx occurs on active to idle transition
	SSPCON1 = 0b00100000;	// Serial port enabled
							// Speed is Fosc/4 = 12Mhz, fast as the microcontroller can

	// PWM1 is used to generate the GSCLK clock signal
	//
	// Everything is setup to update as fast as possible for the highest PWM frequency possible.
	// It all could be slowed down if processor time is in short supply
	// PWM 1 uses TMR2, setup to go fast as possible

	//Trying for 1500 hz * 4096 steps = 6,144,000 hz, closest is 6,000,000 hz

	PR2 = 1;
	T2CON = 0b00000100;//Enabled, 1:1 post, prescale 1:1

	CCPR1L = 0b00000001; //setup CCP1
	CCP1CON = 0b00001100;
	

	
	// An interrupt on timer0 is used to generate the XLAT signal (one for
	// every 4096 GSCLK pulses)

	// Timer0 should interrupt every 4096 pulses of the PWM1
	// PWM1 period is 6,000,000 hz = pulse every 167 nS
	//
	// Fosc is 48,000,000 (48Mhz), so Fosc/4 = 12,000,000
	// Therefore there are 12 ticks per 1uS

	// I calculated TMR0 should be preloaded with 49,168  to interrupt every 682 uS but that 
	// caused the LEDs to dim and appear choppy, through a bit of trial and error 
	// 62,719  is the best preload value. Please contact me if you have any input or corrections.
		
	RCONbits.IPEN = 1;				// Enable prioritised interrupts
	
	INTCON2bits.TMR0IP = 0;		//EDITED FROM ORIG	- DEBUG
									// Set timer0 interrupt to high priority
	INTCONbits.TMR0IF = 0;				// Clear the timer0 interrupt flag

	TMR0L  = XLATCOUNTL;	// Reset the timer0 counter
	TMR0H  = XLATCOUNTH;	//These contsants are set in "HardwareProfile - ChromSys16RGBUSB.h"


	T0CON = 0b10000000; // Timer0 on, 16-bit and 1:2 pre

	INTCONbits.TMR0IE = 1;			// Enable the timer0 interrupt

	// Global enable high priority interrupts
	INTCONbits.GIEH = 1;			// Global enable all high priority interrupts
	
	// Global enable low priority interrupts
	INTCONbits.GIEL = 1;
}



void PackData(void)
{	
// This is a bit confusing as the TLC5940 expects 12-bit numbers, and its RAM efficient to use 8-bit variables,
// so the data must be packed up in a particular way so the outputs will be in the right
// order as specified on the datasheet. As the outputs are pinned R->G->B->Repeat, so the data must
// be mixed, and packed into 8-bit registers
				
// Here the 8-bit HoldVals are bit shifted, making the 4 LSB all 0. Producing a 12-bit number
// so no LED is ever fully on, but they are still plenty bright. XLATCOUNT & XLATCOUNTL can
// be adjusted to make up the difference if you like.

// Otherwise each HoldVal could be multiplied by 16 to convert the 8-bit number
// to a 12 bit number that the TLC5940 expects

// If anyone has a better, more dynamic way to do this, please Contact Me I would like to hear it.


// pack 24 bytes = 16 channels -> then reverse the pack[] order......
packedGreyScale[23]= RedHoldVal[0];
packedGreyScale[22]= (GreenHoldVal[0] >> 4) & 0x0F; 
packedGreyScale[21]= (GreenHoldVal[0] << 4) & 0xF0;
packedGreyScale[20]= BlueHoldVal[0];
packedGreyScale[19]= (RedHoldVal[1] >> 4) & 0x0F;
packedGreyScale[18]= (RedHoldVal[1] << 4) & 0xF0;
packedGreyScale[17]= GreenHoldVal[1];
packedGreyScale[16]= (BlueHoldVal[1] >> 4) & 0x0F; 
packedGreyScale[15]= (BlueHoldVal[1] << 4) & 0xF0;
packedGreyScale[14]= RedHoldVal[2];
packedGreyScale[13]= (GreenHoldVal[2] >> 4) & 0x0F; 
packedGreyScale[12]= (GreenHoldVal[2] << 4) & 0xF0;
packedGreyScale[11]= BlueHoldVal[2];
packedGreyScale[10]= (RedHoldVal[3] >> 4) & 0x0F;
packedGreyScale[9]= (RedHoldVal[3] << 4) & 0xF0;
packedGreyScale[8]= GreenHoldVal[3];
packedGreyScale[7]= (BlueHoldVal[3] >> 4) & 0x0F; 
packedGreyScale[6]= (BlueHoldVal[3] << 4) & 0xF0;
packedGreyScale[5]= RedHoldVal[4];
packedGreyScale[4]= (GreenHoldVal[4] >> 4) & 0x0F; 
packedGreyScale[3]= (GreenHoldVal[4] << 4) & 0xF0;
packedGreyScale[2]= BlueHoldVal[4];
packedGreyScale[1]= (RedHoldVal[5] >> 4) & 0x0F;
packedGreyScale[0]= (RedHoldVal[5] << 4) & 0xF0;
//24 bytes
packedGreyScale[47]= GreenHoldVal[5];
packedGreyScale[46]= (BlueHoldVal[5] >> 4) & 0x0F; 
packedGreyScale[45]= (BlueHoldVal[5] << 4) & 0xF0;
packedGreyScale[44]= RedHoldVal[6];
packedGreyScale[43]= (GreenHoldVal[6] >> 4) & 0x0F; 
packedGreyScale[42]= (GreenHoldVal[6] << 4) & 0xF0;
packedGreyScale[41]= BlueHoldVal[6];
packedGreyScale[40]= (RedHoldVal[7] >> 4) & 0x0F;
packedGreyScale[39]= (RedHoldVal[7] << 4) & 0xF0;
packedGreyScale[38]= GreenHoldVal[7];
packedGreyScale[37]= (BlueHoldVal[7] >> 4) & 0x0F; 
packedGreyScale[36]= (BlueHoldVal[7] << 4) & 0xF0;
packedGreyScale[35]= RedHoldVal[8];
packedGreyScale[34]= (GreenHoldVal[8] >> 4) & 0x0F; 
packedGreyScale[33]= (GreenHoldVal[8] << 4) & 0xF0;
packedGreyScale[32]= BlueHoldVal[8];
packedGreyScale[31]= (RedHoldVal[9] >> 4) & 0x0F;
packedGreyScale[30]= (RedHoldVal[9] << 4) & 0xF0;
packedGreyScale[29]= GreenHoldVal[9];
packedGreyScale[28]= (BlueHoldVal[9] >> 4) & 0x0F; 
packedGreyScale[27]= (BlueHoldVal[9] << 4) & 0xF0;
packedGreyScale[26]= RedHoldVal[10];
packedGreyScale[25]= (GreenHoldVal[10] >> 4) & 0x0F; 
packedGreyScale[24]= (GreenHoldVal[10] << 4) & 0xF0;
//24 bytes
packedGreyScale[71]= BlueHoldVal[10];
packedGreyScale[70]= (RedHoldVal[11] >> 4) & 0x0F;
packedGreyScale[69]= (RedHoldVal[11] << 4) & 0xF0;
packedGreyScale[68]= GreenHoldVal[11];
packedGreyScale[67]= (BlueHoldVal[11] >> 4) & 0x0F; 
packedGreyScale[66]= (BlueHoldVal[11] << 4) & 0xF0;
packedGreyScale[65]= RedHoldVal[12];
packedGreyScale[64]= (GreenHoldVal[12] >> 4) & 0x0F; 
packedGreyScale[63]= (GreenHoldVal[12] << 4) & 0xF0;
packedGreyScale[62]= BlueHoldVal[12];
packedGreyScale[61]= (RedHoldVal[13] >> 4) & 0x0F;
packedGreyScale[60]= (RedHoldVal[13] << 4) & 0xF0;
packedGreyScale[59]= GreenHoldVal[13];
packedGreyScale[58]= (BlueHoldVal[13] >> 4) & 0x0F; 
packedGreyScale[57]= (BlueHoldVal[13] << 4) & 0xF0;
packedGreyScale[56]= RedHoldVal[14];
packedGreyScale[55]= (GreenHoldVal[14] >> 4) & 0x0F; 
packedGreyScale[54]= (GreenHoldVal[14] << 4) & 0xF0;
packedGreyScale[53]= BlueHoldVal[14];
packedGreyScale[52]= (RedHoldVal[15] >> 4) & 0x0F;
packedGreyScale[51]= (RedHoldVal[15] << 4) & 0xF0;
packedGreyScale[50]= GreenHoldVal[15];
packedGreyScale[49]= (BlueHoldVal[15] >> 4) & 0x0F; 
packedGreyScale[48]= (BlueHoldVal[15] << 4) & 0xF0;

PackTheData=0; //data is packed
updatePending=1; //set flag to send the data on the next XLAT interrupt
}



