/************************************************************************
	main.c

	WFF USB Generic HID Demonstration 3
    usbGenericHidCommunication reference firmware 3_0_0_0
    Copyright (C) 2011 Simon Inns

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

	Email: simon.inns@gmail.com

************************************************************************/

#define Hz256
//#define Hz200

#ifndef MAIN_C
	#define MAIN_C
	
	
	#include <string.h> /* for 'strcpypgm2ram' */
	#include <stdlib.h> /* for 'atoi' */
	#include "pwm.h"
	
	#include "eeprom.h"
	
	// Global includes
	// Note: string.h is required for sprintf commands for debug
	#include <string.h>
	
	// Local includes
	#include "HardwareProfile.h"
	#include "debug.h"
	
	// TI TLC5940 
	#include "tlc5940.h"
	// Microchip Application Library includes
	// (expects V2.9a of the USB library from "Microchip Solutions v2011-07-14")
	//
	// The library location must be set in:
	// Project -> Build Options Project -> Directories -> Include search path
	// in order for the project to compile.
	#include "./USB/usb.h"
	#include "./USB/usb_function_hid.h"
		
	// Ensure we have the correct target PIC device family
	#if !defined(__18F4550) && !defined(__18F2550)
		#error "This firmware only supports either the PIC18F4550 or PIC18F2550 microcontrollers."
#endif

// Define the globals for the USB data in the USB RAM of the PIC18F*550
#pragma udata
#pragma udata USB_VARIABLES=0x500
	unsigned char ReceivedDataBuffer[64];
	unsigned char ToSendDataBuffer[64];
#pragma udata
	
USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;

//BOOL blinkStatusValid = FLAG_TRUE;
// http://www.xargs.com/pic/c18large.html

// ==========================================================
// ==========================================================
// ==========================================================



// PIC18F4550/PIC18F2550 configuration for the WFF Generic HID test device
//#pragma config PLLDIV=12, CPUDIV=OSC1_PLL2, USBDIV=2, FOSC=HSPLL_HS// FCMEM=OFF
#pragma config PLLDIV   = 12
#pragma config CPUDIV   = OSC1_PLL2   
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
// #pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
// #pragma config ICPRT    = OFF
#pragma config XINST    = OFF
#pragma config CP0      = OFF
#pragma config CP1      = OFF
// #pragma config CP2      = OFF
// #pragma config CP3      = OFF
#pragma config CPB      = OFF
// #pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
// #pragma config WRT2     = OFF
// #pragma config WRT3     = OFF
#pragma config WRTB     = OFF
#pragma config WRTC     = OFF
// #pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
// #pragma config EBTR2    = OFF
// #pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF

// Private function prototypes
static void initialisePic(void);
void processUsbCommands(void);
void applicationInit(void);
void USBCBSendResume(void);
void highPriorityISRCode();
void lowPriorityISRCode();


void GSCLK_Event();

// Remap vectors for compatibilty with Microchip USB boot loaders
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

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER) || defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
#endif

#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void)
{
     _asm goto highPriorityISRCode _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void)
{
     _asm goto lowPriorityISRCode _endasm
}

#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER) || defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
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
#endif




// High-priority ISR handling function
#pragma interrupt highPriorityISRCode
void highPriorityISRCode()
{
	// Application specific high-priority ISR code goes here
	
	#if defined(USB_INTERRUPT)
		// Perform USB device tasks
		USBDeviceTasks();
	#endif

}

/*--- Relay Structure ---*/
/*--- Relay Structure ---*/
/*--- Relay Structure ---*/
/*--- Relay Structure ---*/

// Low-priority ISR handling function
#pragma interruptlow lowPriorityISRCode
void lowPriorityISRCode()
{
	// Application specific low-priority ISR code goes here
		
	//    if (INTCONbits.TMR0IF)
	if (INTCONbits.T0IE && INTCONbits.T0IF)
	    {
			// Timer interrupt
			#if defined(Hz50)			
				//50 hz
				//T0CON	 = 0x81;				
			    TMR0H	 = 0x15;
			    TMR0L	 = 0xA0;		  		
			#endif	
			#if defined(Hz60)			
				// 60 Hz
				//T0CON	 = 0x81;
				TMR0H	 = 0x3C;
				TMR0L	 = 0xB0;			  			  
			#endif	
			#if defined(Hz100)			
				// 100 Hz
				//T0CON	 = 0x80;
				TMR0H	 = 0x15;
				TMR0L	 = 0xA0;			    
			#endif	
			#if defined(Hz200)			
				// 200 Hz
				//T0CON	 = 0x88;
				TMR0H	 = 0x15;
				TMR0L	 = 0xA0;  
		 	#endif	   
			#if defined(Hz256)			
				// 256 Hz
			  //T0CON	 = 0x88;
			  TMR0H	 = 0x48;
			  TMR0L	 = 0xE5; 
		 	#endif	
		 			
		    // Clear timer flag
			INTCONbits.INT0IF = 0;
			INTCONbits.T0IF=0;
					    
//			LATCbits.LATC0=~	LATCbits.LATC0;			
			
			// can these move to a comment method????
			set_GSCLK_TRIG();
						
			// this is not used????
			RC_Buttons0 = READY;

		}	
}

// String for creating debug messages
char debugString[64];

// Vars for returning Device Version
char s_chr_DSN[]={DSN};
char s_chr_PSD[] ={PSD};
char s_chr_PSD0[]={PSD_p0};
char s_chr_PSD1[]={PSD_p1};
char s_chr_PSD2[]={PSD_p2};
char s_chr_PSD3[]={PSD_p3};
char s_chr_PSD4[]={PSD_p4};
char s_chr_PSD5[]={PSD_p5};
char s_chr_PSD6[]={PSD_p6};
char s_chr_PSD7[]={PSD_p7};
char s_chr_PSD8[]={PSD_p8};
char s_chr_PSD9[]={PSD_p9};
int index;


// Main program entry point
void main(void)
{
	// Initialise and configure the PIC ready to go
    initialisePic();

	// If we are running in interrupt mode attempt to attach the USB device
    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif
	
	// Initialise the debug log functions
    debugInitialise();
    
    // Show that we are up and running
    mDebugStatus_off();


	// Print Device ID
	for (index = 0; index <PSDLENGTH;index++)
	{		
    	switch(EEPROM_getPlayer())
          {
	           	case 0x00:
	            {
	            	debugString[index] = s_chr_PSD0[index];	
	               	break;
	            }
	           	case 0x01:
	            {
	            	debugString[index] = s_chr_PSD1[index];	
	               	break;
	            }
	           	case 0x02:
	            {
	            	debugString[index] = s_chr_PSD2[index];	
	               	break;
	            }
	           	case 0x03:
	            {
	            	debugString[index] = s_chr_PSD3[index];	
	               	break;
	            }
	           	case 0x04:
	            {
	            	debugString[index] = s_chr_PSD4[index];	
	               	break;
	            }
	           	case 0x05:
	            {
	            	debugString[index] = s_chr_PSD5[index];	
	               	break;
	            }
	           	case 0x06:
	            {
	            	debugString[index] = s_chr_PSD6[index];	
	               	break;
	            }
	           	case 0x07:
	            {
	            	debugString[index] = s_chr_PSD7[index];	
	               	break;
	            }
	           	case 0x08:
	            {
	            	debugString[index] = s_chr_PSD8[index];	
	               	break;
	            }
	           	case 0x09:
	            {
	            	debugString[index] = s_chr_PSD9[index];	
	               	break;
	            }
	           	default:
	            {
	            	debugString[index] = s_chr_PSD[index];	
	               	break;
	            }            
		  }   
	}
	debugString[PSDLENGTH] = 0;
	debugOut(debugString);	
			
	// Print version number
	for (index = 0; index <DSNLENGTH;index++)
	{
		debugString[index] = s_chr_DSN[index];		
	}
	debugString[DSNLENGTH] = 0;
	debugOut(debugString);
	
	// Print copy right
//	sprintf(debugString, "(C)2011 Simon Inns - http://www.waitingforfriday.com");
	sprintf(debugString, "(C)2014 David Quesenberry - http://www.QBytesWorld.com");
	debugOut(debugString);
	
	sprintf(debugString, "USB Device Initialised.");
	debugOut(debugString);
	
////      GSCLK = 0;//   output_low(GSCLK); 
//      SCLK  = 0;  //   output_low(SCLK);                      
//      DCPRG = 0;   //   output_low(DCPRG); 
//      VPRG  = 0;  //   output_high(VPRG);      
//      XLAT  = 0;  //   output_low(XLAT);    
//      BLANK = 0;  //   output_high(BLANK); 
      
// ================================================
    
	TLC5940_Init();

// ================================================	
	//Timer0

	#if defined(Hz50)	
		// 50 Hz
		set_DUTY_CYCLE(50);	
		//Prescaler 1:4; TMR0 Preload = 5536; Actual Interrupt Time : 20 ms		
		T0CON	 = 0x81;
	    TMR0H	 = 0x15;
	    TMR0L	 = 0xA0;
	#endif
	#if defined(Hz60)	
	    // 60 Hz
	    set_DUTY_CYCLE(60);
		//Prescaler 1:4; TMR0 Preload = 15536; Actual Interrupt Time : 16.666666667 ms	    	
		T0CON	 = 0x81;
		TMR0H	 = 0x3C;
		TMR0L	 = 0xB0;
	#endif	
	#if defined(Hz100)
		// 100 Hz
		set_DUTY_CYCLE(100);
		//Prescaler 1:2; TMR0 Preload = 5536; Actual Interrupt Time : 10 ms
		T0CON	 = 0x80;
		TMR0H	 = 0x15;
		TMR0L	 = 0xA0;
	#endif	
	#if defined(Hz200)
		// 200 Hz
		set_DUTY_CYCLE(200);
		//Prescaler 1:1; TMR0 Preload = 5536; Actual Interrupt Time : 5 ms
		T0CON	 = 0x88;
		TMR0H	 = 0x15;
		TMR0L	 = 0xA0;
	#endif	
	#if defined(Hz256)
		// 256 Hz
		set_DUTY_CYCLE(255);// 256;
		////Prescaler 1:1; TMR0 Preload = 18661; Actual Interrupt Time : 3.90625 ms
		T0CON	 = 0x88;
		TMR0H	 = 0x48;
		TMR0L	 = 0xE5;
	#endif
	
		    			  
    RCONbits.IPEN = 1;            // Enable interrupt priority 
    INTCONbits.PEIE = 1;          // interrupts allowed
    INTCONbits.GIE = 1;             
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    INTCON2bits.TMR0IP = 0;       // interrupt priority 0
    INTCONbits.TMR0IE = 1;        // timer0 interrupt enabled
//===========================================================================
// PWM 			
	#if defined(Hz50)
		/*
		 * PWM registers configuration
		 * Fosc = 48000000 Hz
		 * Fpwm =   203389.83 Hz (Requested : 204750 Hz  diff +1361)
		 * Duty Cycle = 50 %
		 * Resolution is 7 bits
		 * Prescaler is 1
		 * Ensure that your PWM pin is configured as digital output
		 * see more details on http://www.micro-examples.com/
		 * this source code is provided 'as is',
		 * use it at your own risks
		 */
		PR2 = 0b00111010 ;
		T2CON = 0b00000100 ;
		CCPR1L = 0b00011101 ;
		CCP1CON = 0b00011100 ;	
	#endif	
	#if defined(Hz60)
		/*
		 * PWM registers configuration
		 * Fosc = 48000000 Hz
		 * Fpwm =   244897.96 Hz (Requested : 245760 Hz  diff -863)
		 * Duty Cycle = 50 %
		 * Resolution is 7 bits
		 * Prescaler is 1
		 * Ensure that your PWM pin is configured as digital output
		 * see more details on http://www.micro-examples.com/
		 * this source code is provided 'as is',
		 * use it at your own risks
		 */
		PR2 = 0b00110000 ;
		T2CON = 0b00000100 ;
		CCPR1L = 0b00011000 ;
		CCP1CON = 0b00011100 ;
	#endif	
	#if defined(Hz100)
//		/*
//		 * PWM registers configuration
//		 * Fosc = 48000000 Hz
//		 * Fpwm = 413793.10 Hz (Requested : 409600 Hz diff +4193)
//		 * Duty Cycle = 50 %
//		 * Resolution is 6 bits
//		 * Prescaler is 1
//		 * Ensure that your PWM pin is configured as digital output
//		 * see more details on http://www.micro-examples.com/
//		 * this source code is provided 'as is',
//		 * use it at your own risks
//		 */
//		PR2 = 0b00011100 ;
//		T2CON = 0b00000100 ;
//		CCPR1L = 0b00001110 ;
//		CCP1CON = 0b00011100 ;
		/*
		 * PWM registers configuration
		 * Fosc = 48000000 Hz
		 * Fpwm =   400000.00 Hz (Requested : 409600.00 Hz diff -9600)
		 * Duty Cycle = 50 %
		 * Resolution is 6 bits
		 * Prescaler is 1
		 * Ensure that your PWM pin is configured as digital output
		 * see more details on http://www.micro-examples.com/
		 * this source code is provided 'as is',
		 * use it at your own risks
		 */
		PR2 = 0b00011101 ;
		T2CON = 0b00000100 ;
		CCPR1L = 0b00001110 ;
		CCP1CON = 0b00111100 ;		
	#endif	
	#if defined(Hz200)		
		/*
		 * PWM registers configuration
		 * Fosc = 48000000 Hz
		 * Fpwm =  800000.00 Hz (Requested : 819200 Hz diff -19200)
		 * Duty Cycle = 50 %
		 * Resolution is 5 bits
		 * Prescaler is 1
		 * Ensure that your PWM pin is configured as digital output
		 * see more details on http://www.micro-examples.com/
		 * this source code is provided 'as is',
		 * use it at your own risks
		 */
		PR2 = 0b00001110 ;
		T2CON = 0b00000100 ;
		CCPR1L = 0b00000111 ;
		CCP1CON = 0b00011100 ;
	#endif	
	#if defined(Hz256)
		///*
		// * PWM registers configuration
		// * Fosc = 48000000 Hz
		// * Fpwm = 1000000.00 Hz (Requested : 1000000 Hz diff 0)
		// * Duty Cycle = 50 %
		// * Resolution is 5 bits
		// * Prescaler is 4
		// * Ensure that your PWM pin is configured as digital output
		// * see more details on http://www.micro-examples.com/
		// * this source code is provided 'as is',
		// * use it at your own risks
		// */
		//PR2 = 0b00000010 ;
		//T2CON = 0b00000101 ;
		//CCPR1L = 0b00000001 ;
		//CCP1CON = 0b00011100 ;
				
		/*
		 * PWM registers configuration
		 * Fosc = 48000000 Hz
		 * Fpwm = 1090909.09 Hz (Requested : 1048576 Hz)
		 * Duty Cycle = 50 %
		 * Resolution is 5 bits
		 * Prescaler is 1
		 * Ensure that your PWM pin is configured as digital output
		 * see more details on http://www.micro-examples.com/
		 * this source code is provided 'as is',
		 * use it at your own risks
		 */
		PR2 = 0b00001010 ;
		T2CON = 0b00000100 ;
		CCPR1L = 0b00000101 ;
		CCP1CON = 0b00011100 ;
	#endif
// ================================================	
// ================================================	
// ================================================

	// Main processing loop
    while(1)
    {	
		#if defined(USB_POLLING)
			// If we are in polling mode the USB device tasks must be processed here
			// (otherwise the interrupt is performing this task)
	        USBDeviceTasks();
        #endif
    	
    	// Process USB Commands
        processUsbCommands();  
        
        // Note: Other application specific actions can be placed here    
					
//		LATCbits.LATC7=0;		

		// Make the LEDs go....
		Do_GrayScale();
   }
}


// Initialise the PIC
static void initialisePic(void)
{
    // PIC port set up --------------------------------------------------------

	// Default all pins to digital
    ADCON1 = 0x0F;

	// Configure ports as inputs (1) or outputs(0)
	TRISA = 0b00000000;
//	TRISB = 0b00000011; // input for Error and Sin- 
	TRISB = 0b11000000; // input for Error and Sin- 	
	TRISC = 0b00000000;
#if defined(__18F4550)
	TRISD = 0b00000000;
	TRISE = 0b00000000;
#endif

	// Clear all ports
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	
	#define joy_direction TRISAbits.TRISA2
	
#if defined(__18F4550)
	PORTD = 0b00000000;
	PORTE = 0b00000000;
#endif

	// If you have a VBUS sense pin (for self-powered devices when you
	// want to detect if the USB host is connected) you have to specify
	// your input pin in HardwareProfile.h
    #if defined(USE_USB_BUS_SENSE_IO)
    	tris_usb_bus_sense = INPUT_PIN;
    #endif
    
    // In the case of a device which can be both self-powered and bus-powered
    // the device must respond correctly to a GetStatus (device) request and
    // tell the host how it is currently powered.
    //
    // To do this you must device a pin which is high when self powered and low
    // when bus powered and define this in HardwareProfile.h
    #if defined(USE_SELF_POWER_SENSE_IO)
    	tris_self_power = INPUT_PIN;
    #endif

    // Application specific initialisation
    applicationInit();
    
    
    		
	//
//	EEPROM_setPlayer(6);
//	player = EEPROM_getPlayer();
//	player = 2;

    // Initialise the USB device
    USBDeviceInit();
}

// Application specific device initialisation
void applicationInit(void)
{
	// Initialise the status LEDs
	mInitStatusLeds();
	
	// Initialise the switch
	mInitAllSwitches();
	
    // Initialize the variable holding the USB handle for the last transmission
    USBOutHandle = 0;
    USBInHandle = 0;
}

// Process USB commands
void processUsbCommands(void)
{   
    // Check if we are in the configured state; otherwise just return
    if((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1))
    {
	    // We are not configured
	    return;
	}

	// Check if data was received from the host.
    if(!HIDRxHandleBusy(USBOutHandle))
    {   
		// Command mode 
		if (ReceivedDataBuffer[0]!=0x10 && ReceivedDataBuffer[0]!=0x81 && ReceivedDataBuffer[0]!=0x82 )
		{
			if (mDebugStatus == 0x01)
			{
	       	sprintf(debugString, "Received command 0x%X from host.",ReceivedDataBuffer[0]);
			debugOut(debugString);
			}
		}
				
        switch(ReceivedDataBuffer[0])
		{		
//			case 0x10:	// Debug information request from host
//				// Copy any waiting debug text to the send data buffer
//				copyDebugToSendBuffer((BYTE*)&ToSendDataBuffer[0]);
//			        
//		        // Transmit the response to the host
//                if(!HIDTxHandleBusy(USBInHandle))
//				{
//					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
//				}
//				break;
				
			// Place application specific commands here:
			
			case 0x10:	// Trigger information request from host
				// Copy any waiting debug text to the send data buffer
				copyDebugToSendBuffer((BYTE*)&ToSendDataBuffer[0]);

		        // Transmit the response to the host
                if(!HIDTxHandleBusy(USBInHandle))
				{
					//ToSendDataBuffer[0] = get_TRIGGERED();
					if 	(get_TRIGGERED() == 0x01)
					{	        
						clear_TRIGGERED();
						
						sprintf(debugString, "TRIGGER");
						debugOut(debugString);
						copyDebugToSendBuffer((BYTE*)&ToSendDataBuffer[0]);					
					}
					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
				}
				break;
				
			// Place application specific commands here:			
			
			
			// Joystick is a 4 or 8 way
            case 0x48:  // Change Joystick 4 or 8 way
				
				if (ReceivedDataBuffer[1] == 0x04)
					{
						// 4 way joystick
						mJoyDirection = 1;
					}
					else
					{	
						// Must be an 8 way joystick
						mJoyDirection = 0;
					}	
					
            	break;
            		
			
			// Joystick Z: Slide, Dial, or Rotate
            case 0x49:  // Change Joystick Slide, Dial, or Rotate  Z = (S, D, R)

				// Default to nothing 0x80
				mJoyZsw1	= 0;
				mJoyZsw2	= 0;
				
				if (ReceivedDataBuffer[1] == 0x01) 
					{// it's a Dial :   -->|<--
						mJoyZsw1 = 1;						
					}
					else
				if (ReceivedDataBuffer[1] == 0x2)
					{// it's a Slide :  |<--->|
						mJoyZsw2 = 1;
					}
					else
				if (ReceivedDataBuffer[1] == 0x03)
					{// it's a Rotate : >----->
						mJoyZsw1 = 1;
						mJoyZsw2 = 1;
					}
											
            	break;
            	
            // Can be the joystick spin sensitivity
            // Mouse has a LOW or HIGH DPI Resolusion
            case 0x84:  // Change mouse DPI
				
				if (ReceivedDataBuffer[1] == 0x00)
					{
						// Low speed
						mMouseSpeed = 0;
					}
					else
					{	
						// High Speed
						mMouseSpeed = 1;
					}	
					
            	break;
            	
			
            case 0x80:  // Toggle the LED
				// Toggle the LED0
				mDebugStatus_Toggle();
					
            	break;            	
            	
            case 0x81:  // Read the push switch status
				ToSendDataBuffer[0] = PORTBbits.RB7;//XERR;

				// Transmit the response to the host
                if(!HIDTxHandleBusy(USBInHandle))
				{
					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
				}
            	break;
            	
            case 0x82:  // Read the Debug status
				// Get the debug state and put it in the send buffer
				ToSendDataBuffer[0] = mDebugStatus_Get();
				
				// Transmit the response to the host
                if(!HIDTxHandleBusy(USBInHandle))
				{
					USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
				}
            	break;

// =====================================================
			case TLC_CMD: // should be ZERO.
				
				// Ask the TLC5940 to do work...
				USB_TLC5940(ReceivedDataBuffer);

			if (mDebugStatus == 0x01)
			{
					
		       	sprintf(debugString, "TLC_CMD - 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X from host.",
		       		ReceivedDataBuffer[0],ReceivedDataBuffer[1],ReceivedDataBuffer[2],ReceivedDataBuffer[3],ReceivedDataBuffer[4],ReceivedDataBuffer[5]);
				debugOut(debugString); 
			}													
				break;
				
// =====================================================
			case PID_SET: // Set product ID (Device ID 0-9).
				
				// Ask the PIC to set the ID
				EEPROM_setPlayer((unsigned char) ReceivedDataBuffer[1]);
					
			if (mDebugStatus == 0x01)
			{
		       	sprintf(debugString, "PID_SET - 0x%X 0x%X 0x%X round trip.",
		       		ReceivedDataBuffer[0],ReceivedDataBuffer[1],EEPROM_getPlayer());
				debugOut(debugString); 
			}
	// Reset the device			
_asm 
   reset
_endasm
//				reset_cpu(); // or mclr is grounded to reset 
																
				break;				

// =====================================================
			case PID_GET: // Set product ID.
				
				// Ask the PIC to set the ID
		       	sprintf(debugString, "PID_GET - 0x%X to host.", EEPROM_getPlayer());
				debugOut(debugString); 
																
				break;				
				
// =====================================================
											
            default:	// Unknown command received
		       	sprintf(debugString, "OOPS - Invalid command 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X from host.",
		       		ReceivedDataBuffer[0],ReceivedDataBuffer[1],ReceivedDataBuffer[2],ReceivedDataBuffer[3],ReceivedDataBuffer[4],ReceivedDataBuffer[5]);
				debugOut(debugString);            
           		break;
		}	
		 
        // Re-arm the OUT endpoint for the next packet
        USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
  	}
}

// USB Callback handling routines -----------------------------------------------------------

// Call back that is invoked when a USB suspend is detected
void USBCBSuspend(void)
{
}

// This call back is invoked when a wakeup from USB suspend is detected.
void USBCBWakeFromSuspend(void)
{
}

// The USB host sends out a SOF packet to full-speed devices every 1 ms.
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here. Callback caller is already doing that.
}

// The purpose of this callback is mainly for debugging during development.
// Check UEIR to see which error causes the interrupt.
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.
}

// Check other requests callback
void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
}

// Callback function is called when a SETUP, bRequest: SET_DESCRIPTOR request arrives.
void USBCBStdSetDscHandler(void)
{
    // You must claim session ownership if supporting this request
}

//This function is called when the device becomes initialized
void USBCBInitEP(void)
{
    // Enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    
    // Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
}

// Send resume call-back
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    // Verify that the host has armed us to perform remote wakeup.
    if(USBGetRemoteWakeupStatus() == FLAG_TRUE) 
    {
        // Verify that the USB bus is suspended (before we send remote wakeup signalling).
        if(USBIsBusSuspended() == FLAG_TRUE)
        {
            USBMaskInterrupts();
            
            // Bring the clock speed up to normal running state
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FLAG_FALSE;

            // Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            // device must continuously see 5ms+ of idle on the bus, before it sends
            // remote wakeup signalling.  One way to be certain that this parameter
            // gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            // least 3ms from bus idle to USBIsBusSuspended() == FLAG_TRUE, yeilds
            // 5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            } while(delay_count);
            
            // Start RESUME signaling for 1-13 ms
            USBResumeControl = 1;
            delay_count = 1800U;
            do
            {
                delay_count--;
            } while(delay_count);
            USBResumeControl = 0;

            USBUnmaskInterrupts();
        }
    }
}

// USB callback function handler
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            // Application callback tasks and functions go here
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        default:
            break;
    }      
    return FLAG_TRUE; 
}

#endif
